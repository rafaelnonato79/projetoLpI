#pragma once
#include "Plano.h"
#include <string>

class PlanoPersonalizado : public Plano {
private:
  int id;

public:
  PlanoPersonalizado();
  PlanoPersonalizado(const std::string &descricao, double valor);

  size_t getId() const override;
  void setId(size_t i) override;

  double calcularValor() const override;

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;
};
