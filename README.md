# ICG-2nd-Pipeline
---

## Introdução
Este projeto aborda e implementa o processo de construção do pipeline gráfico, bem como a importação e rasterização de objetos utilizando-se do mesmo. Para tanto, é usado um framework modificado (https://raw.githubusercontent.com/VictorKoehler/ICG-1st-BresenhamAlgorithm) com base em um de fins didáticos disponibilizado por Christian Pagot, professor da Universidade Federal da Paraíba, da qual este trabalho se destina como complemento de nota da disciplina de Introdução à Computação Gráfica, período 2018.1.

Discente: Victor José de Sousa Koehler

Matrícula: 20170068974

<br><br><br>

---

## Dependências
Eigen<sup>[0]</sup>: http://eigen.tuxfamily.org

Assimp: http://assimp.org/


---

## O Projeto
Este projeto é uma continuação do trabalho de desenvolvimento de um framework didático de rasterização. Detalhes de uso, implementação e documentação do mesmo não fazem parte do escopo deste trabalho. Para mais informações, visite: https://raw.githubusercontent.com/VictorKoehler/ICG-1st-BresenhamAlgorithm

<br /> <br />

Este projeto está dividido conceitualmente da seguinte forma:
- main.h, mygl.h, definitions.h: Framework base de rasterização.
- eigen-folder: Biblioteca Eigen para cálculos númericos/algébricos.
- pipeline.m, pipeline2.m: Material de apoio fornecido pelo docente (modificado).
- Esfera.obj, monkey_head2.obj: Material usado como exemplo. Origem: Blender<sup>[1]</sup>
- main.cpp: Inicialização
- pipeline_extensions.h: Componente comunicante entre Framework de rasterização <-> Pipeline+Espaco
- common.h: Contém algumas implementações comuns a várias partes do projeto, especificamente, contém métodos para gerar matrizes bem conhecidas, como as transformações e bases.
- scene.h: Contém a classe Scene, responsável parcial do Pipeline (view, projection, viewport), bem como armazena os objetos da cena. Atua como se fosse um "universo".
- objectmodel.h: Representa um objeto (modelo), contendo os vértices e a matriz Model.
- examples.h: Contém os exemplos de implementação e importação.

<br /> <br />

---

## Funcionamento
O projeto é constituido de três partes principais + extensões e exemplos:
Fundamentalmente, é necessário instanciar um objeto do tipo Scene, o qual conterá os objetos (modelos) da "*cena*" bem como a configuração do espaço e da câmera (Pipeline). Recomenda-se, pelo menos como referência, o uso do segundo construtor da classe, isto é, `Scene(Vector3f camera_position, Vector3f camera_lookAt, Vector3f camera_up, float camera_dist, int screen_width, int screen_height)`, pela praticidade e clareza do mesmo. A classe ainda dispõe de métodos construtores das matrizes do Pipeline, bem como de um método de carregamento de objetos.
A classe ObjectModel contém todos os objetos visíveis, sendo formada por um conjunto de vértices de triângulos, bem como contém a matriz Model (individual ao objeto).
Note que para importar um modelo de um arquivo é possível usar o método `int loadObject(const std::string &file_name)` da classe Scene, que por sua vez adiciona automaticamente tal objeto em seu escopo.
Além disso, um importante detalhe na implementação dessas classes é a exposição do nível de acesso das matrizes (Model, no caso de ObjectModel; View, Projection e Viewport no caso de Scene) e de seus containers (Vector de Vertice, no caso de ObjectModel; Vector de ObjectModel, no caso de Scene), possibilitando acesso direto e otimizado dessas propriedades.
Por fim, o arquivo examples.h contém diversos trechos de código, incluindo testes das implementações.

<br /> <br />

---

## Detalhes e Especificação de Implementação



## Resultados



## Experimentos



## Referências


0. _Por questões de compatibilidade e praticidade, optou-se por copiar e manter a biblioteca Eigen 3.3.5 na pasta eigen-folder. Este projeto e autor não possui qualquer vínculo, relação ou posse com o projeto Eigen e seus autores._
1. _https://blender.org/_
