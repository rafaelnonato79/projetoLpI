#include "../header/PlanoPersonalizado.h"

PlanoPersonalizado::PlanoPersonalizado(const std::string &descricao,
                                       double valor)
    : Plano(descricao, valor) {}

size_t PlanoPersonalizado::getId() const { return id; }

void PlanoPersonalizado::setId(size_t i) { id = i; }

double PlanoPersonalizado::calcularValor() const { return Plano::valor; }
