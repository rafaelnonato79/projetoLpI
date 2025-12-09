# Diagrama UML - Sistema de Gerenciamento de Academia

## Arquivo PlantUML

```plantuml
@startuml Sistema_Academia

skinparam classAttributeIconSize 0
skinparam backgroundColor white
skinparam shadowing false

' ============ CLASSES PRINCIPAIS ============

class Gerenciador {
  -alunos: vector<Aluno>
  -professores: vector<Professor>
  -planos: vector<shared_ptr<Plano>>
  -aulas: vector<shared_ptr<Aula>>
  -equipamentos: vector<Equipamento>
  -academias: vector<Academia>
  -avaliacoes: vector<Avaliacao>
  --
  +adicionarAluno(Aluno)
  +removerAluno(matricula)
  +listarAlunos()
  +adicionarProfessor(Professor)
  +removerProfessor(id)
  +adicionarPlano(Plano)
  +adicionarAula(Aula)
  +adicionarEquipamento(Equipamento)
}

abstract class Pessoa {
  -id: int
  -nome: string
  -telefone: string
  --
  +getId(): size_t
  +getNome(): string
  +getTelefone(): string
  +setNome(string)
  +setTelefone(string)
  {abstract} +exibir(ostream)
}

class Professor {
  -especialidade: string
  --
  +getEspecialidade(): string
  +setEspecialidade(string)
  +exibir(ostream)
}

class Aluno {
  -matricula: int
  -plano: Plano*
  -treinos: vector<Treino>
  --
  +getMatricula(): int
  +setPlano(Plano*)
  +adicionarTreino(Treino)
  +getTreinos(): vector<Treino>
  +exibir(ostream)
}

class Treinador {
  -especialidade: string
  --
  +adicionarAluno(Aluno)
  +removerAluno(string)
  +listarAlunos()
}

abstract class Plano {
  #descricao: string
  #valor: double
  #id: int
  --
  +getDescricao(): string
  +getValor(): double
  +setDescricao(string)
  +setValor(double)
  {abstract} +calcularValor(): double
}

class PlanoPersonalizado {
  -id: int
  --
  +calcularValor(): double
}

class Aula {
  -nome: string
  -professor: Professor*
  --
  +getNome(): string
  +getProfessor(): Professor*
  +setProfessor(Professor*)
}

class Modalidade {
  -nome: string
  --
  +getNome(): string
  +setNome(string)
}

class Treino {
  -nome: string
  -data: string
  -equipamentos: vector<Equipamento>
  --
  +getNome(): string
  +getData(): string
  +adicionarEquipamento(Equipamento)
  +getEquipamentos(): vector<Equipamento>
}

class Equipamento {
  -id: int
  -nome: string
  -quantidade: int
  --
  +getNome(): string
  +getQuantidade(): int
  +setQuantidade(int)
}

class Exercicio {
  -nome: string
  -grupoMuscular: string
  --
  +getNome(): string
  +getGrupoMuscular(): string
}

class Academia {
  -id: size_t
  -nome: string
  -maxAlunos: size_t
  -filiais: vector<Filial>
  --
  +getNome(): string
  +adicionarFilial(Filial)
  +getFiliais(): vector<Filial>
}

class Filial {
  -id: size_t
  -nome: string
  -endereco: string
  --
  +getNome(): string
  +getEndereco(): string
}

' ============ RELACIONAMENTOS ============

Gerenciador "1" o-- "*" Aluno : gerencia
Gerenciador "1" o-- "*" Professor : gerencia
Gerenciador "1" o-- "*" Plano : gerencia
Gerenciador "1" o-- "*" Equipamento : gerencia
Gerenciador "1" o-- "*" Academia : gerencia

Treinador "1" --> "*" Aluno : gerencia
Treinador "1" --> "*" Modalidade : ministra

Pessoa <|-- Professor
Pessoa <|-- Aluno
Pessoa <|-- Treinador

Aluno "1" --> "0..1" Plano : possui
Aluno "*" --> "*" Aula : participa
Aluno "1" *-- "*" Treino : possui

Plano <|-- PlanoPersonalizado

Professor "1" --> "*" Aula : leciona

Treino "*" o-- "*" Equipamento : utiliza
Treino "*" o-- "*" Exercicio : contém

Academia "1" *-- "*" Filial : possui

@enduml
```

## Descrição das Classes

### Interfaces
- **IIdentificavel**: Define métodos para objetos que possuem identificadores únicos
- **IFilePersistable**: Define métodos para persistência de dados em arquivos

### Hierarquia de Pessoas
- **Pessoa**: Classe base para todas as pessoas (id, nome, telefone)
- **Professor**: Estende Pessoa, adiciona especialidade
- **Aluno**: Estende Pessoa, adiciona matrícula, plano, treinos
- **Treinador**: Estende Pessoa, adiciona especialidade

### Planos
- **Plano**: Classe base para planos de academia
- **PlanoPersonalizado**: Estende Plano com características personalizadas

### Entidades Principais
- **Academia**: Representa uma academia de ginástica com múltiplas filiais
- **Filial**: Representa uma filial de uma academia
- **Aula**: Representa uma aula oferecida por um professor
- **Treino**: Representa um plano de treino com equipamentos
- **Equipamento**: Representa equipamentos disponíveis
- **Avaliacao**: Representa avaliações feitas por alunos

### Gerenciador
- **Gerenciador**: Classe central que gerencia todas as operações CRUD de todas as entidades
- Implementa persistência de dados em arquivos (bin/)
- Carrega dados automaticamente dos arquivos ao buscar entidades

## Persistência de Dados

Os arquivos de persistência estão em `bin/`:
- `alunos.txt` - Lista de alunos
- `professores.txt` - Lista de professores
- `planos.txt` - Lista de planos
- `planos_personalizados.txt` - Planos personalizados
- `aulas.txt` - Aulas oferecidas
- `equipamentos.txt` - Equipamentos disponíveis
- `avaliacoes.txt` - Avaliações realizadas
- `academias.txt` - Academias cadastradas
- `filiais.txt` - Filiais das academias
- `treinos.txt` - Treinos dos alunos

## Fluxo Principal

1. O programa começa no `main.cpp` com um menu interativo
2. O usuário escolhe uma opção para gerenciar diferentes entidades
3. O Gerenciador carrega dados dos arquivos conforme necessário
4. Operações CRUD são realizadas na memória
5. Mudanças são imediatamente persistidas nos arquivos
6. Dados são recarregados quando necessário garantir sincronização
