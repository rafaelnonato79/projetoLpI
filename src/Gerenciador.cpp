#include "../header/Gerenciador.h"
#include "../header/Aluno.h"
#include "../header/Aula.h"
#include "../header/Equipamento.h"
#include "../header/Exceptions.h"
#include "../header/Plano.h"
#include "../header/PlanoPersonalizado.h"
#include "../header/Professor.h"
#include <algorithm>
#include <iostream>

void Gerenciador::adicionarAluno(const Aluno &a, Filial *filial) {
  Aluno copy = a;
  if (filial && filial->getId() > 0) {
  }
  if (copy.getMatricula() == 0)
    copy.setMatricula(nextAlunoMatricula++);
  auto it = std::find_if(alunos.begin(), alunos.end(), [&](const Aluno &x) {
    return x.getMatricula() == copy.getMatricula();
  });
  if (it != alunos.end())
    throw DuplicateEntry("Aluno ja cadastrado (matricula)");
  copy.setFilial(filial); // link aluno to filial
  alunos.push_back(copy);
  Gerenciador::salvarObjetoEmArquivo(copy, "alunos.txt");
}

void Gerenciador::listarAlunos() const {
  std::cout << "\n===== LISTA DE ALUNOS =====\n\n";
  std::vector<Aluno> alunosArquivo;
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunosArquivo);
  if (alunos.empty()) {
    std::cout << "Nenhum aluno cadastrado.\n";
    return;
  }
  for (const auto &a : alunos)
    std::cout << a << "\n";
}

Aluno *Gerenciador::buscarAlunoPorMatricula(int matricula) {
  std::vector<Aluno> alunosArquivo;
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunosArquivo);
  for (auto &a : alunosArquivo)
    if (a.getMatricula() == matricula)
      return &a;
  return nullptr;
}

void Gerenciador::removerAluno(int matricula) {
  std::vector<Aluno> alunosArquivo;
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunosArquivo);
  auto it = std::remove_if(
      alunosArquivo.begin(), alunosArquivo.end(),
      [&](const Aluno &a) { return a.getMatricula() == matricula; });
  if (it == alunosArquivo.end())
    throw NotFound("Aluno nao encontrado");
  alunosArquivo.erase(it, alunosArquivo.end());
  std::ofstream file("bin/alunos.txt", std::ios::trunc);
  for (const auto &a : alunosArquivo) {
    file << a.toFileString() << std::endl;
  }
}

void Gerenciador::matricularAlunoEmAula(int matricula,
                                        const std::string &nomeAula) {
  Aluno *a = buscarAlunoPorMatricula(matricula);
  if (!a)
    throw NotFound("Aluno nao encontrado");
  // verificar se aula existe
  auto it = std::find_if(aulas.begin(), aulas.end(),
                         [&](const std::shared_ptr<Aula> &au) {
                           return au->getNome() == nomeAula;
                         });
  if (it == aulas.end())
    throw NotFound("Aula nao encontrada");
  a->matricularEmAula(nomeAula);
}

void Gerenciador::adicionarProfessor(const Professor &p) {
  Professor copy = p;
  if (copy.getId() == 0)
    copy.setId(nextProfessorId++);
  professores.push_back(copy);
}

void Gerenciador::listarProfessores() const {
  std::cout << "\n===== LISTA DE PROFESSORES =====\n\n";
  if (professores.empty()) {
    std::cout << "Nenhum professor cadastrado.\n";
    return;
  }
  for (const auto &p : professores)
    std::cout << p << "\n";
}

void Gerenciador::removerProfessor(int id) {
  auto itf = std::find_if(professores.begin(), professores.end(),
                          [&](const Professor &p) { return p.getId() == id; });
  if (itf == professores.end())
    throw NotFound("Professor nao encontrado");
  professores.erase(itf);
}

Professor *Gerenciador::buscarProfessorPorId(int id) {
  for (auto &p : professores)
    if (p.getId() == id)
      return &p;
  return nullptr;
}

void Gerenciador::adicionarPlano(std::shared_ptr<Plano> p) {
  if (p->getId() == 0)
    p->setId(nextPlanoId++);
  planos.push_back(std::move(p));
}

void Gerenciador::listarPlanos() const {
  std::cout << "\n===== LISTA DE PLANOS =====\n\n";
  if (planos.empty()) {
    std::cout << "Nenhum plano cadastrado.\n";
    return;
  }
  for (const auto &p : planos)
    p->exibir(std::cout), std::cout << "\n";
}

