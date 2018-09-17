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
- main_extensions.h: Componente comunicante entre Framework de rasterização <-> Pipeline+Espaco
- common.h: Contém algumas implementações comuns a várias partes do projeto, especificamente, contém métodos para gerar matrizes bem conhecidas, como as transformações e bases.
- espaco.h: Contém a classe SpaceContainer, responsável parcial do Pipeline (view, projection, viewport), bem como armazena os objetos da cena. Atua como se fosse um "universo".
- objetos.h: Representa um objeto (modelo), contendo os vértices e a matriz Model.

<br /> <br />

---

## Funcionamento / Instruções de uso


## Detalhes e Especificação de Implementação


## Resultados



## Experimentos


## Referências


0. _Por questões de compatibilidade e praticidade, optou-se por copiar e manter a biblioteca Eigen 3.3.5 na pasta eigen-folder. Este projeto e autor não possui qualquer vínculo, relação ou posse com o projeto Eigen e seus autores._
1. _https://blender.org/_
