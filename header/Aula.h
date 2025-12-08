#pragma once
#include <ostream>
#include <string>

class Professor; // Forward declaration

class Aula {
private:
  std::string nome;
  Professor *professor;

public:
  Aula(const std::string &nome, Professor *prof);
  ~Aula();

  void exibir(std::ostream &os) const;

  std::string getNome() const;
  Professor *getProfessor() const;
  void setProfessor(Professor *p);

  friend std::ostream &operator<<(std::ostream &os, const Aula &a);
};
