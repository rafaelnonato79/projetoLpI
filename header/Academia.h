#ifndef ACADEMIA_H
#define ACADEMIA_H

#include "Aluno.h"
#include "Plano.h"
#include "Treinador.h"
#include "Treino.h"
#include <string>
#include <vector>

class Academia {
  std::string nome;
  size_t maxAlunos;
  std::vector<Treinador *> treinadores;
  std::vector<Aluno *> alunos;
  std::vector<Treino *> treinos;
  std::vector<Plano *> planos;

public:
  Academia();
  Academia(const std::string &nome, size_t maxAlunos,
           const std::vector<Treinador *> &treinadores,
           const std::vector<Aluno *> &alunos,
           const std::vector<Treino *> &treinos,
           const std::vector<Plano *> &planos);

  void setAcademia(const std::string &nome, size_t maxAlunos,
                   const std::vector<Treinador *> &treinadores,
                   const std::vector<Aluno *> &alunos,
                   const std::vector<Treino *> &treinos,
                   const std::vector<Plano *> &planos);

  std::string getNome() const;
  void setNome(const std::string &nome);

  size_t getMaxAlunos() const;
  void setMaxAlunos(size_t maxAlunos);

  void adicionarTreinador(Treinador *treinador);
  void adicionarAluno(Aluno *aluno);
  void adicionarTreino(Treino *treino);
  void adicionarPlano(Plano *plano);

  bool removerTreinador(const std::string &nome);
  bool removerAluno(const std::string &nome);
  bool removerTreino(const std::string &nome);
  bool removerPlano(const std::string &nome);

  Treinador *buscarTreinador(const std::string &nome) const;
  Aluno *buscarAluno(const std::string &nome) const;
  Treino *buscarTreino(const std::string &nome) const;
  Plano *buscarPlano(const std::string &nome) const;
};

#endif
