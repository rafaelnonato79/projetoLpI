#include "../header/Exercicio.h"
#include "../header/MesmoIdExcecao.h"

Exercicio::Exercicio() : exercicio("") {}

Exercicio::Exercicio(const std::string &exercicio) : exercicio(exercicio) {}

void Exercicio::setExercicio(const std::string &exercicio) {
  this->exercicio = exercicio;
}

std::string Exercicio::getExercicio() const { return exercicio; }

bool Exercicio::deletarExercicio(std::vector<Exercicio *> &exercicios,
                                 const std::string &exercicio) {
  for (auto it = exercicios.begin(); it != exercicios.end(); ++it) {
    if ((*it)->getExercicio() == exercicio) {
      delete *it;
      exercicios.erase(it);
      return true;
    }
  }
  return false;
}

bool Exercicio::atualizarExercicio(std::vector<Exercicio *> &exercicios,
                                   const std::string &exercicio,
                                   const std::string &novoExercicio) {

  for (auto &ex : exercicios) {
    if (ex->getExercicio() == exercicio) {

      if (novoExercicio == exercicio) {
        throw MesmoIdExcecao(
            "O novo nome do exercício não pode ser igual ao nome antigo.");
      }
      ex->setExercicio(novoExercicio);
      return true;
    }
  }
  return false;
}
