#pragma once
#include "Plano.h"
#include <string>

class PlanoPersonalizado : public Plano {
private:
  int id;

public:
  PlanoPersonalizado(const std::string &descricao, double valor);

  int getId() const;
  void setId(int i);

  double calcularValor() const;
};
