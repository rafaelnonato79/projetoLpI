#pragma once
#include <ostream>
#include <string>

class Pessoa {
private:
  int id;
  std::string nome;
  std::string telefone;

public:
  Pessoa();
  Pessoa(int id, const std::string &nome, const std::string &telefone);

  int getId() const;
  std::string getNome() const;
  std::string getTelefone() const;

  void setId(int id);
  void setNome(const std::string &n);
  void setTelefone(const std::string &t);

  virtual void exibir(std::ostream &os) const;

  virtual ~Pessoa();
};
