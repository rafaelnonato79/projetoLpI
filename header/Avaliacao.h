#pragma once
#include "IFilePersistable.h"
#include "IIndentificavel.h"
#include <string>

class Avaliacao : public IIdentificavel, public IFilePersistable {
private:
  static size_t nextId;
  size_t id;
  int alunoMatricula;
  std::string alvo; // e.g., "Professor", "Aula", "Academia"
  int nota;         // rating, e.g., 1-5
  std::string comentario;

public:
  Avaliacao();
  Avaliacao(int alunoMatricula, const std::string &alvo, int nota,
            const std::string &comentario);

  size_t getId() const override;
  void setId(size_t i) override;
  int getAlunoMatricula() const;
  std::string getAlvo() const;
  int getNota() const;
  std::string getComentario() const;

  void setNota(int n);
  void setComentario(const std::string &c);

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;
};
