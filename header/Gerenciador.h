#pragma once
#include "Academia.h"
#include "Aluno.h"
#include "Aula.h"
#include "Avaliacao.h"
#include "Equipamento.h"
#include "Plano.h"
#include "PlanoPersonalizado.h"
#include "Professor.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Gerenciador {
private:
  std::string nomeAcademia;
  size_t id;
  int maxAlunos = 0;
  int nextAcademiaId = 1;
  int nextAlunoMatricula = 1;
  int nextProfessorId = 1;
  int nextPlanoId = 1;
  int nextEquipamentoId = 1;

  std::vector<Aluno> alunos;
  std::vector<Professor> professores;
  std::vector<std::shared_ptr<Plano>> planos;
  std::vector<std::shared_ptr<Aula>> aulas;
  std::vector<Equipamento> equipamentos;
  std::vector<std::string> horarios;
  std::vector<Academia> academias;

  std::vector<Avaliacao> avaliacoes;

public:
  // Alunos
  void adicionarAluno(const Aluno &a, Filial *filial);
  void adicionarAluno(const Aluno &a, size_t filialId);
  void listarAlunos() const;
  Aluno *buscarAlunoPorMatricula(int matricula);
  void removerAluno(int matricula);
  void atualizarAluno(int matricula, const Aluno &alunoAtualizado);
  void matricularAlunoEmAula(int matricula, const std::string &nomeAula);

  // Professores
  void adicionarProfessor(const Professor &p);
  void listarProfessores() const;
  void removerProfessor(int id);
  Professor *buscarProfessorPorId(int id);
  void atualizarProfessor(int id, const Professor &professorAtualizado);

  // Planos
  void adicionarPlano(std::shared_ptr<Plano> p);
  void listarPlanos() const;
  void adicionarPlanoPersonalizado(const std::string &descricao, double valor);
  std::shared_ptr<Plano> buscarPlanoPorDescricao(const std::string &descricao);
  std::shared_ptr<Plano> buscarPlanoPorId(int id) const;
  void removerPlanoPorId(int id);
  bool editarPlano(int idPlano, const std::string &novaDescricao,
                   double novoValor);

  // Aulas
  void adicionarAula(std::shared_ptr<Aula> a);
  void listarAulas() const;
  void removerAula(const std::string &nome);
  std::shared_ptr<Aula> buscarAulaPorNome(const std::string &nome) const;
  std::shared_ptr<Aula> atribuirProfessorAAula(int idProfessor,
                                               const std::string &nomeAula);

  // Equipamentos
  void adicionarEquipamento(const Equipamento &e);
  void listarEquipamentos() const;
  void removerEquipamento(int id);
  Equipamento *buscarEquipamentoPorNome(const std::string &nome);
  Equipamento *buscarEquipamentoPorId(int id);
  void atualizarEquipamento(int id, const Equipamento &equipamentoAtualizado);

  // Treinos
  void adicionarTreinoAoAluno(int matricula, const Treino &treino);
  void carregarTreinosDoAluno(int matricula, Aluno *aluno);
  void salvarTodosOsTreinos();

  // Academia info
  void setNomeAcademia(const std::string &nome);
  std::string getNomeAcademia() const;
  void adicionarHorario(const std::string &horario);
  void setMaxAlunos(int max);
  int getMaxAlunos() const;
  void listarHorarios() const;

  // Professores <-> Aulas/Alunos
  std::vector<std::string> listarAulasDoProfessor(int id) const;
  std::vector<Aluno> listarAlunosDoProfessor(int id) const;

  // Academia CRUD
  void criarAcademia(Academia &a, Filial &filialPrincipal);
  Academia *buscarAcademiaPorNome(const std::string &nome);
  void atualizarAcademia(size_t id, const std::string &novoNome,
                         size_t novoMaxAlunos);
  void removerAcademia(const std::string &nome);
  void listarAcademias() const;
  Academia *buscarAcademiaPorId(size_t id);
  const std::vector<Academia> &getAcademias() const;

  // Avaliacao CRUD
  void adicionarAvaliacao(const Avaliacao &a);
  void listarAvaliacoes() const;
  Avaliacao *buscarAvaliacaoPorId(size_t id);
  void removerAvaliacao(size_t id);
  void atualizarAvaliacao(size_t id, int novaNota,
                          const std::string &novoComentario);

  void adicionarFilial(const Filial &f, size_t academiaId);
  void listarFiliais(size_t academiaId) const;
  Filial *buscarFilialPorId(size_t academiaId, size_t filialId);
  void removerFilial(size_t academiaId, size_t filialId);
  void atualizarFilial(size_t academiaId, size_t filialId,
                       const std::string &novoNome,
                       const std::string &novoEndereco);

  template <typename T>
  static void salvarObjetoEmArquivo(const T &obj, const std::string &caminho) {
    std::filesystem::create_directories("bin");
    std::ofstream file("bin/" + caminho, std::ios::app);
    if (file.is_open()) {
      file << obj.toFileString() << std::endl;
      file.close();
    }
  }

  template <typename T>
  static bool carregarObjetosDeArquivo(const std::string &caminho,
                                       std::vector<T> &objetos) {
    std::ifstream file("bin/" + caminho);
    if (!file.is_open())
      return false;
    std::string line;
    while (std::getline(file, line)) {
      T obj;
      if (obj.fromFileString(line)) {
        objetos.push_back(obj);
      }
    }
    return true;
  }

  template <typename T, typename Key>
  static bool atualizarObjetoEmArquivo(
      const std::string &caminho, const Key &chave, const T &novoObjeto,
      std::function<bool(const T &, const Key &)> comparador) {
    std::vector<T> objetos;
    if (!carregarObjetosDeArquivo(caminho, objetos))
      return false;
    bool atualizado = false;
    for (auto &obj : objetos) {
      if (comparador(obj, chave)) {
        obj = novoObjeto;
        atualizado = true;
        break;
      }
    }
    if (atualizado) {
      std::ofstream file("bin/" + caminho, std::ios::trunc);
      if (!file.is_open())
        return false;
      for (const auto &obj : objetos) {
        file << obj.toFileString() << std::endl;
      }
    }
    return atualizado;
  }

  template <typename T, typename Key>
  static bool removerObjetoDeArquivo(
      const std::string &caminho, const Key &chave,
      std::function<bool(const T &, const Key &)> comparador) {
    std::vector<T> objetos;
    if (!carregarObjetosDeArquivo(caminho, objetos))
      return false;
    auto oldSize = objetos.size();
    objetos.erase(
        std::remove_if(objetos.begin(), objetos.end(),
                       [&](const T &obj) { return comparador(obj, chave); }),
        objetos.end());
    if (objetos.size() == oldSize)
      return false; // nothing removed
    std::ofstream file("bin/" + caminho, std::ios::trunc);
    if (!file.is_open())
      return false;
    for (const auto &obj : objetos) {
      file << obj.toFileString() << std::endl;
    }
    return true;
  }
};
