# projetoLpI

## Introdução

Este projeto faz parte da avaliação da **segunda unidade** da disciplina de **Linguagem de Programação**, orientada pelo professor **Jerffeson Gomes Dutra**.

O sistema foi desenvolvido em **C++** com o objetivo de **gerenciar uma academia**, incluindo o controle de **alunos, professores, aulas, planos, equipamentos e treinos**.  

A estrutura do projeto está organizada da seguinte forma:
- `header/` — contém os arquivos de cabeçalho (headers)
- `src/` — contém as implementações e o arquivo principal `main.cpp`

---

### Integrantes do grupo

- **César Nascimento de França**  
- **Guilherme Amador Rosa Veras**  
- **Rafael Fernandes da Silva**  
- **Rafael Nonato Moreira da Silva**
## Requisitos

- Compilador C++ com suporte a C++17 (por exemplo MinGW-w64 / g++) no Windows.
- (Opcional) Java + PlantUML/Graphviz para gerar diagramas a partir do arquivo PlantUML.

## Estrutura do repositório

- `header/` - arquivos `.h` com declarações das classes
- `src/` - arquivos `.cpp` com implementações e `main.cpp`
- `diagrams/project.puml` - diagrama PlantUML do projeto

## Como compilar (Windows PowerShell)

Opção A — compilar a partir da pasta `src` (procedimento simples):

1. Abra o PowerShell e navegue até a pasta `src`:

```powershell
cd C:\\PROGRAMACAO-PROJETOS\\projetoLpI\\src
```

2. Compile com g++ (exemplo MinGW):

```powershell
# Se estiver usando g++ no PATH
g++ -std=c++17 -I..\\header *.cpp -o academia.exe
```

3. Execute:

```powershell
# ajustar console para UTF-8 se necessário
chcp 65001
.\\academia.exe
```

Opção B — compilar a partir da raiz do projeto (com paths explícitos):

```powershell
cd C:\\PROGRAMACAO-PROJETOS\\projetoLpI
g++ -std=c++17 -Iheader src\\*.cpp -o academia.exe
chcp 65001
.\\academia.exe
```

## Como usar

- Execute `academia.exe` e siga os menus interativos no terminal.
- Menus oferecem opções para gerenciar Academia, Alunos, Professores, Planos, Equipamentos e Treinos.
- Para listar os treinos de um aluno: `Gerenciar Treinos` → `Listar treinos de um aluno` e informe a matrícula.


