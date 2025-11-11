#include "../header/Aula.h"
#include "../header/Professor.h"

Aula::Aula(const std::string &nome, Professor *prof) : nome(nome), professor(prof) {}

Aula::~Aula() = default;

void Aula::exibir(std::ostream &os) const {
    os << "Aula: " << nome;
    if (professor) os << " | Professor: " << professor->getNome();
}

std::string Aula::getNome() const { return nome; }

Professor *Aula::getProfessor() const { return professor; }

void Aula::setProfessor(Professor *p) { professor = p; }

std::ostream &operator<<(std::ostream &os, const Aula &a) {
    a.exibir(os);
    return os;
}
