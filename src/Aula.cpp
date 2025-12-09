#include "../header/Aula.h"
#include "../header/Professor.h"

Aula::Aula() : nome(""), professor(nullptr), professorId(0) {}

Aula::Aula(const std::string &nome, Professor *prof)
        : nome(nome), professor(prof),
            professorId(prof ? static_cast<int>(prof->getId()) : 0) {}

Aula::~Aula() = default;

void Aula::exibir(std::ostream &os) const {
    os << "Aula: " << nome;
    if (professor)
        os << " | Professor: " << professor->getNome();
}

std::string Aula::getNome() const { return nome; }

Professor *Aula::getProfessor() const { return professor; }

void Aula::setProfessor(Professor *p) {
    professor = p;
    professorId = p ? static_cast<int>(p->getId()) : 0;
}

int Aula::getProfessorId() const { return professorId; }

std::ostream &operator<<(std::ostream &os, const Aula &a) {
    a.exibir(os);
    return os;
}

std::string Aula::toFileString() const {
    return nome + ";" + std::to_string(getProfessorId());
}

bool Aula::fromFileString(const std::string &line) {
    size_t sep = line.find(';');
    if (sep == std::string::npos)
        return false;
    nome = line.substr(0, sep);
    try {
        professorId = std::stoi(line.substr(sep + 1));
    } catch (...) {
        professorId = 0;
    }
    professor = nullptr; // pointer resolved posteriormente
    return true;
}