void Gerenciador::adicionarPlanoPersonalizado(const std::string &descricao,
                                              double valor) {
  auto p = std::make_shared<PlanoPersonalizado>(descricao, valor);
  if (p->getId() == 0)
    p->setId(nextPlanoId++);
  planos.push_back(p);
}

std::shared_ptr<Plano>
Gerenciador::buscarPlanoPorDescricao(const std::string &descricao) {
  for (auto &p : planos)
    if (p->getDescricao() == descricao)
      return p;
  return nullptr;
}

std::shared_ptr<Plano> Gerenciador::buscarPlanoPorId(int id) const {
  for (const auto &p : planos)
    if (p->getId() == id)
      return p;
  return nullptr;
}

void Gerenciador::removerPlanoPorId(int id) {
  auto it = std::find_if(
      planos.begin(), planos.end(),
      [&](const std::shared_ptr<Plano> &p) { return p->getId() == id; });
  if (it == planos.end())
    throw NotFound("Plano nao encontrado");
  planos.erase(it);
}

bool Gerenciador::editarPlano(int idPlano, const std::string &novaDescricao,
                              double novoValor) {
  auto p = buscarPlanoPorId(idPlano);
  if (!p)
    return false;
  // verificar duplicata se mudou descricao
  if (!novaDescricao.empty() && novaDescricao != p->getDescricao()) {
    for (const auto &pp : planos)
      if (pp->getDescricao() == novaDescricao)
        return false;
    p->setDescricao(novaDescricao);
  }
  p->setValor(novoValor);
  return true;
}

void Gerenciador::adicionarAula(std::shared_ptr<Aula> a) {
  aulas.push_back(std::move(a));
}

void Gerenciador::listarAulas() const {
  std::cout << "\n===== LISTA DE AULAS =====\n\n";
  if (aulas.empty()) {
    std::cout << "Nenhuma aula cadastrada.\n";
    return;
  }
  for (const auto &a : aulas) {
    a->exibir(std::cout);
    std::cout << "\n";
  }
}

void Gerenciador::removerAula(const std::string &nome) {
  auto it = std::remove_if(
      aulas.begin(), aulas.end(),
      [&](const std::shared_ptr<Aula> &a) { return a->getNome() == nome; });
  if (it == aulas.end())
    throw NotFound("Aula nao encontrada");
  aulas.erase(it, aulas.end());
}

// adicionarEquipamento implemented earlier to assign ids
void Gerenciador::adicionarEquipamento(const Equipamento &e) {
  Equipamento copy = e;
  if (copy.getId() == 0)
    copy.setId(nextEquipamentoId++);
  equipamentos.push_back(copy);
}

void Gerenciador::listarEquipamentos() const {
  std::cout << "\n===== LISTA DE EQUIPAMENTOS =====\n\n";
  if (equipamentos.empty()) {
    std::cout << "Nenhum equipamento cadastrado.\n";
    return;
  }
  for (const auto &e : equipamentos)
    std::cout << e << "\n";
}

std::shared_ptr<Aula>
Gerenciador::buscarAulaPorNome(const std::string &nome) const {
  for (const auto &a : aulas)
    if (a->getNome() == nome)
      return a;
  return nullptr;
}

std::shared_ptr<Aula>
Gerenciador::atribuirProfessorAAula(int idProfessor,
                                    const std::string &nomeAula) {
  auto aula = buscarAulaPorNome(nomeAula);
  if (!aula)
    throw NotFound("Aula nao encontrada");
  auto it = std::find_if(
      professores.begin(), professores.end(),
      [&](const Professor &p) { return p.getId() == idProfessor; });
  if (it == professores.end())
    throw NotFound("Professor nao encontrado");
  aula->setProfessor(&(*it));
  return aula;
}

void Gerenciador::removerEquipamento(const std::string &nome) {
  auto it =
      std::remove_if(equipamentos.begin(), equipamentos.end(),
                     [&](const Equipamento &e) { return e.getNome() == nome; });
  if (it == equipamentos.end())
    throw NotFound("Equipamento nao encontrado");
  equipamentos.erase(it, equipamentos.end());
}

Equipamento *Gerenciador::buscarEquipamentoPorNome(const std::string &nome) {
  for (auto &e : equipamentos)
    if (e.getNome() == nome)
      return &e;
  return nullptr;
}

Equipamento *Gerenciador::buscarEquipamentoPorId(int id) {
  for (auto &e : equipamentos)
    if (e.getId() == id)
      return &e;
  return nullptr;
}

