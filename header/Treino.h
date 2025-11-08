
#ifndef TREINO_H
#define TREINO_H

#include "Modalidade.h"
#include <string>
#include <vector>

class Treino {
  std::string nome;
  std::vector<class Exercicio *> exercicios;
  Modalidade *modalidade;

public:
  Treino();
  Treino(const std::string &nome, std::vector<class Exercicio *> exercicios,
         class Modalidade *modalidade);

  void setNome(const std::string &nome);
  std::string getNome() const;

  void setExercicios(const std::vector<class Exercicio *> &exercicios);
  const std::vector<class Exercicio *> &getExercicios() const;

  void setModalidade(class Modalidade *modalidade);
  class Modalidade *getModalidade() const;

  static bool deletarTreino(std::vector<Treino *> &treino,
                            const std::string &nome);
  static bool atualizarTreino(std::vector<Treino *> &treino,
                              const std::string &nome,
                              const std::string &novoNome,
                              std::vector<class Exercicio *> exercicios,
                              class Modalidade *modalidade);
};

#endif
