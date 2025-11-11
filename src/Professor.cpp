#include "../header/Professor.h"

Professor::Professor(int id, const std::string &nome, const std::string &telefone, const std::string &especialidade)
    : Pessoa(id, nome, telefone), especialidade(especialidade) {}

std::string Professor::getEspecialidade() const { return especialidade; }

void Professor::exibir(std::ostream &os) const {
    Pessoa::exibir(os);
    os << " | Especialidade: " << especialidade;
}

void Professor::setEspecialidade(const std::string &e) { especialidade = e; }

void Professor::setNome(const std::string &n) { Pessoa::setNome(n); }

void Professor::setTelefone(const std::string &t) { Pessoa::setTelefone(t); }

void Professor::setId(int id) { Pessoa::setId(id); }

std::ostream &operator<<(std::ostream &os, const Professor &p) {
    p.exibir(os);
    return os;
}