// Academia info
void Gerenciador::setNomeAcademia(const std::string &nome) {
  nomeAcademia = nome;
}

std::string Gerenciador::getNomeAcademia() const { return nomeAcademia; }

void Gerenciador::adicionarHorario(const std::string &horario) {
  horarios.push_back(horario);
}

void Gerenciador::setMaxAlunos(int max) {
  if (max < 0)
    max = 0;
  maxAlunos = max;
}

int Gerenciador::getMaxAlunos() const { return maxAlunos; }

void Gerenciador::listarHorarios() const {
  std::cout << "\n===== HORARIOS =====\n\n";
  if (horarios.empty()) {
    std::cout << "Nenhum horario cadastrado.\n";
    return;
  }
  for (const auto &h : horarios)
    std::cout << h << "\n";
}

// Professores <-> Aulas/Alunos
std::vector<std::string> Gerenciador::listarAulasDoProfessor(int id) const {
  std::vector<std::string> res;
  for (const auto &a : aulas) {
    if (a->getProfessor() && a->getProfessor()->getId() == id)
      res.push_back(a->getNome());
  }
  return res;
}

std::vector<Aluno> Gerenciador::listarAlunosDoProfessor(int id) const {
  std::vector<Aluno> res;
  // obter aulas do professor
  auto aulasProf = listarAulasDoProfessor(id);
  for (const auto &al : alunos) {
    for (const auto &nomeAula : al.getAulasInscritas()) {
      if (std::find(aulasProf.begin(), aulasProf.end(), nomeAula) !=
          aulasProf.end()) {
        res.push_back(al);
        break;
      }
    }
  }
  return res;
}

void Gerenciador::criarAcademia(Academia &a, Filial &filialPrincipal) {
  std::vector<Academia> academiasArquivo;
  Gerenciador::carregarObjetosDeArquivo("academias.txt", academiasArquivo);
  size_t nextAcademiaId = 1;
  for (const auto &academia : academiasArquivo) {
    if (academia.getId() >= nextAcademiaId)
      nextAcademiaId = academia.getId() + 1;
  }
  Academia copy = a;
  copy.setId(nextAcademiaId);

  Gerenciador::salvarObjetoEmArquivo(copy, "academias.txt");

  Filial filialCopy = filialPrincipal;
  filialCopy.setAcademiaId(nextAcademiaId);
  adicionarFilial(filialCopy, nextAcademiaId);

  academias.emplace_back(copy);
}

Academia *Gerenciador::buscarAcademiaPorNome(const std::string &nome) {
  for (auto &a : academias)
    if (a.getNome() == nome)
      return &a;
  return nullptr;
}

void Gerenciador::atualizarAcademia(size_t id, const std::string &novoNome,
                                    size_t novoMaxAlunos) {
  Academia *a = buscarAcademiaPorId(id);
  if (a) {
    a->setNome(novoNome);
    a->setMaxAlunos(novoMaxAlunos);
  }
}

void Gerenciador::removerAcademia(const std::string &nome) {
  auto it =
      std::remove_if(academias.begin(), academias.end(),
                     [&](const Academia &a) { return a.getNome() == nome; });
  if (it != academias.end())
    academias.erase(it, academias.end());

  // Remover do arquivo
  std::vector<Academia> academiasArquivo;
  Gerenciador::carregarObjetosDeArquivo("academias.txt", academiasArquivo);
  academiasArquivo.erase(
      std::remove_if(academiasArquivo.begin(), academiasArquivo.end(),
                     [&](const Academia &a) { return a.getNome() == nome; }),
      academiasArquivo.end());
  std::ofstream file("bin/academias.txt", std::ios::trunc);
  for (const auto &a : academiasArquivo) {
    file << a.toFileString() << std::endl;
  }
}

const std::vector<Academia> &Gerenciador::getAcademias() const {
  return academias;
}
void Gerenciador::listarAcademias() const {
  std::cout << "\n===== LISTA DE ACADEMIAS =====\n\n";
  std::vector<Academia> academiasArquivo;
  Gerenciador::carregarObjetosDeArquivo("academias.txt", academiasArquivo);
  if (academiasArquivo.empty()) {
    std::cout << "Nenhuma academia cadastrada.\n";
    return;
  }
  for (const auto &a : academiasArquivo)
    std::cout << "Id: " << a.getId() << " | Nome da academia: " << a.getNome()
              << " | Max Alunos: " << a.getMaxAlunos() << "\n";
}

Academia *Gerenciador::buscarAcademiaPorId(size_t id) {
  for (auto &a : academias)
    if (a.getId() == id)
      return &a;
  return nullptr;
}

