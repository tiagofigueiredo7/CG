#!/usr/bin/env python3
"""
Conversor de arquivos .obj para o formato .3d
Uso: python conversor.py <arquivo.obj> <saida.3d>
"""

import sys

def parse_obj(obj_file):
    """
    Faz parse um arquivo .obj e retorna vértices e faces.
    """
    vertices = []
    faces = []
    
    with open(obj_file, 'r') as f:
        for line in f:
            line = line.strip()
            
            # Ignorar linhas vazias e comentários
            if not line or line.startswith('#'):
                continue
            
            parts = line.split()
            if not parts:
                continue
            
            # Ler vértices
            if parts[0] == 'v':
                x, y, z = float(parts[1]), float(parts[2]), float(parts[3])
                vertices.append((x, y, z))
            
            # Ler faces (podem ser triângulos ou quads)
            elif parts[0] == 'f':
                # OBJ pode ter formatos como: f 1 2 3 ou f 1/1/1 2/2/2 3/3/3
                # Pegamos apenas no índice do vértice (primeiro número)
                face_indices = []
                for vertex_data in parts[1:]:
                    # Separar por '/' e pegar no primeiro valor (índice do vértice)
                    vertex_idx = int(vertex_data.split('/')[0]) - 1  # OBJ usa índices base-1
                    face_indices.append(vertex_idx)
                faces.append(face_indices)
    
    return vertices, faces

def triangulate_faces(faces):
    """
    Converte faces em triângulos.
    Se a face já é um triângulo, mantém. Se é quad, divide em 2 triângulos.
    """
    triangles = []
    
    for face in faces:
        if len(face) == 3:
            # Já é um triângulo
            triangles.append(face)
        elif len(face) == 4:
            # É um quad, dividir em 2 triângulos
            triangles.append([face[0], face[1], face[2]])
            triangles.append([face[0], face[2], face[3]])
        elif len(face) > 4:
            # Polígono com mais de 4 vértices - triangulação em leque
            for i in range(1, len(face) - 1):
                triangles.append([face[0], face[i], face[i + 1]])
    
    return triangles

def convert_to_3d(obj_file, output_file):
    """
    Converte arquivo .obj para formato .3d
    """
    print(f"Lendo arquivo {obj_file}...")
    vertices, faces = parse_obj(obj_file)
    
    print(f"  - Vértices encontrados: {len(vertices)}")
    print(f"  - Faces encontradas: {len(faces)}")
    
    # Triangular as faces
    triangles = triangulate_faces(faces)
    print(f"  - Triângulos gerados: {len(triangles)}")
    
    # Escrever no formato .3d
    print(f"Escrevendo arquivo {output_file}...")
    with open(output_file, 'w') as f:
        for triangle in triangles:
            # Cada triângulo tem 3 vértices
            for vertex_idx in triangle:
                v = vertices[vertex_idx]
                f.write(f"{v[0]} {v[1]} {v[2]}\n")
    
    total_vertices = len(triangles) * 3
    print(f"✓ Conversão concluída! {total_vertices} vértices escritos.")

def main():
    if len(sys.argv) != 3:
        print("Uso: python conversor.py <arquivo.obj> <saida.3d>")
        print("\nExemplo:")
        print("  python conversor.py vaca.obj vaca.3d")
        sys.exit(1)
    
    obj_file = sys.argv[1]
    output_file = sys.argv[2]
    
    try:
        convert_to_3d(obj_file, output_file)
    except FileNotFoundError:
        print(f"ERRO: Arquivo '{obj_file}' não encontrado.")
        sys.exit(1)
    except Exception as e:
        print(f"ERRO durante conversão: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
