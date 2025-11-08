#ifndef LIMITEALUNOSEXCEDIDO_H
#define LIMITEALUNOSEXCEDIDO_H

#include <exception>
#include <string>

class LimiteExcedido : public std::exception {
  std::string mensagem;

public:
  LimiteExcedido(const std::string &msg) : mensagem(msg) {}
  const char *what() const noexcept override { return mensagem.c_str(); }
};

#endif