void Gerenciador::adicionarAvaliacao(const Avaliacao &a) {
  avaliacoes.push_back(a);
}

void Gerenciador::listarAvaliacoes() const {
  std::cout << "\n===== LISTA DE AVALIACOES =====\n\n";
  if (avaliacoes.empty()) {
    std::cout << "Nenhuma avaliacao cadastrada.\n";
    return;
  }
  for (const auto &a : avaliacoes)
    std::cout << "ID: " << a.getId() << " | Aluno: " << a.getAlunoMatricula()
              << " | Alvo: " << a.getAlvo() << " | Nota: " << a.getNota()
              << " | Comentario: " << a.getComentario() << "\n";
}

Avaliacao *Gerenciador::buscarAvaliacaoPorId(size_t id) {
  for (auto &a : avaliacoes)
    if (a.getId() == id)
      return &a;
  return nullptr;
}

void Gerenciador::removerAvaliacao(size_t id) {
  auto it = std::remove_if(avaliacoes.begin(), avaliacoes.end(),
                           [&](const Avaliacao &a) { return a.getId() == id; });
  if (it != avaliacoes.end())
    avaliacoes.erase(it, avaliacoes.end());
}

void Gerenciador::atualizarAvaliacao(size_t id, int novaNota,
                                     const std::string &novoComentario) {
  Avaliacao *a = buscarAvaliacaoPorId(id);
  if (a) {
    a->setNota(novaNota);
    a->setComentario(novoComentario);
  }
}

void Gerenciador::adicionarFilial(const Filial &f, size_t academiaId) {
  // Find the biggest filial id in filiais.txt
  std::vector<Filial> filiaisArquivo;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", filiaisArquivo);
  size_t nextFilialId = 1;
  for (const auto &filial : filiaisArquivo) {
    if (filial.getId() >= nextFilialId)
      nextFilialId = filial.getId() + 1;
  }
  Filial filialCopy = f;
  filialCopy.setId(nextFilialId);
  filialCopy.setAcademiaId(academiaId);
  Gerenciador::salvarObjetoEmArquivo(filialCopy, "filiais.txt");
  for (auto &a : academias) {
    if (a.getId() == academiaId) {
      a.adicionarFilial(filialCopy);
      break;
    }
  }
}

void Gerenciador::listarFiliais(size_t academiaId) const {
  std::vector<Filial> filiaisArquivo;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", filiaisArquivo);
  std::cout << "\n===== LISTA DE FILIAIS =====\n";
  bool found = false;
  for (const auto &f : filiaisArquivo) {
    if (f.getAcademiaId() == academiaId) {
      std::cout << "Id: " << f.getId() << " | Nome: " << f.getNome()
                << " | Endereco: " << f.getEndereco() << "\n";
      found = true;
    }
  }
  if (!found) {
    std::cout << "Nenhuma filial encontrada para essa academia.\n";
  }
}

Filial *Gerenciador::buscarFilialPorId(size_t academiaId, size_t filialId) {
  std::vector<Filial> filiaisArquivo;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", filiaisArquivo);
  for (auto &f : filiaisArquivo) {
    if (f.getAcademiaId() == academiaId && f.getId() == filialId)
      return &f;
  }
  return nullptr;
}

void Gerenciador::removerFilial(size_t academiaId, size_t filialId) {
  std::vector<Filial> filiaisArquivo;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", filiaisArquivo);
  auto it = std::remove_if(
      filiaisArquivo.begin(), filiaisArquivo.end(), [&](const Filial &f) {
        return f.getAcademiaId() == academiaId && f.getId() == filialId;
      });
  filiaisArquivo.erase(it, filiaisArquivo.end());
  std::ofstream file("bin/filiais.txt", std::ios::trunc);
  for (const auto &f : filiaisArquivo) {
    file << f.toFileString() << std::endl;
  }
}

void Gerenciador::atualizarFilial(size_t academiaId, size_t filialId,
                                  const std::string &novoNome,
                                  const std::string &novoEndereco) {
  std::vector<Filial> filiaisArquivo;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", filiaisArquivo);
  for (auto &f : filiaisArquivo) {
    if (f.getAcademiaId() == academiaId && f.getId() == filialId) {
      f.setNome(novoNome);
      f.setEndereco(novoEndereco);
      break;
    }
  }
  std::ofstream file("bin/filiais.txt", std::ios::trunc);
  for (const auto &f : filiaisArquivo) {
    file << f.toFileString() << std::endl;
  }
}
