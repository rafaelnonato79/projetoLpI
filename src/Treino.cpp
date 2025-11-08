#include "../header/Treino.h"

Treino::Treino() : nome(""), modalidade(nullptr) {}

Treino::Treino(const std::string &nome, std::vector<Exercicio *> exercicios,
               Modalidade *modalidade)
    : nome(nome), exercicios(exercicios), modalidade(modalidade) {}

void Treino::setNome(const std::string &nome) { this->nome = nome; }

std::string Treino::getNome() const { return nome; }

void Treino::setExercicios(const std::vector<Exercicio *> &exercicios) {
  this->exercicios = exercicios;
}

const std::vector<Exercicio *> &Treino::getExercicios() const {
  return exercicios;
}

void Treino::setModalidade(Modalidade *modalidade) {
  this->modalidade = modalidade;
}

Modalidade *Treino::getModalidade() const { return modalidade; }

bool Treino::deletarTreino(std::vector<Treino *> &treinos,
                           const std::string &nome) {
  for (auto it = treinos.begin(); it != treinos.end(); ++it) {
    if ((*it)->getNome() == nome) {
      delete *it;
      treinos.erase(it);
      return true;
    }
  }
  return false;
}

bool Treino::atualizarTreino(std::vector<Treino *> &treinos,
                             const std::string &nome,
                             const std::string &novoNome,
                             std::vector<Exercicio *> exercicios,
                             Modalidade *modalidade) {
  for (auto &treino : treinos) {
    if (treino->getNome() == nome) {
      treino->setNome(novoNome);
      treino->setExercicios(exercicios);
      treino->setModalidade(modalidade);
      return true;
    }
  }
  return false;
}
