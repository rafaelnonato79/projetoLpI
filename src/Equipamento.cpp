#include "../header/Equipamento.h"

Equipamento::Equipamento(std::string nome, int quantidade)
    : nome(std::move(nome)), quantidade(quantidade) {}

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
