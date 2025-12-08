#pragma once
#include <string>

class Avaliacao {
private:
  static size_t nextId;
  size_t id;
  int alunoMatricula;
  std::string alvo; // e.g., "Professor", "Aula", "Academia"
  int nota;         // rating, e.g., 1-5
  std::string comentario;

public:
  Avaliacao(int alunoMatricula, const std::string &alvo, int nota,
            const std::string &comentario);

  size_t getId() const;
  int getAlunoMatricula() const;
  std::string getAlvo() const;
  int getNota() const;
  std::string getComentario() const;

  void setNota(int n);
  void setComentario(const std::string &c);
};
