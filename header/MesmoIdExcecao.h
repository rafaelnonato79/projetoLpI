#ifndef LIMITEALUNOSEXCEDIDO_H
#define LIMITEALUNOSEXCEDIDO_H

#include <exception>
#include <string>

class MesmoIdExcecao : public std::exception {
  std::string mensagem;

public:
  MesmoIdExcecao(const std::string &msg) : mensagem(msg) {}
  const char *what() const noexcept override { return mensagem.c_str(); }
};

#endif
