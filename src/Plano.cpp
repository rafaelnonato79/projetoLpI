#include "../header/Plano.h"
#include <iomanip>
#include <iostream>
#include <sstream>

Plano::Plano() : descricao(""), valor(0.0), id(0) {}

Plano::Plano(const std::string &descricao, double valor)
  : descricao(descricao), valor(valor), id(0) {}

Plano::~Plano() {}

std::string Plano::getDescricao() const { return descricao; }

void Plano::setDescricao(const std::string &d) { descricao = d; }

void Plano::setValor(double v) { valor = v; }

size_t Plano::getId() const { return id; }

void Plano::setId(size_t i) { id = i; }

std::string converterMoeda(double valor) {
  std::ostringstream oss;
  oss << "R$" << std::fixed << std::setprecision(2) << valor;
  return oss.str();
}

std::ostream &operator<<(std::ostream &os, const Plano &p) {
  os << "ID:" << p.getId() << " | Descricao: " << p.getDescricao()
     << " | Valor estimado: R$ " << p.calcularValor();
  return os;
}

void Plano::exibir(std::ostream &os) const {
  os << "ID:" << getId() << " | Descricao: " << getDescricao()
     << " | Valor estimado: R$ " << calcularValor();
}

std::string Plano::toFileString() const {
  return std::to_string(getId()) + ";" + descricao + ";" +
         std::to_string(valor);
}

bool Plano::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  try {
    id = static_cast<int>(std::stoul(line.substr(0, sep1)));
    descricao = line.substr(sep1 + 1, sep2 - sep1 - 1);
    valor = std::stod(line.substr(sep2 + 1));
  } catch (...) {
    return false;
  }
  return true;
}
