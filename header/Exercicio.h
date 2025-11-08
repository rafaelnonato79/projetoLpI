#ifndef EXERCICIO_H
#define EXERCICIO_H

#include <string>
#include <vector>

using namespace std;

class Exercicio {
  string exercicio;

public:
  Exercicio();
  Exercicio(const string &exercicio);

  void setExercicio(const string &exercicio);
  string getExercicio() const;

  static bool deletarExercicio(vector<Exercicio *> &exercicios,
                               const string &exercicio);
  static bool atualizarExercicio(vector<Exercicio *> &exercicios,
                                 const string &exercicio,
                                 const string &novoExercicio);
};

#endif
