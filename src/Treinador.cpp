#include "../header/Treinador.h"
#include "../header/MesmoIdExcecao.h"
#include <algorithm>

Treinador::Treinador() : modalidade(nullptr) {}

Treinador::Treinador(const std::string &nome, Modalidade *modalidade) {
  setNome(nome);
  this->modalidade = modalidade;
}

void Treinador::setModalidade(Modalidade *mod) { modalidade = mod; }

Modalidade *Treinador::getModalidade() const { return modalidade; }

void Treinador::adicionarAluno(Aluno *aluno) { alunos.push_back(aluno); }

void Treinador::removerAluno(Aluno *aluno) {
  alunos.erase(std::remove(alunos.begin(), alunos.end(), aluno), alunos.end());
}

const std::vector<Aluno *> &Treinador::getAlunos() const { return alunos; }

bool Treinador::atualizarTreinador(std::vector<Treinador *> &treinadores,
                                   const std::string &nome,
                                   Modalidade *novaModalidade) {
  for (auto &treinador : treinadores) {
    if (treinador->getNome() == nome) {

      if (treinador->getNome() == nome) {
        // Lança exceção se o novo nome for igual ao antigo
        throw MesmoIdExcecao(
            "O novo nome do treinador não pode ser igual ao nome antigo.");
      }
      treinador->setModalidade(novaModalidade);
      return true;
    }
  }
  return false;
}

bool Treinador::deletarTreinador(std::vector<Treinador *> &treinadores,
                                 const std::string &nome) {
  for (auto it = treinadores.begin(); it != treinadores.end(); ++it) {
    if ((*it)->getNome() == nome) {
      delete *it;
      treinadores.erase(it);
      return true;
    }
  }
  return false;
}

Treinador *
Treinador::buscarTreinador(const std::vector<Treinador *> &treinadores,
                           const std::string &nome) {
  for (auto *treinador : treinadores) {
    if (treinador->getNome() == nome) {
      return treinador;
    }
  }
  return nullptr;
}
