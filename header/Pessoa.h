#pragma once
#include "IIndentificavel.h"
#include <ostream>
#include <string>

class Pessoa : public IIdentificavel {
private:
  int id;
  std::string nome;
  std::string telefone;

public:
  Pessoa();
  Pessoa(int id, const std::string &nome, const std::string &telefone);

  size_t getId() const override;
  std::string getNome() const;
  std::string getTelefone() const;

  void setId(size_t id) override;
  void setNome(const std::string &n);
  void setTelefone(const std::string &t);

  virtual void exibir(std::ostream &os) const;

  virtual ~Pessoa();
};
