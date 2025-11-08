#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>

class Modalidade {
  std::string modalidade;

public:
  Modalidade();
  Modalidade(const std::string &modalidade);

  void setModalidade(const std::string &modalidade);
  std::string getModalidade() const;

  static bool deletarModalidade(std::vector<Modalidade *> &modalidades,
                                const std::string &modalidade);
  static bool atualizarModalidade(std::vector<Modalidade *> &modalidades,
                                  const std::string &modalidade,
                                  const std::string &novaModalidade);
};

#endif
