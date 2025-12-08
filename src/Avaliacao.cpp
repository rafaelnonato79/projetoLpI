#include "../header/Avaliacao.h"

size_t Avaliacao::nextId = 1;

Avaliacao::Avaliacao(int alunoMatricula, const std::string &alvo, int nota,
                     const std::string &comentario)
    : id(nextId++), alunoMatricula(alunoMatricula), alvo(alvo), nota(nota),
      comentario(comentario) {}

size_t Avaliacao::getId() const { return id; }

int Avaliacao::getAlunoMatricula() const { return alunoMatricula; }

std::string Avaliacao::getAlvo() const { return alvo; }

int Avaliacao::getNota() const { return nota; }

std::string Avaliacao::getComentario() const { return comentario; }

void Avaliacao::setNota(int n) { nota = n; }

void Avaliacao::setComentario(const std::string &c) { comentario = c; }
