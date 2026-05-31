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
- [Relatório Fase 4](./reports/fase4/relatorio_fase_4.pdf)

#### Demos
- [Demo Fase 2](./tests/others/p2/demo_fase_2.xml)
- [Demo Fase 3](./tests/others/p3/demo_fase_3.xml)
- [Demo Fase 4](./tests/others/p4/demo_fase_4.xml)

#### Outros ficheiros
- **Ficheiros de cena:** [tests/](./tests/) ou em subdiretórios de [tests/](./tests/)
- **Ficheiros de modelos:** [projeto/models/](./projeto/models/)
- **Ficheiros `.patch`:** [projeto/patchs/](./projeto/patchs/)
- **Ficheiros de texturas:** [projeto/texturas/](./projeto/texturas/)
- **Formato de ficheiros de modelos:** [extra_files/formato.3d](./extra_files/formato.3d)

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
> Os ficheiros gerados pelo programa `generator` são guardados diretamente na diretoria `projeto/models/`.
> O `engine` lê os ficheiros `.patch` da diretoria `projeto/patchs/`, as texturas da diretoria `projeto/texturas/` e os ficheiros `.3d` da diretoria `projeto/models/`.
> Não é necessário especificar o caminho completo para os ficheiros de modelos, texturas ou patches, basta especificar o nome do ficheiro (com a extensão). Por exemplo, para usar o modelo `sphere.3d` gerado pelo `generator`, basta especificar `sphere.3d` no ficheiro de cena, e não é necessário especificar o caminho completo `projeto/models/sphere.3d`.
> Para além disso, os ficheiros de cena podem ser guardados em qualquer diretoria, mas é recomendado que sejam guardados na diretoria `tests/` ou em subdiretórios desta.