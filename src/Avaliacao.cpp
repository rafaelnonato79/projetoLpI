#include "../header/Avaliacao.h"

size_t Avaliacao::nextId = 1;

Avaliacao::Avaliacao()
    : id(nextId++), alunoMatricula(0), alvo(""), nota(0), comentario("") {}

Avaliacao::Avaliacao(int alunoMatricula, const std::string &alvo, int nota,
                     const std::string &comentario)
    : id(nextId++), alunoMatricula(alunoMatricula), alvo(alvo), nota(nota),
      comentario(comentario) {}

size_t Avaliacao::getId() const { return id; }
void Avaliacao::setId(size_t i) { id = i; }

int Avaliacao::getAlunoMatricula() const { return alunoMatricula; }

std::string Avaliacao::getAlvo() const { return alvo; }

int Avaliacao::getNota() const { return nota; }

std::string Avaliacao::getComentario() const { return comentario; }

void Avaliacao::setNota(int n) { nota = n; }

void Avaliacao::setComentario(const std::string &c) { comentario = c; }

std::string Avaliacao::toFileString() const {
  return std::to_string(id) + ";" + std::to_string(alunoMatricula) + ";" +
         alvo + ";" + std::to_string(nota) + ";" + comentario;
}

bool Avaliacao::fromFileString(const std::string &line) {
  size_t s1 = line.find(';');
  if (s1 == std::string::npos)
    return false;
  size_t s2 = line.find(';', s1 + 1);
  if (s2 == std::string::npos)
    return false;
  size_t s3 = line.find(';', s2 + 1);
  if (s3 == std::string::npos)
    return false;
  size_t s4 = line.find(';', s3 + 1);
  if (s4 == std::string::npos)
    return false;
  try {
    id = std::stoul(line.substr(0, s1));
    alunoMatricula = std::stoi(line.substr(s1 + 1, s2 - s1 - 1));
    alvo = line.substr(s2 + 1, s3 - s2 - 1);
    nota = std::stoi(line.substr(s3 + 1, s4 - s3 - 1));
    comentario = line.substr(s4 + 1);
    if (id >= nextId)
      nextId = id + 1;
  } catch (...) {
    return false;
  }
  return true;
}
