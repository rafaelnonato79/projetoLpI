#include "../header/Filial.h"

size_t Filial::nextId = 1;

Filial::Filial() : academiaId(0), id(0), nome(""), endereco("") {}

Filial::Filial(const std::string &nome, const std::string &endereco)
    : nome(nome), endereco(endereco) {}
Filial::Filial(size_t academiaId, const std::string &nome,
               const std::string &endereco)
    : academiaId(academiaId), nome(nome), endereco(endereco) {}

size_t Filial::getId() const { return id; }

void Filial::setId(size_t i) { id = i; }

size_t Filial::getAcademiaId() const { return academiaId; }

void Filial::setAcademiaId(size_t i) { academiaId = i; }

std::string Filial::getNome() const { return nome; }

void Filial::setNome(const std::string &n) { nome = n; }

std::string Filial::getEndereco() const { return endereco; }

void Filial::setEndereco(const std::string &e) { endereco = e; }

std::string Filial::toFileString() const {
  return std::to_string(id) + ";" + std::to_string(academiaId) + ";" + nome +
         ";" + endereco;
}

bool Filial::fromFileString(const std::string &line) {
  size_t sep1 = line.find(';');
  if (sep1 == std::string::npos)
    return false;
  size_t sep2 = line.find(';', sep1 + 1);
  if (sep2 == std::string::npos)
    return false;
  size_t sep3 = line.find(';', sep2 + 1);
  if (sep3 == std::string::npos)
    return false;
  try {
    id = std::stoul(line.substr(0, sep1));
    academiaId = std::stoul(line.substr(sep1 + 1, sep2 - sep1 - 1));
    nome = line.substr(sep2 + 1, sep3 - sep2 - 1);
    endereco = line.substr(sep3 + 1);
  } catch (...) {
    return false;
  }
  return true;
}
