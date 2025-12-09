#pragma once
#include "IFilePersistable.h"
#include "IIndentificavel.h"
#include <ostream>
#include <string>

class Equipamento : public IIdentificavel, public IFilePersistable {
private:
  int id;
  std::string nome;
  int quantidade;

public:
  Equipamento();
  Equipamento(std::string nome, int quantidade);

  std::string getNome() const;
  int getQuantidade() const;
  size_t getId() const override;

  void setId(size_t i) override;
  void setQuantidade(int q);
  void setNome(const std::string &n);

  Equipamento operator+(const Equipamento &o) const;

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;

  friend std::ostream &operator<<(std::ostream &os, const Equipamento &e);
};
