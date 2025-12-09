#include "../header/Treino.h"
#include "../header/Equipamento.h"
#include <algorithm>
#include <filesystem>
#include <fstream>

Treino::Treino() : nome(""), data("") {}

Treino::Treino(const std::string &nome, const std::string &data)
  : nome(nome), data(data) {}

std::string Treino::getNome() const { return nome; }

std::string Treino::getData() const { return data; }

void Treino::adicionarEquipamento(const Equipamento &e) {
  equipamentos.push_back(e);
}

const std::vector<Equipamento> &Treino::getEquipamentos() const {
  return equipamentos;
}

Treino &Treino::operator+=(const Equipamento &e) {
  equipamentos.push_back(e);
  return *this;
}

void Treino::setNome(const std::string &n) { nome = n; }

void Treino::setData(const std::string &d) { data = d; }

bool Treino::removerEquipamentoPorNome(const std::string &nome) {
  auto it =
      std::remove_if(equipamentos.begin(), equipamentos.end(),
                     [&](const Equipamento &e) { return e.getNome() == nome; });
  if (it == equipamentos.end())
    return false;
  equipamentos.erase(it, equipamentos.end());
  return true;
}

bool Treino::editarQuantidadeEquipamento(const std::string &nome,
                                         int novaQuantidade) {
  for (auto &e : equipamentos) {
    if (e.getNome() == nome) {
      e.setQuantidade(novaQuantidade);
      return true;
    }
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Treino &t) {
  os << t.getNome() << " | " << t.getData();
  const auto &eqs = t.getEquipamentos();
  if (!eqs.empty()) {
    os << " | Equipamentos: ";
    for (size_t i = 0; i < eqs.size(); ++i) {
      os << eqs[i].getNome() << " (" << eqs[i].getQuantidade() << " repetições)";
      if (i + 1 < eqs.size())
        os << ", ";
    }
  }
  return os;
}

std::string Treino::toFileString() const {
  std::string result = nome + ";" + data;
  for (const auto &eq : equipamentos) {
    result += ";" + eq.getNome() + ":" + std::to_string(eq.getQuantidade());
  }
  return result;
}

bool Treino::fromFileString(const std::string &line) {
  equipamentos.clear();
  size_t pos1 = line.find(';');
  if (pos1 == std::string::npos)
    return false;
  nome = line.substr(0, pos1);
  size_t pos2 = line.find(';', pos1 + 1);
  if (pos2 == std::string::npos) {
    data = line.substr(pos1 + 1);
    return true;
  }
  data = line.substr(pos1 + 1, pos2 - pos1 - 1);

  size_t start = pos2 + 1;
  while (start < line.size()) {
    size_t next = line.find(';', start);
    std::string eqStr = line.substr(start, next - start);
    size_t sep = eqStr.find(':');
    if (sep != std::string::npos) {
      std::string eqNome = eqStr.substr(0, sep);
      int eqQtd = std::stoi(eqStr.substr(sep + 1));
      equipamentos.emplace_back(eqNome, eqQtd);
    }
    if (next == std::string::npos)
      break;
    start = next + 1;
  }
  return true;
}
