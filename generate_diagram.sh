#!/bin/bash
# Script para gerar PNG do diagrama UML

# Verifica se PlantUML está instalado
if ! command -v plantuml &> /dev/null; then
    echo "PlantUML não está instalado!"
    echo "Para instalar no Linux: sudo apt-get install plantuml"
    echo "Para instalar no macOS: brew install plantuml"
    echo "Para Windows: visite https://plantuml.com/download"
    exit 1
fi

# Extrai o conteúdo PlantUML do arquivo markdown
echo "Gerando PNG do diagrama UML..."

# Cria arquivo temporário com o código PlantUML
cat > /tmp/academia_diagram.puml << 'EOF'
@startuml Academia_System

skinparam backgroundColor #FEFEFE
skinparam classBackgroundColor #F0F0F0
skinparam classBorderColor #333333

' ============ INTERFACES ============

interface IIdentificavel {
  {abstract} +getId(): size_t
  {abstract} +setId(id: size_t): void
}

interface IFilePersistable {
  {abstract} +toFileString(): string
  {abstract} +fromFileString(line: string): bool
}

' ============ CLASSES BASE ============

class Pessoa {
  -id: int
  -nome: string
  -telefone: string
  --
  +Pessoa()
  +Pessoa(id, nome, telefone)
  +getId(): size_t
  +getNome(): string
  +getTelefone(): string
  +setId(id): void
  +setNome(n): void
  +setTelefone(t): void
  +exibir(os): void
  +toFileString(): string
  +fromFileString(line): bool
  +~Pessoa()
}

' ============ HERANÇA DE PESSOA ============

class Professor {
  -especialidade: string
  --
  +Professor()
  +Professor(id, nome, telefone, especialidade)
  +getEspecialidade(): string
  +setEspecialidade(e): void
  +exibir(os): void
  +toFileString(): string
  +fromFileString(line): bool
}

class Aluno {
  -matricula: int
  -plano: Plano*
  -professor: Professor*
  -filial: Filial*
  -treinos: vector<Treino>
  -aulasInscritas: vector<string>
  --
  +Aluno()
  +Aluno(matricula, nome, telefone)
  +getMatricula(): int
  +setMatricula(m): void
  +setPlano(p): void
  +getPlano(): Plano*
  +adicionarTreino(t): void
  +getTreinos(): vector<Treino>
  +matricularEmAula(nomeAula): void
  +getAulasInscritas(): vector<string>
  +setProfessor(p): void
  +getProfessor(): Professor*
  +setFilial(f): void
  +getFilial(): Filial*
  +operator==(): bool
  +operator<(): bool
  +exibir(os): void
  +toFileString(): string
  +fromFileString(line): bool
}

