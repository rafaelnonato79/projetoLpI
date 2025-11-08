#ifndef ALUNO_H
#define ALUNO_H

#include "Treinador.h"
#include "Treino.h"
#include <string>
#include <vector>

using namespace std;

class Aluno : public Pessoa {
  Treinador *treinador;
  Treino *treino;

public:
  Aluno();
  Aluno(const string &nome, Treinador *treinador, Treino *treino);

  static bool deletarAluno(vector<Aluno *> &alunos, const string &nome);
  static bool atualizarAluno(vector<Aluno *> &alunos, const string &nome,
                             const string &novoNome, Treinador *treinador,
                             Treino *treino);
};

#endif
