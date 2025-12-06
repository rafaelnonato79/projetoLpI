#include "../header/PlanoPersonalizado.h"

PlanoPersonalizado::PlanoPersonalizado(const std::string &descricao, double valor) : Plano(descricao, valor) {}

int PlanoPersonalizado::getId() const { return id; }

void PlanoPersonalizado::setId(int i) { id = i; }

double PlanoPersonalizado::calcularValor() const { return Plano::valor; }
