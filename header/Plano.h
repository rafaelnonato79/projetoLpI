#ifndef PLANO_H
#define PLANO_H

#include <string>

class Plano {
protected:
  std::string nome;
  double precoBase;
  std::string descricao;

public:
  Plano();
  Plano(const std::string &nome, double precoBase,
        const std::string &descricao);
  virtual ~Plano() = default;

  void setNome(const std::string &nome);
  std::string getNome() const;

  void setPrecoBase(double preco);
  double getPrecoBase() const;

  void setDescricao(const std::string &descricao);
  std::string getDescricao() const;

  virtual double calcularPrecoFinal() const = 0;
};

class PlanoMensal : public Plano {
public:
  PlanoMensal(const std::string &nome, double precoBase,
              const std::string &descricao);
  double calcularPrecoFinal() const override;
};

class PlanoAnual : public Plano {
public:
  PlanoAnual(const std::string &nome, double precoBase,
             const std::string &descricao);
  double calcularPrecoFinal() const override;
};

#endif
