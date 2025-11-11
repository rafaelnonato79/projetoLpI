#include "../header/PlanoPersonalizado.h"

PlanoPersonalizado::PlanoPersonalizado(double valor, const std::string &descricao) : Plano(descricao, valor) {}

double PlanoPersonalizado::calcularValor() const { return valor; }
