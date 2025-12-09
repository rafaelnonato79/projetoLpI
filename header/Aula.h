#pragma once
#include "IFilePersistable.h"
#include <ostream>
#include <string>

class Professor; // Forward declaration

class Aula : public IFilePersistable {
private:
  std::string nome;
  Professor *professor;
  int professorId;

public:
  Aula();
  Aula(const std::string &nome, Professor *prof);
  ~Aula();

  void exibir(std::ostream &os) const;

  std::string getNome() const;
  Professor *getProfessor() const;
  void setProfessor(Professor *p);
  int getProfessorId() const;

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;

  friend std::ostream &operator<<(std::ostream &os, const Aula &a);
};
