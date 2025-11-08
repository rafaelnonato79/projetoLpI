#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
  std::string nome;

public:
  void setNome(const std::string &n);
  std::string getNome() const;
};

#endif
