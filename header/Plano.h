#pragma once
#include <string>

class Plano {
protected:
  std::string descricao;
  double valor;
  int id;

public:
  Plano(const std::string &descricao, double valor);
  virtual ~Plano();

  std::string getDescricao() const;
  double getValor() const;
  void setDescricao(const std::string &desc);
  void setValor(double v);
  int getId() const;
  void setId(int i);
  virtual double calcularValor() const;
  virtual void exibir(std::ostream &os) const;
};
