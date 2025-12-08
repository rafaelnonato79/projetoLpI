#pragma once
#include "IFilePersistable.h"
#include <string>

class Filial : public IFilePersistable {
private:
  static size_t nextId;
  size_t academiaId;
  size_t id;
  std::string nome;
  std::string endereco;

public:
  Filial();

  Filial(const std::string &nome, const std::string &endereco);
  Filial(size_t academiaId, const std::string &nome,
         const std::string &endereco);

  size_t getId() const;
  void setId(size_t id);

  size_t getAcademiaId() const;
  void setAcademiaId(size_t academiaId);

  std::string getNome() const;
  void setNome(const std::string &n);

  std::string getEndereco() const;
  void setEndereco(const std::string &e);

  std::string toFileString() const override;
  bool fromFileString(const std::string &line) override;
};
