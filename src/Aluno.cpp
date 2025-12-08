#include "../header/Aluno.h"
#include "../header/Plano.h"
#include "../header/Professor.h"
#include "../header/Treino.h"
#include <algorithm>

Aluno::Aluno(int matricula, const std::string &nome,
             const std::string &telefone)
    : Pessoa(matricula, nome, telefone), matricula(matricula) {}

Aluno::Aluno(const std::string &nome, const std::string &telefone)
    : Pessoa(0, nome, telefone), matricula(0) {}

int Aluno::getMatricula() const { return matricula; }

void Aluno::setPlano(Plano *p) { plano = p; }

Plano *Aluno::getPlano() const { return plano; }

void Aluno::adicionarTreino(const Treino &t) { treinos.push_back(t); }

const std::vector<Treino> &Aluno::getTreinos() const { return treinos; }

bool Aluno::operator==(const Aluno &o) const {
  return matricula == o.matricula;
}

bool Aluno::operator<(const Aluno &o) const { return getNome() < o.getNome(); }

void Aluno::exibir(std::ostream &os) const {
  Pessoa::exibir(os);
  os << " | Matricula: " << matricula;
  if (plano)
    os << " | Plano: " << plano->getDescricao();
  if (professor)
    os << " | Professor: " << professor->getNome();
}

void Aluno::matricularEmAula(const std::string &nomeAula) {
  aulasInscritas.push_back(nomeAula);
}

const std::vector<std::string> &Aluno::getAulasInscritas() const {
  return aulasInscritas;
}

void Aluno::setProfessor(Professor *p) { professor = p; }

Professor *Aluno::getProfessor() const { return professor; }

void Aluno::setMatricula(int m) {
  matricula = m;
  Pessoa::setId(m);
}

std::ostream &operator<<(std::ostream &os, const Aluno &a) {
  a.exibir(os);
  return os;
}
