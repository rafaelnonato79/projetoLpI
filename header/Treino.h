#pragma once
#include "Equipamento.h"
#include <ostream>
#include <string>
#include <vector>

class Treino {
private:
  std::string nome;
  std::string data;
  std::vector<Equipamento> equipamentos;

public:
  Treino(const std::string &nome, const std::string &data);

  std::string getNome() const;
  std::string getData() const;

  void setNome(const std::string &n);
  void setData(const std::string &d);

  void adicionarEquipamento(const Equipamento &e);
  const std::vector<Equipamento> &getEquipamentos() const;

  Treino &operator+=(const Equipamento &e);

  bool removerEquipamentoPorNome(const std::string &nome);
  bool editarQuantidadeEquipamento(const std::string &nome, int novaQuantidade);

  friend std::ostream &operator<<(std::ostream &os, const Treino &t);
};
