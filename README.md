# CG (Computação Gráfica)
Projeto de grupo desenvolvido no âmbito da Unidade Curricular de Computação Gráfica. Este projeto consistiu na implementação de um  mini motor gráfico 3D baseado em cenas, e de um gerador que forneça exemplos de utilização para o mesmo.

### Membros do Grupo
- [Duarte Escairo](https://github.com/darteescar)
- [Luís Soares](https://github.com/luis7788)
- [Tiago Figueiredo](https://github.com/tiagofigueiredo7)
- [Inês Ribeiro](https://github.com/inesferribeiro)

---

### Ficheiros relevantes
- [Enunciado](./extra_files/enunciado.pdf)
- <<report fase 1>>
- <<report fase 2>>
- <<report fase 3>>
- <<report fase 4>>

> ⚠️ **Dependências:** Para compilar e correr os programas é necessário ter instalado o `CMake`, o `GLUT` e a biblioteca `libtinyxml2-dev`. Para além disso, é necessário ter um compilador C++ instalado (recomenda-se o `g++`).

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
./engine ../../tests/other/p1/sphere.3d
```

> **Nota:** Os ficheiros de cena devem estar localizados na diretoria `projeto/tests/` ou em subdiretorias da mesma, e os ficheiros de modelos devem estar localizados na diretoria `projeto/models/`.
