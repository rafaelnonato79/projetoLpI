#include "../header/Modalidade.h"
#include "../header/MesmoIdExcecao.h"

Modalidade::Modalidade() : modalidade("") {}

Modalidade::Modalidade(const std::string &modalidade)
    : modalidade(modalidade) {}

void Modalidade::setModalidade(const std::string &modalidade) {
  this->modalidade = modalidade;
}

std::string Modalidade::getModalidade() const { return modalidade; }

bool Modalidade::deletarModalidade(std::vector<Modalidade *> &modalidades,
                                   const std::string &modalidade) {
  for (auto it = modalidades.begin(); it != modalidades.end(); ++it) {
    if ((*it)->getModalidade() == modalidade) {
      delete *it;
      modalidades.erase(it);
      return true;
    }
  }
  return false;
}

bool Modalidade::atualizarModalidade(std::vector<Modalidade *> &modalidades,
                                     const std::string &modalidade,
                                     const std::string &novaModalidade) {
  for (auto &mod : modalidades) {
    if (mod->getModalidade() == modalidade) {

      if (novaModalidade == modalidade) {
        throw MesmoIdExcecao(
            "O novo nome da modalidade não pode ser igual ao nome antigo.");
      }
      mod->setModalidade(novaModalidade);
      return true;
    }
  }
  return false;
}

std::string Modalidade::toFileString() const { return modalidade; }

bool Modalidade::fromFileString(const std::string &line) {
  modalidade = line;
  return true;
}
