#include "../header/Professor.h"

Professor::Professor() : Pessoa(), especialidade("") {}

Professor::Professor(int id, const std::string &nome,
           const std::string &telefone,
           const std::string &especialidade)
  : Pessoa(id, nome, telefone), especialidade(especialidade) {}

std::string Professor::getEspecialidade() const { return especialidade; }

void Professor::exibir(std::ostream &os) const {
  os << "ID: " << getId() << " | Nome: " << getNome() << " | Telefone: " << getTelefone();
  os << " | Especialidade: " << especialidade;
}

void Professor::setEspecialidade(const std::string &e) { especialidade = e; }

void Professor::setNome(const std::string &n) { Pessoa::setNome(n); }

void Professor::setTelefone(const std::string &t) { Pessoa::setTelefone(t); }

void Professor::setId(size_t id) { Pessoa::setId(id); }

std::ostream &operator<<(std::ostream &os, const Professor &p) {
  p.exibir(os);
  return os;
}

std::string Professor::toFileString() const {
  return std::to_string(getId()) + ";" + getNome() + ";" + getTelefone() +
         ";" + especialidade;
}

bool Professor::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  size_t sep3 = line.find(';', sep2 + 1);
  if (sep3 == std::string::npos)
    return false;
  try {
    setId(std::stoul(line.substr(0, sep1)));
    setNome(line.substr(sep1 + 1, sep2 - sep1 - 1));
    setTelefone(line.substr(sep2 + 1, sep3 - sep2 - 1));
    especialidade = line.substr(sep3 + 1);
  } catch (...) {
    return false;
  }
  return true;
}
