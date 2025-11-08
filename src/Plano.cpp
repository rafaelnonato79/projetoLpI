#include "../header/Plano.h"

Plano::Plano() : nome(""), precoBase(0.0), descricao("") {}

Plano::Plano(const std::string &nome, double precoBase,
             const std::string &descricao)
    : nome(nome), precoBase(precoBase), descricao(descricao) {}

void Plano::setNome(const std::string &nome) { this->nome = nome; }

std::string Plano::getNome() const { return nome; }

void Plano::setPrecoBase(double preco) { this->precoBase = preco; }

double Plano::getPrecoBase() const { return precoBase; }

void Plano::setDescricao(const std::string &descricao) {
  this->descricao = descricao;
}

std::string Plano::getDescricao() const { return descricao; }

PlanoMensal::PlanoMensal(const std::string &nome, double precoBase,
                         const std::string &descricao)
    : Plano(nome, precoBase, descricao) {}

double PlanoMensal::calcularPrecoFinal() const { return precoBase; }

PlanoAnual::PlanoAnual(const std::string &nome, double precoBase,
                       const std::string &descricao)
    : Plano(nome, precoBase, descricao) {}

double PlanoAnual::calcularPrecoFinal() const { return precoBase * 12 * 0.9; }
