#include "../header/Equipamento.h"

Equipamento::Equipamento() : id(0), nome(""), quantidade(0) {}

Equipamento::Equipamento(std::string nome, int quantidade)
  : id(0), nome(std::move(nome)), quantidade(quantidade) {}

std::string Equipamento::getNome() const { return nome; }

int Equipamento::getQuantidade() const { return quantidade; }

size_t Equipamento::getId() const { return id; }

void Equipamento::setId(size_t i) { id = i; }

void Equipamento::setQuantidade(int q) { quantidade = q; }

void Equipamento::setNome(const std::string &n) { nome = n; }

Equipamento Equipamento::operator+(const Equipamento &o) const {
  if (nome != o.nome)
    return *this; // se nomes diferentes, retorna cópia simples
  return Equipamento(nome, quantidade + o.quantidade);
}

std::ostream &operator<<(std::ostream &os, const Equipamento &e) {
  os << "ID:" << e.getId() << " " << e.getNome() << " (" << e.getQuantidade()
     << " repetições)";
  return os;
}

std::string Equipamento::toFileString() const {
  return std::to_string(getId()) + ";" + nome + ";" +
         std::to_string(quantidade);
}

bool Equipamento::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  try {
    id = static_cast<int>(std::stoul(line.substr(0, sep1)));
    nome = line.substr(sep1 + 1, sep2 - sep1 - 1);
    quantidade = std::stoi(line.substr(sep2 + 1));
  } catch (...) {
    return false;
  }
  return true;
}
