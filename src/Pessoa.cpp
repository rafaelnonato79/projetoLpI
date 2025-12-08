#include "../header/Pessoa.h"

Pessoa::Pessoa(int id, const std::string &nome, const std::string &telefone)
    : id(id), nome(nome), telefone(telefone) {}

Pessoa::Pessoa() : id(0), nome(""), telefone("") {}

Pessoa::~Pessoa() {}

int Pessoa::getId() const { return id; }

void Pessoa::setId(int novo) { id = novo; }

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
