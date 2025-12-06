#include "../header/Plano.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Plano::Plano(const std::string &descricao, double valor) : descricao(descricao), valor(valor) {}

Plano::~Plano() {}

std::string Plano::getDescricao() const { return descricao; }

void Plano::setDescricao(const std::string &d) { descricao = d; }

void Plano::setValor(double v) { valor = v; }

int Plano::getId() const { return id; }

void Plano::setId(int i) { id = i; }

std::string converterMoeda(double valor){
	std::ostringstream oss;
	oss << "R$" << std::fixed << std::setprecision(2) << valor;
	return oss.str();
}

std::ostream &operator<<(std::ostream &os, const Plano &p) {
	os << "ID:" << p.getId() << " | Descricao: " << p.getDescricao() << " | Valor estimado: R$ " << p.calcularValor();
	return os;
}



