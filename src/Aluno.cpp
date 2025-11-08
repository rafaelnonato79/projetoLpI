#include "../header/Aluno.h"
#include "../header/MesmoIdExcecao.h"

using namespace std;

Aluno::Aluno() : treinador(nullptr), treino(nullptr) {}

Aluno::Aluno(const string &nome, Treinador *treinador, Treino *treino) {
  setNome(nome);
  this->treinador = treinador;
  this->treino = treino;
}

void Aluno::Pessoa::setNome(const std::string &nome) {
  this->Pessoa::setNome(nome);
}

std::string Aluno::Pessoa::getNome() const { return this->Pessoa::getNome(); }

bool Aluno::deletarAluno(vector<Aluno *> &alunos, const string &nome) {
  for (auto it = alunos.begin(); it != alunos.end(); ++it) {
    if ((*it)->getNome() == nome) {
      delete *it;
      alunos.erase(it);
      return true;
    }
  }
  return false;
}

bool Aluno::atualizarAluno(vector<Aluno *> &alunos, const string &nome,
                           const string &novoNome, Treinador *treinador,
                           Treino *treino) {

  for (const auto &aluno : alunos) {
    if (aluno->getNome() == novoNome && aluno->getNome() != nome) {
      throw MesmoIdExcecao("Já existe um aluno com esse nome.");
    }
  }
  for (auto &aluno : alunos) {
    if (aluno->getNome() == nome) {
      aluno->setNome(novoNome);
      aluno->treinador = treinador;
      aluno->treino = treino;
      return true;
    }
  }
  return false;
}
