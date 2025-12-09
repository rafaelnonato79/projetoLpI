#include "../header/Pessoa.h"

Pessoa::Pessoa(int id, const std::string &nome, const std::string &telefone)
    : id(id), nome(nome), telefone(telefone) {}

Pessoa::Pessoa() : id(0), nome(""), telefone("") {}

Pessoa::~Pessoa() {}

size_t Pessoa::getId() const { return id; }

void Pessoa::setId(size_t novo) { id = novo; }

std::string Pessoa::getNome() const { return nome; }

std::string Pessoa::getTelefone() const { return telefone; }

void Pessoa::setNome(const std::string &novo) { nome = novo; }

void Pessoa::setTelefone(const std::string &novo) { telefone = novo; }

void Pessoa::exibir(std::ostream &os) const {
  os << "ID: " << id << " | Nome: " << nome << " | Telefone: " << telefone;
}

std::ostream &operator<<(std::ostream &os, const Pessoa &p) {
  p.exibir(os);
  return os;
}

std::string Pessoa::toFileString() const {
  return std::to_string(id) + ";" + nome + ";" + telefone;
}

bool Pessoa::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  try {
    id = static_cast<int>(std::stoul(line.substr(0, sep1)));
    nome = line.substr(sep1 + 1, sep2 - sep1 - 1);
    telefone = line.substr(sep2 + 1);
  } catch (...) {
    return false;
  }
  return true;
}
