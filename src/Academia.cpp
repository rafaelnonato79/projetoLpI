#include "../header/Academia.h"
#include <algorithm>

size_t Academia::nextId = 1;

Academia::Academia() : id(0), nome(""), maxAlunos(0) {}

Academia::Academia(const std::string &nome, size_t maxAlunos)
    : nome(nome), maxAlunos(maxAlunos) {}

std::string Academia::getNome() const { return nome; }

void Academia::setNome(const std::string &n) { nome = n; }
unsigned long Academia::getMaxAlunos() const { return maxAlunos; }

void Academia::setMaxAlunos(unsigned long max) { maxAlunos = max; }

size_t Academia::getId() const { return id; }
void Academia::setId(size_t i) { id = i; }

const std::vector<Filial> &Academia::getFiliais() const { return filiais; }

Filial *Academia::buscarFilialPorId(size_t filialId) {
  for (auto &f : filiais)
    if (f.getId() == filialId)
      return &f;
  return nullptr;
}

void Academia::adicionarFilial(const Filial &f) { filiais.push_back(f); }

void Academia::removerFilial(size_t filialId) {
  auto it =
      std::remove_if(filiais.begin(), filiais.end(),
                     [&](const Filial &f) { return f.getId() == filialId; });
  if (it != filiais.end())
    filiais.erase(it, filiais.end());
}

std::string Academia::toFileString() const {
  return std::to_string(id) + ";" + nome + ";" + std::to_string(maxAlunos);
}

bool Academia::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  try {
    id = std::stoul(line.substr(0, sep1));
    nome = line.substr(sep1 + 1, sep2 - sep1 - 1);
    maxAlunos = std::stoul(line.substr(sep2 + 1));
  } catch (...) {
    return false;
  }
  return true;
}
