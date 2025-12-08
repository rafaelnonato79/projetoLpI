#pragma once
#include "IIndentificavel.h"
#include <ostream>
#include <string>

class Equipamento : public IIdentificavel {
private:
  int id;
  std::string nome;
  int quantidade;

public:
  Equipamento(std::string nome, int quantidade);

  std::string getNome() const;
  int getQuantidade() const;
  size_t getId() const override;

  void setId(size_t i) override;
  void setQuantidade(int q);
  void setNome(const std::string &n);

  Equipamento operator+(const Equipamento &o) const;

  friend std::ostream &operator<<(std::ostream &os, const Equipamento &e);
};
