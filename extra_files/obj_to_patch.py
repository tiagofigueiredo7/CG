import math
import sys

def parse_obj(filepath):
    vertices = []
    with open(filepath) as f:
        for line in f:
            if line.startswith('v '):
                parts = line.strip().split()
                x, y, z = float(parts[1]), float(parts[2]), float(parts[3])
                vertices.append((x, y, z))
    return vertices

def extract_profile(vertices, bin_size=1.0):
    bins = {}
    for x, y, z in vertices:
        b = round(z / bin_size) * bin_size
        if b not in bins:
            bins[b] = []
        bins[b].append((x, y))

    profile = []
    for b in sorted(bins.keys()):
        pts = bins[b]
        lx = [p[0] for p in pts]
        ly = [p[1] for p in pts]
        cx = sum(lx) / len(lx)
        cy = sum(ly) / len(ly)
        rx_neg = cx - min(lx)
        rx_pos = max(lx) - cx
        ry_neg = cy - min(ly)
        ry_pos = max(ly) - cy
        profile.append((b, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos))

    return profile

def select_key_levels(profile, n_levels=7):
    # Selecionar n_levels niveis distribuidos uniformemente ao longo do perfil
    total = len(profile)
    indices = [round(i * (total - 1) / (n_levels - 1)) for i in range(n_levels)]
    return [profile[i] for i in indices]

def interp_level(lev0, lev1, t):
    return tuple(lev0[i] + t * (lev1[i] - lev0[i]) for i in range(7))

def normalize_levels(key_levels, scale_z=8.0, scale_r=1.4):
    z_min = key_levels[0][0]
    z_max = key_levels[-1][0]
    r_max = max(max(l[3], l[4], l[5], l[6]) for l in key_levels)

    norm = []
    for lev in key_levels:
        z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos = lev
        z_n   = (z - z_min) / (z_max - z_min) * scale_z
        f     = scale_r / r_max
        norm.append((z_n, cx*f, cy*f, rx_neg*f, rx_pos*f, ry_neg*f, ry_pos*f))

    return norm

def ellipse_quads(z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos):
    k = 0.5523
    return [
        # Q0: +x -> +y
        [(cx+rx_pos, cy,          z),
         (cx+rx_pos, cy+ry_pos*k, z),
         (cx+rx_pos*k, cy+ry_pos, z),
         (cx,          cy+ry_pos, z)],
        # Q1: +y -> -x
        [(cx,          cy+ry_pos, z),
         (cx-rx_neg*k, cy+ry_pos, z),
         (cx-rx_neg,   cy+ry_pos*k, z),
         (cx-rx_neg,   cy,        z)],
        # Q2: -x -> -y
        [(cx-rx_neg,   cy,          z),
         (cx-rx_neg,   cy-ry_neg*k, z),
         (cx-rx_neg*k, cy-ry_neg,   z),
         (cx,          cy-ry_neg,   z)],
        # Q3: -y -> +x
        [(cx,          cy-ry_neg,   z),
         (cx+rx_pos*k, cy-ry_neg,   z),
         (cx+rx_pos,   cy-ry_neg*k, z),
         (cx+rx_pos,   cy,          z)],
    ]

def build_patches(norm_levels):
    # Adicionar polos nas extremidades
    z_start = norm_levels[0][0]
    z_end   = norm_levels[-1][0]
    pole_start = (z_start, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    pole_end   = (z_end,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    levels = [pole_start] + norm_levels + [pole_end]

    all_points = []
    level_quad_idx = []

    for lev in levels:
        z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos = lev
        is_pole = (rx_pos < 1e-6 and rx_neg < 1e-6)
        quad_idx = []

        if is_pole:
            pole = len(all_points)
            all_points.append((cx, cy, z))
            for _ in range(4):
                quad_idx.append([pole] * 4)
        else:
            quads = ellipse_quads(z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos)
            starts = []
            for q in range(4):
                s = len(all_points)
                all_points.append(quads[q][0])
                all_points.append(quads[q][1])
                all_points.append(quads[q][2])
                starts.append(s)
            for q in range(4):
                quad_idx.append([
                    starts[q],
                    starts[q] + 1,
                    starts[q] + 2,
                    starts[(q + 1) % 4]
                ])
        level_quad_idx.append(quad_idx)

    patches = []
    for band in range(len(levels) - 1):
        lev0 = levels[band]
        lev1 = levels[band + 1]
        bot  = level_quad_idx[band]
        top  = level_quad_idx[band + 1]

        for q in range(4):
            mid_pts = []
            for frac in [1/3.0, 2/3.0]:
                lev_mid = interp_level(lev0, lev1, frac)
                z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos = lev_mid
                is_pole = (rx_pos < 1e-6 and rx_neg < 1e-6)

                if is_pole:
                    best = min(range(len(all_points)),
                               key=lambda i: abs(all_points[i][2] - z))
                    col_idx = [best] * 4
                else:
                    quads_m = ellipse_quads(z, cx, cy, rx_neg, rx_pos, ry_neg, ry_pos)
                    col_idx = []
                    for col in range(4):
                        idx = len(all_points)
                        all_points.append(quads_m[q][col])
                        col_idx.append(idx)
                mid_pts.append(col_idx)

            patch = bot[q] + mid_pts[0] + mid_pts[1] + top[q]
            patches.append(patch)

    return patches, all_points

def write_patch(patches, all_points, output_path):
    max_idx = max(max(p) for p in patches)
    assert max_idx < len(all_points), \
        f"Erro: indice {max_idx} fora do intervalo [{len(all_points)} pontos]"

    lines = [str(len(patches))]
    for p in patches:
        lines.append(', '.join(str(i) for i in p))
    lines.append(str(len(all_points)))
    for pt in all_points:
        lines.append(f"{pt[0]:.6f}, {pt[1]:.6f}, {pt[2]:.6f}")

    with open(output_path, 'w') as f:
        f.write('\n'.join(lines) + '\n')

    print(f"Ficheiro escrito: {output_path}")
    print(f"  Patches:          {len(patches)}")
    print(f"  Pontos controlo:  {len(all_points)}")

def main():
    if len(sys.argv) < 3:
        print("Uso: python obj_to_patch.py <input.obj> <output.patch> [n_levels] [scale_z] [scale_r]")
        print("  n_levels  : numero de niveis chave ao longo do eixo (default: 7)")
        print("  scale_z   : comprimento normalizado do eixo Z (default: 8.0)")
        print("  scale_r   : raio maximo normalizado (default: 1.4)")
        sys.exit(1)

    obj_path    = sys.argv[1]
    patch_path  = sys.argv[2]
    n_levels    = int(sys.argv[3])   if len(sys.argv) > 3 else 7
    scale_z     = float(sys.argv[4]) if len(sys.argv) > 4 else 8.0
    scale_r     = float(sys.argv[5]) if len(sys.argv) > 5 else 1.4

    print(f"A ler: {obj_path}")
    vertices = parse_obj(obj_path)
    print(f"  Vertices lidos: {len(vertices)}")

    profile = extract_profile(vertices)
    print(f"  Faixas extraidas: {len(profile)}")

    key_levels = select_key_levels(profile, n_levels)
    print(f"  Niveis chave selecionados: {len(key_levels)}")

    norm_levels = normalize_levels(key_levels, scale_z, scale_r)

    patches, all_points = build_patches(norm_levels)

    write_patch(patches, all_points, patch_path)

if __name__ == '__main__':
    main()