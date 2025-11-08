#ifndef TREINADOR_H
#define TREINADOR_H

#include "Modalidade.h"
#include "Pessoa.h"

#include <string>
#include <vector>

class Aluno;

class Treinador : public Pessoa {
  Modalidade *modalidade;
  std::vector<Aluno *> alunos;

public:
  Treinador();
  Treinador(const std::string &nome, Modalidade *modalidade);

  void setModalidade(Modalidade *mod);
  Modalidade *getModalidade() const;

  void adicionarAluno(Aluno *aluno);
  void removerAluno(Aluno *aluno);

  static Treinador *buscarTreinador(const std::vector<Treinador *> &treinadores,
                                    const std::string &nome);

  const std::vector<Aluno *> &getAlunos() const;

  static bool atualizarTreinador(std::vector<Treinador *> &treinadores,
                                 const std::string &nome,
                                 Modalidade *novaModalidade);
  static bool deletarTreinador(std::vector<Treinador *> &treinadores,
                               const std::string &nome);
};

#endif