class Treinador {
  -especialidade: string
  --
  +Treinador()
  +Treinador(id, nome, telefone, especialidade)
  +getEspecialidade(): string
  +setEspecialidade(e): void
  +exibir(os): void
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ PLANOS ============

class Plano {
  -descricao: string
  -valor: double
  -id: int
  --
  +Plano()
  +Plano(descricao, valor)
  +getDescricao(): string
  +getValor(): double
  +setDescricao(desc): void
  +setValor(v): void
  +getId(): size_t
  +setId(i): void
  +calcularValor(): double
  +exibir(os): void
  +toFileString(): string
  +fromFileString(line): bool
}

class PlanoPersonalizado {
  -id: int
  --
  +PlanoPersonalizado()
  +PlanoPersonalizado(descricao, valor)
  +getId(): size_t
  +setId(i): void
  +calcularValor(): double
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ TREINO E EQUIPAMENTO ============

class Treino {
  -nome: string
  -data: string
  -equipamentos: vector<Equipamento>
  --
  +Treino()
  +Treino(nome, data)
  +getNome(): string
  +getData(): string
  +setNome(n): void
  +setData(d): void
  +adicionarEquipamento(e): void
  +getEquipamentos(): vector<Equipamento>
  +operator+=(): Treino&
  +removerEquipamentoPorNome(nome): bool
  +editarQuantidadeEquipamento(nome, qtd): bool
  +toFileString(): string
  +fromFileString(line): bool
}

class Equipamento {
  -id: int
  -nome: string
  -quantidade: int
  --
  +Equipamento()
  +Equipamento(nome, quantidade)
  +getNome(): string
  +getQuantidade(): int
  +getId(): size_t
  +setId(i): void
  +setQuantidade(q): void
  +setNome(n): void
  +operator+(): Equipamento
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ AULA ============

class Aula {
  -nome: string
  -professor: Professor*
  -professorId: int
  --
  +Aula()
  +Aula(nome, prof)
  +exibir(os): void
  +getNome(): string
  +getProfessor(): Professor*
  +setProfessor(p): void
  +getProfessorId(): int
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ AVALIAÇÃO ============

class Avaliacao {
  -{static} nextId: size_t
  -id: size_t
  -alunoMatricula: int
  -alvo: string
  -nota: int
  -comentario: string
  --
  +Avaliacao()
  +Avaliacao(matricula, alvo, nota, comentario)
  +getId(): size_t
  +setId(i): void
  +getAlunoMatricula(): int
  +getAlvo(): string
  +getNota(): int
  +getComentario(): string
  +setNota(n): void
  +setComentario(c): void
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ ACADEMIA E FILIAL ============

class Academia {
  -{static} nextId: size_t
  -id: size_t
  -nome: string
  -maxAlunos: size_t
  -treinadores: vector<Treinador*>
  -alunos: vector<Aluno*>
  -treinos: vector<Treino*>
  -planos: vector<Plano*>
  -filiais: vector<Filial>
  --
  +Academia()
  +Academia(nome, maxAlunos)
  +getId(): size_t
  +setId(i): void
  +getNome(): string
  +setNome(n): void
  +getMaxAlunos(): size_t
  +setMaxAlunos(max): void
  +adicionarFilial(f): void
  +buscarFilialPorId(id): Filial*
  +getFiliais(): vector<Filial>
  +toFileString(): string
  +fromFileString(line): bool
}

class Filial {
  -{static} nextId: size_t
  -academiaId: size_t
  -id: size_t
  -nome: string
  -endereco: string
  --
  +Filial()
  +Filial(nome, endereco)
  +Filial(academiaId, nome, endereco)
  +getId(): size_t
  +setId(i): void
  +getAcademiaId(): size_t
  +setAcademiaId(i): void
  +getNome(): string
  +setNome(n): void
  +getEndereco(): string
  +setEndereco(e): void
  +toFileString(): string
  +fromFileString(line): bool
}

' ============ GERENCIADOR ============

class Gerenciador {
  -nomeAcademia: string
  -id: size_t
  -maxAlunos: int
  -nextAcademiaId: int
  -nextAlunoMatricula: int
  -nextProfessorId: int
  -nextPlanoId: int
  -nextEquipamentoId: int
  -alunos: vector<Aluno>
  -professores: vector<Professor>
  -planos: vector<shared_ptr<Plano>>
  -aulas: vector<shared_ptr<Aula>>
  -equipamentos: vector<Equipamento>
  -horarios: vector<string>
  -academias: vector<Academia>
  -avaliacoes: vector<Avaliacao>
  --
  +adicionarAluno(a, filial): void
  +listarAlunos(): void
  +buscarAlunoPorMatricula(matricula): Aluno*
  +adicionarProfessor(p): void
  +adicionarPlano(p): void
  +adicionarEquipamento(e): void
  +adicionarTreinoAoAluno(matricula, treino): void
  +adicionarAvaliacao(a): void
}

' ============ EXCEÇÕES ============

class ValidationError {
}

class NotFound {
}

class DuplicateEntry {
}

' ============ INTERFACES IMPLEMENTADAS ============

Pessoa ..|> IIdentificavel
Pessoa ..|> IFilePersistable

Professor --|> Pessoa
Aluno --|> Pessoa
Treinador --|> Pessoa

Plano ..|> IIdentificavel
Plano ..|> IFilePersistable

PlanoPersonalizado --|> Plano

Equipamento ..|> IIdentificavel
Equipamento ..|> IFilePersistable

Treino ..|> IFilePersistable

Aula ..|> IFilePersistable

Avaliacao ..|> IIdentificavel
Avaliacao ..|> IFilePersistable

Academia ..|> IFilePersistable

Filial ..|> IIdentificavel
Filial ..|> IFilePersistable

' ============ RELACIONAMENTOS ============

Aluno *-- "0..*" Treino : contém
Aluno --> "0..1" Plano : utiliza
Aluno --> "0..1" Professor : vinculado_a
Aluno --> "0..1" Filial : matriculado_em

Professor "1" --> "*" Aula : leciona

Aula --> "0..1" Professor : lecionada_por

Treino *-- "0..*" Equipamento : utiliza

Academia *-- "1..*" Filial : possui
Academia "1" --> "*" Aluno : contém
Academia "1" --> "*" Treinador : emprega
Academia "1" --> "*" Plano : oferece

Gerenciador "1" --> "*" Aluno : gerencia
Gerenciador "1" --> "*" Professor : gerencia
Gerenciador "1" --> "*" Plano : gerencia
Gerenciador "1" --> "*" Aula : gerencia
Gerenciador "1" --> "*" Equipamento : gerencia
Gerenciador "1" --> "*" Academia : gerencia
Gerenciador "1" --> "*" Avaliacao : gerencia
Gerenciador "1" --> "*" Treino : gerencia

Avaliacao --> "0..1" Aluno : avalia

@enduml
EOF

# Gera o PNG
plantuml /tmp/academia_diagram.puml -o /tmp

# Move para o diretório do projeto
if [ -f "/tmp/academia_diagram.png" ]; then
    cp /tmp/academia_diagram.png ./DIAGRAMA_UML.png
    echo "✓ PNG gerado com sucesso: DIAGRAMA_UML.png"
    rm /tmp/academia_diagram.puml
    rm /tmp/academia_diagram.png
else
    echo "✗ Erro ao gerar PNG"
    exit 1
fi
