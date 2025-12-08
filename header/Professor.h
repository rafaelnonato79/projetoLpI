#pragma once
#include "Pessoa.h"
#include <ostream>
#include <string>

class Professor : public Pessoa {
private:
  std::string especialidade;

public:
  Professor(int id, const std::string &nome, const std::string &telefone,
            const std::string &especialidade);

  std::string getEspecialidade() const;
  void setEspecialidade(const std::string &e);

  void exibir(std::ostream &os) const override;

  void setNome(const std::string &n);
  void setTelefone(const std::string &t);
  void setId(size_t id) override;

  friend std::ostream &operator<<(std::ostream &os, const Professor &p);
};
