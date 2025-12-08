#pragma once
#include "Aluno.h"
#include "Aula.h"
#include "Equipamento.h"
#include "Plano.h"
#include "PlanoPersonalizado.h"
#include "Professor.h"
#include <memory>
#include <string>
#include <vector>

class Gerenciador {
private:
  std::string nomeAcademia;
  int maxAlunos = 0;
  int nextAlunoMatricula = 1;
  int nextProfessorId = 1;
  int nextPlanoId = 1;
  int nextEquipamentoId = 1;

  std::vector<Aluno> alunos;
  std::vector<Professor> professores;
  std::vector<std::shared_ptr<Plano>> planos;
  std::vector<std::shared_ptr<Aula>> aulas;
  std::vector<Equipamento> equipamentos;
  std::vector<std::string> horarios;

public:
  // Alunos
  void adicionarAluno(const Aluno &a);
  void listarAlunos() const;
  Aluno *buscarAlunoPorMatricula(int matricula);
  void removerAluno(int matricula);
  void matricularAlunoEmAula(int matricula, const std::string &nomeAula);

  // Professores
  void adicionarProfessor(const Professor &p);
  void listarProfessores() const;
  void removerProfessor(int id);
  Professor *buscarProfessorPorId(int id);

  // Planos
  void adicionarPlano(std::shared_ptr<Plano> p);
  void listarPlanos() const;
  void adicionarPlanoPersonalizado(const std::string &descricao, double valor);
  std::shared_ptr<Plano> buscarPlanoPorDescricao(const std::string &descricao);
  std::shared_ptr<Plano> buscarPlanoPorId(int id) const;
  void removerPlanoPorId(int id);
  bool editarPlano(int idPlano, const std::string &novaDescricao,
                   double novoValor);

  // Aulas
  void adicionarAula(std::shared_ptr<Aula> a);
  void listarAulas() const;
  void removerAula(const std::string &nome);
  std::shared_ptr<Aula> buscarAulaPorNome(const std::string &nome) const;
  std::shared_ptr<Aula> atribuirProfessorAAula(int idProfessor,
                                               const std::string &nomeAula);

  // Equipamentos
  void adicionarEquipamento(const Equipamento &e);
  void listarEquipamentos() const;
  void removerEquipamento(const std::string &nome);
  Equipamento *buscarEquipamentoPorNome(const std::string &nome);
  Equipamento *buscarEquipamentoPorId(int id);

  // Academia info
  void setNomeAcademia(const std::string &nome);
  std::string getNomeAcademia() const;
  void adicionarHorario(const std::string &horario);
  void setMaxAlunos(int max);
  int getMaxAlunos() const;
  void listarHorarios() const;

  // Professores <-> Aulas/Alunos
  std::vector<std::string> listarAulasDoProfessor(int id) const;
  std::vector<Aluno> listarAlunosDoProfessor(int id) const;
};
