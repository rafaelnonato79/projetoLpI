#pragma once
#include "Filial.h"
#include "Pessoa.h"
#include "Plano.h"
#include "Professor.h"
#include "Treino.h"
#include <ostream>
#include <string>
#include <vector>

class Aluno : public Pessoa {
private:
  int matricula;
  Plano *plano = nullptr;
  Professor *professor = nullptr;
  Filial *filial = nullptr;
  std::vector<Treino> treinos;
  std::vector<std::string> aulasInscritas;

public:
  Aluno(); // Default constructor needed for file operations
  Aluno(int matricula, const std::string &nome, const std::string &telefone);
  Aluno(const std::string &nome, const std::string &telefone);

  int getMatricula() const;
  void setMatricula(int m);

  void setPlano(Plano *p);
  Plano *getPlano() const;

  void adicionarTreino(const Treino &t);
  const std::vector<Treino> &getTreinos() const;

  void matricularEmAula(const std::string &nomeAula);
  const std::vector<std::string> &getAulasInscritas() const;

  void setProfessor(Professor *p);
  Professor *getProfessor() const;

  void setFilial(Filial *f); // Link aluno to one filial
  Filial *getFilial() const; // Get linked filial

  bool operator==(const Aluno &o) const;
  bool operator<(const Aluno &o) const;

  void exibir(std::ostream &os) const override;

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;

  friend std::ostream &operator<<(std::ostream &os, const Aluno &a);
};
