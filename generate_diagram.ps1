# Script para gerar PNG do diagrama UML no Windows

# Verifica se Java está instalado (necessário para PlantUML)
try {
    $javaVersion = java -version 2>&1
    Write-Host "✓ Java encontrado"
} catch {
    Write-Host "✗ Java não está instalado!"
    Write-Host "Visite: https://www.oracle.com/java/technologies/downloads/"
    exit 1
}

# Verifica se PlantUML está instalado
$plantUmlPath = "C:\Program Files\PlantUML\plantuml.jar"
if (-not (Test-Path $plantUmlPath)) {
    # Tenta encontrar em outros locais comuns
    $possiblePaths = @(
        "C:\Program Files (x86)\PlantUML\plantuml.jar",
        "$env:APPDATA\PlantUML\plantuml.jar",
        "C:\plantuml\plantuml.jar"
    )
    
    $found = $false
    foreach ($path in $possiblePaths) {
        if (Test-Path $path) {
            $plantUmlPath = $path
            $found = $true
            break
        }
    }
    
    if (-not $found) {
        Write-Host "✗ PlantUML não está instalado!"
        Write-Host ""
        Write-Host "Para instalar PlantUML no Windows:"
        Write-Host "1. Visite: https://plantuml.com/download"
        Write-Host "2. Baixe o plantuml.jar"
        Write-Host "3. Coloque em C:\Program Files\PlantUML\ ou atualize o caminho no script"
        exit 1
    }
}

Write-Host "✓ PlantUML encontrado em: $plantUmlPath"

# Cria arquivo temporário com o código PlantUML
$diagramContent = @'
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
  -alunos: vector<Aluno>
  -professores: vector<Professor>
  -planos: vector<shared_ptr<Plano>>
  -aulas: vector<shared_ptr<Aula>>
  -equipamentos: vector<Equipamento>
  -academias: vector<Academia>
  -avaliacoes: vector<Avaliacao>
  --
  +adicionarAluno(a, filial): void
  +listarAlunos(): void
  +adicionarProfessor(p): void
  +adicionarPlano(p): void
  +adicionarEquipamento(e): void
  +adicionarTreinoAoAluno(matricula, treino): void
  +adicionarAvaliacao(a): void
}

' ============ RELACIONAMENTOS ============

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
'@

# Salva o arquivo temporário
$tempFile = "$env:TEMP\academia_diagram.puml"
$diagramContent | Out-File -FilePath $tempFile -Encoding UTF8

Write-Host "Gerando PNG do diagrama..."

# Executa PlantUML
java -jar $plantUmlPath -tpng -o $PSScriptRoot $tempFile

# Verifica se foi gerado com sucesso
$outputFile = "$PSScriptRoot\academia_diagram.png"
if (Test-Path $outputFile) {
    # Renomeia para DIAGRAMA_UML.png
    Rename-Item -Path $outputFile -NewName "DIAGRAMA_UML.png" -Force
    Write-Host "✓ PNG gerado com sucesso: DIAGRAMA_UML.png"
    
    # Remove arquivo temporário
    Remove-Item -Path $tempFile -Force
    
    # Abre a imagem no visualizador padrão
    Start-Process DIAGRAMA_UML.png
} else {
    Write-Host "✗ Erro ao gerar PNG"
    Write-Host "Verifique se o PlantUML está instalado corretamente."
    exit 1
}
