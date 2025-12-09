#pragma once
#include "IFilePersistable.h"
#include "IIndentificavel.h"
#include <string>

class Plano : public IIdentificavel, public IFilePersistable {
protected:
  std::string descricao;
  double valor;
  int id;

public:
  Plano();
  Plano(const std::string &descricao, double valor);
  virtual ~Plano();

  std::string getDescricao() const;
  double getValor() const;
  void setDescricao(const std::string &desc);
  void setValor(double v);
  size_t getId() const override;
  void setId(size_t i) override;
  virtual double calcularValor() const = 0;
  virtual void exibir(std::ostream &os) const;

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;
};
