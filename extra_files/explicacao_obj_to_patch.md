# obj_to_patch.py — Documentação

## Descrição

O programa `obj_to_patch.py` converte um modelo geométrico no formato `.obj` num ficheiro `.patch` de superfícies de Bézier bicúbicas, pronto a ser utilizado pelo `generator` para tessellação. O processo é inteiramente automático — o programa detecta a orientação do modelo, extrai o seu perfil geométrico e gera os pontos de controlo sem necessitar de intervenção manual.

## Utilização

```
python3 obj_to_patch.py <input.obj> <output.patch> [n_levels]
```

| Argumento | Obrigatório | Descrição |
|-----------|:-----------:|-----------|
| `input.obj` | sim | Ficheiro OBJ de entrada |
| `output.patch` | sim | Ficheiro `.patch` de saída |
| `n_levels` | não | Número de níveis chave ao longo do eixo principal (default: `7`) |

## Pipeline de processamento

### 1. Leitura do ficheiro OBJ

O programa lê todas as linhas do ficheiro `.obj` que começam por `v` e extrai as coordenadas $(x, y, z)$ de cada vértice, ignorando normais, coordenadas de textura e faces.

### 2. Detecção do eixo principal

Para cada um dos três eixos, calcula-se a extensão do modelo:

$$\text{range}_i = \max_j(v_{ij}) - \min_j(v_{ij}), \quad i \in \{x, y, z\}$$

O eixo com maior extensão é considerado o eixo principal. As coordenadas dos vértices são então reordenadas de forma a que esse eixo corresponda sempre ao eixo $z$ interno, tornando o processamento seguinte independente da orientação original do modelo.

### 3. Extração do perfil geométrico

O modelo é dividido em `n_bins = n_levels × 3` faixas de igual largura ao longo do eixo principal. Para cada faixa $b$, calculam-se os seguintes valores a partir dos vértices que lhe pertencem:

**Centróide local:**

$$c_x(b) = \frac{1}{N_b} \sum_{i \in b} x_i, \qquad c_y(b) = \frac{1}{N_b} \sum_{i \in b} y_i$$

**Raios assimétricos** a partir do centróide local, nos quatro semi-eixos:

$$r_x^-(b) = c_x(b) - \min_{i \in b}(x_i), \qquad r_x^+(b) = \max_{i \in b}(x_i) - c_x(b)$$

$$r_y^-(b) = c_y(b) - \min_{i \in b}(y_i), \qquad r_y^+(b) = \max_{i \in b}(y_i) - c_y(b)$$

O perfil de cada faixa fica assim descrito pelo tuplo $(z_b,\ c_x,\ c_y,\ r_x^-,\ r_x^+,\ r_y^-,\ r_y^+)$.

### 4. Seleção dos níveis chave

De entre as `n_bins` faixas extraídas, seleciona-se um subconjunto de `n_levels` faixas distribuídas uniformemente ao longo do eixo principal. O índice da faixa selecionada para o nível $i$ é:

$$\text{idx}_i = \text{round}\!\left(i \cdot \frac{N_{\text{bins}} - 1}{n_{\text{levels}} - 1}\right), \quad i \in \{0, \ldots, n_{\text{levels}}-1\}$$

Estes níveis chave são os que definem a forma geral da superfície gerada.

### 5. Normalização das coordenadas

As coordenadas são normalizadas de forma a preservar as proporções reais do modelo. O raio máximo observado em todos os níveis chave é normalizado para 1.0, e o comprimento em $z$ escala proporcionalmente:

$$f = \frac{1.0}{r_{\max}}, \qquad \text{scale}_z = \frac{z_{\max} - z_{\min}}{r_{\max}}$$

$$z_{\text{norm}} = \frac{z - z_{\min}}{z_{\max} - z_{\min}} \times \text{scale}_z, \qquad r_{\text{norm}} = r \times f$$

### 6. Aproximação cúbica de Bézier de uma elipse assimétrica

Cada secção transversal é aproximada por quatro arcos cúbicos de Bézier de 90° cada, usando a constante:

$$k = \frac{4(\sqrt{2}-1)}{3} \approx 0.5523$$

que minimiza o erro de aproximação de um arco circular com uma curva cúbica de Bézier. Como cada secção é uma elipse assimétrica com raios distintos nos quatro semi-eixos e centróide deslocado, os quatro pontos de controlo de cada quadrante são calculados individualmente. Para o quadrante $Q_0$ (de $+x$ para $+y$):

$$P_0 = (c_x + r_x^+,\ c_y,\ z)$$
$$P_1 = (c_x + r_x^+,\ c_y + r_y^+ \cdot k,\ z)$$
$$P_2 = (c_x + r_x^+ \cdot k,\ c_y + r_y^+,\ z)$$
$$P_3 = (c_x,\ c_y + r_y^+,\ z)$$

Os restantes quadrantes seguem o mesmo padrão com os respetivos raios:

| Quadrante | Direção | Raios usados |
|:---------:|:-------:|:------------:|
| $Q_0$ | $+x \to +y$ | $r_x^+$, $r_y^+$ |
| $Q_1$ | $+y \to -x$ | $r_x^-$, $r_y^+$ |
| $Q_2$ | $-x \to -y$ | $r_x^-$, $r_y^-$ |
| $Q_3$ | $-y \to +x$ | $r_x^+$, $r_y^-$ |

O ponto $P_3$ de cada quadrante coincide com o ponto $P_0$ do quadrante seguinte, garantindo continuidade $C^0$ ao longo da secção transversal.

### 7. Construção dos patches bicúbicos

Adicionam-se dois **polos** às extremidades da lista de níveis — pontos singulares com $r = 0$ onde a superfície converge, representando as pontas do modelo. Para cada banda entre dois níveis consecutivos $z_0$ e $z_1$, e para cada um dos quatro quadrantes angulares, constrói-se um patch bicúbico com uma grelha $4 \times 4$ de pontos de controlo organizada em quatro linhas:

| Linha | Nível em $z$ | Origem |
|:-----:|:------------:|:-------|
| 0 | $z_0$ | pontos do nível inferior |
| 1 | $z_0 + \frac{1}{3}(z_1 - z_0)$ | interpolação linear |
| 2 | $z_0 + \frac{2}{3}(z_1 - z_0)$ | interpolação linear |
| 3 | $z_1$ | pontos do nível superior |

Os raios e centróides nos níveis intermédios são obtidos por interpolação linear entre os dois níveis adjacentes. Com `n_levels` níveis chave mais os 2 polos, obtêm-se `n_levels + 1` bandas de 4 quadrantes cada, resultando em `(n_levels + 1) × 4` patches no total.

### 8. Escrita do ficheiro `.patch`

O ficheiro de saída segue o formato padrão:

```
<número de patches>
<índices dos 16 pontos de controlo do patch 0>
...
<índices dos 16 pontos de controlo do patch N-1>
<número de pontos de controlo>
<x0>, <y0>, <z0>
...
```