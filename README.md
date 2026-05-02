# CG (Computação Gráfica)
Projeto de grupo desenvolvido no âmbito da Unidade Curricular de Computação Gráfica. Este projeto consistiu na implementação de um  mini motor gráfico 3D baseado numa estrutura de <i>scene graph</i>, e de um gerador que forneça exemplos de utilização para o mesmo.

### Membros do Grupo
- [Duarte Escairo](https://github.com/darteescar)
- [Luís Soares](https://github.com/luis7788)
- [Tiago Figueiredo](https://github.com/tiagofigueiredo7)
- [Inês Ribeiro](https://github.com/inesferribeiro)

---

### Ficheiros relevantes
- [Enunciado](./extra_files/enunciado.pdf)
- [Relatório Fase 1](./reports/fase1/relatorio_fase_1.pdf)
- [Relatório Fase 2](./reports/fase2/relatorio_fase_2.pdf)
- [Relatório Fase 3](./reports/fase3/relatorio_fase_3.pdf)
- <<report fase 4>> *(não disponível)*

#### Demos
- [Demo Fase 2](./tests/others/p2/demo_fase_2.xml)
- [Demo Fase 3](./tests/others/p3/demo_fase_3.xml)
- [Demo Fase 4](./tests/others/p4/demo_fase_4.xml)

#### Patchs
- Os ficheiros `.patch` podem ser encontrados na diretoria [projeto/patchs](./projeto/patchs/)

> [!WARNING]
> **Dependências:** Para compilar e correr os programas é necessário ter instalado o `CMake`, o `GLUT` e a biblioteca `libtinyxml2-dev`. Para além disso, é necessário ter um compilador C++ instalado (recomenda-se o `g++`).

## Compile

Para compilar o projeto pela primeira vez, basta correr os seguintes comandos no terminal, a partir da diretoria principal do projeto:

```bash
cd projeto/build
cmake .. && make
```

Caso seja feita alguma alteração ao código, basta correr o comando `make` para compilar novamente o projeto (dentro da diretoria `projeto/build`).

## Execute

Para correr o programa `generator`, basta correr o seguinte comando no terminal, a partir da diretoria `projeto/build`:

```bash
./generator <figure> <parameters> <output_file>
```
Este comando é genérico já que é necessário especificar a figura, os parâmetros e o ficheiro de saída. Como exemplo de utilização, o comando abaixo gera um ficheiro `sphere.3d` com uma esfera de raio 1, 10 _slices_ e 10 _stacks_:

```bash
./generator sphere 1 10 10 sphere.3d
```

Para correr o programa `engine`, basta correr o seguinte comando no terminal, a partir da diretoria `projeto/build`:

```bash
./engine <scene_file>
```
Este comando é genérico já que é necessário especificar o ficheiro de cena a ser renderizado. Como exemplo de utilização, o comando abaixo renderiza a cena descrita no ficheiro `sphere.3d`:

```bash
./engine ../../tests/others/p1/sphere.xml
```
> [!NOTE]
> Os ficheiros de cena devem estar localizados na diretoria `tests/` ou em subdiretorias da mesma, os ficheiros de modelos devem estar localizados na diretoria `projeto/models/` e os ficheiros `.patch` devem estar localizados na diretoria `projeto/patchs/`.