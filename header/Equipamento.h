#pragma once
#include <ostream>
#include <string>

class Equipamento {
private:
  int id;
  std::string nome;
  int quantidade;

public:
  Equipamento(std::string nome, int quantidade);

  std::string getNome() const;
  int getQuantidade() const;
  int getId() const;

  void setId(int i);
  void setQuantidade(int q);
  void setNome(const std::string &n);

  Equipamento operator+(const Equipamento &o) const;

  friend std::ostream &operator<<(std::ostream &os, const Equipamento &e);
};
