# projetoLpI

## Introdução

Projeto da **terceira unidade** da disciplina de **Linguagem de Programação** (prof. **Jerffeson Gomes Dutra**).

Sistema em **C++17** para gerenciar uma academia: alunos, professores, aulas, planos, equipamentos, treinos, academias/filiais e avaliações. Todos os dados são persistidos em arquivos texto em `bin/`.

### Integrantes do grupo

- **César Nascimento de França**  
- **Guilherme Amador Rosa Veras**  
- **Rafael Fernandes da Silva**  
- **Rafael Nonato Moreira da Silva**
## Requisitos

- Compilador C++ com suporte a C++17 (ex.: MinGW-w64 / g++ em Windows).
- PowerShell (para os comandos abaixo). Opcional: Java + PlantUML/Graphviz se quiser gerar a imagem a partir dos arquivos `.puml`.

## Estrutura do repositório

- `header/` — cabeçalhos das classes (interfaces `IIdentificavel`, `IFilePersistable` e demais entidades)
- `src/` — implementações em C++ e `main.cpp`
- `bin/` — arquivos texto usados para persistência (alunos, professores, planos, treinos, etc.)
- `diagrama_simplificado.puml` — diagrama PlantUML simplificado

## Como compilar e executar

### Opção 1: Usando `make` (Linux, macOS e Windows com MinGW/MSYS2)

Na raiz do projeto:

```bash
make run
```

Ou compilar e rodar em separado:

```bash
make          # compila
./main        # executa (Linux/macOS)
main.exe      # executa (Windows)
```

Limpar arquivos compilados:

```bash
make clean
```

### Opção 2: Compilação manual com g++ (Windows PowerShell)

Na raiz do projeto:

```powershell
g++ -std=c++17 -Iheader src\*.cpp -o main.exe
.\main.exe
```

Observações:
- Se precisar ajustar encoding do console: `chcp 65001` para UTF-8.
- A opção `make run` funciona em qualquer SO com `make` instalado (recomendado).
- No Windows sem `make`, use a compilação manual com g++.

## Como usar

- Execute `main.exe` e siga os menus interativos.
- Operações disponíveis: gerenciar Academia/Filiais, Alunos, Professores, Planos (inclui planos personalizados), Aulas, Equipamentos, Treinos e Avaliações.
- Todos os dados são salvos automaticamente nos arquivos em `bin/` após cada operação.

## Destaques do projeto

- 2 classes abstratas: `Pessoa` (método puro virtual `exibir`) e `Plano` (método puro virtual `calcularValor`).
- Persistência completa em arquivos texto por entidade (`bin/*.txt`).
- Sistema de treinos vinculado ao aluno, com equipamentos listados por nome.
- Diagrama UML atualizado em `diagrama_simplificado.puml`.


