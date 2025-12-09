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
  alunos.clear();
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunos);

  int maxId = 0;
  for (const auto &al : alunos)
    if (al.getMatricula() > maxId)
      maxId = al.getMatricula();
  nextAlunoMatricula = maxId + 1;

  Aluno copy = a;
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

void Gerenciador::adicionarAluno(const Aluno &a, size_t filialId) {
  alunos.clear();
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunos);

  int maxId = 0;
  for (const auto &al : alunos)
    if (al.getMatricula() > maxId)
      maxId = al.getMatricula();
  nextAlunoMatricula = maxId + 1;

  Aluno copy = a;
  if (copy.getMatricula() == 0)
    copy.setMatricula(nextAlunoMatricula++);

  auto it = std::find_if(alunos.begin(), alunos.end(), [&](const Aluno &x) {
    return x.getMatricula() == copy.getMatricula();
  });
  if (it != alunos.end())
    throw DuplicateEntry("Aluno ja cadastrado (matricula)");

  // Filial pointer será nullptr, mas está OK para persistência
  copy.setFilial(nullptr);
  alunos.push_back(copy);
  Gerenciador::salvarObjetoEmArquivo(copy, "alunos.txt");
}

void Gerenciador::listarAlunos() const {
  std::cout << "\n===== LISTA DE ALUNOS =====\n\n";
  std::vector<Aluno> alunosArquivo;
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunosArquivo);
  if (alunosArquivo.empty()) {
    std::cout << "Nenhum aluno cadastrado.\n";
    return;
  }
  for (const auto &a : alunosArquivo)
    std::cout << a << "\n";
}

Aluno *Gerenciador::buscarAlunoPorMatricula(int matricula) {
  alunos.clear();
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunos);
  auto it = std::find_if(alunos.begin(), alunos.end(),
                         [&](const Aluno &a) {
                           return a.getMatricula() == matricula;
                         });
  if (it == alunos.end())
    return nullptr;
  
  // Carregar treinos do aluno
  carregarTreinosDoAluno(matricula, &(*it));
  
  return &(*it);
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

  alunos = alunosArquivo;
}

void Gerenciador::atualizarAluno(int matricula, const Aluno &alunoAtualizado) {
  std::vector<Aluno> alunosArquivo;
  Gerenciador::carregarObjetosDeArquivo("alunos.txt", alunosArquivo);
  bool encontrado = false;
  for (auto &a : alunosArquivo) {
    if (a.getMatricula() == matricula) {
      a = alunoAtualizado;
      encontrado = true;
      break;
    }
  }
  if (!encontrado)
    throw NotFound("Aluno nao encontrado");
  
  std::ofstream file("bin/alunos.txt", std::ios::trunc);
  for (const auto &a : alunosArquivo) {
    file << a.toFileString() << std::endl;
  }
  alunos = alunosArquivo;
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
  professores.clear();
  Gerenciador::carregarObjetosDeArquivo("professores.txt", professores);

  int maxId = 0;
  for (const auto &prof : professores)
    if (static_cast<int>(prof.getId()) > maxId)
      maxId = static_cast<int>(prof.getId());
  nextProfessorId = maxId + 1;

  Professor copy = p;
  if (copy.getId() == 0)
    copy.setId(nextProfessorId++);

  auto it = std::find_if(professores.begin(), professores.end(),
                         [&](const Professor &pr) {
                           return pr.getId() == copy.getId();
                         });
  if (it != professores.end())
    throw DuplicateEntry("Professor ja cadastrado (id)");

  professores.push_back(copy);
  Gerenciador::salvarObjetoEmArquivo(copy, "professores.txt");
}

void Gerenciador::listarProfessores() const {
  std::cout << "\n===== LISTA DE PROFESSORES =====\n\n";
  std::vector<Professor> profs;
  Gerenciador::carregarObjetosDeArquivo("professores.txt", profs);
  if (profs.empty()) {
    std::cout << "Nenhum professor cadastrado.\n";
    return;
  }
  for (const auto &p : profs)
    std::cout << p << "\n";
}

void Gerenciador::removerProfessor(int id) {
  std::vector<Professor> profs;
  Gerenciador::carregarObjetosDeArquivo("professores.txt", profs);
  auto itf = std::find_if(profs.begin(), profs.end(),
                          [&](const Professor &p) { return p.getId() == id; });
  if (itf == profs.end())
    throw NotFound("Professor nao encontrado");
  profs.erase(itf);
  std::ofstream file("bin/professores.txt", std::ios::trunc);
  for (const auto &p : profs)
    file << p.toFileString() << std::endl;
  professores = profs;
}

Professor *Gerenciador::buscarProfessorPorId(int id) {
  professores.clear();
  Gerenciador::carregarObjetosDeArquivo("professores.txt", professores);
  auto it = std::find_if(professores.begin(), professores.end(),
                         [&](const Professor &p) { return p.getId() == id; });
  if (it == professores.end())
    return nullptr;
  return &(*it);
}

void Gerenciador::atualizarProfessor(int id, const Professor &professorAtualizado) {
  std::vector<Professor> profs;
  Gerenciador::carregarObjetosDeArquivo("professores.txt", profs);
  bool encontrado = false;
  for (auto &p : profs) {
    if (p.getId() == id) {
      p = professorAtualizado;
      encontrado = true;
      break;
    }
  }
  if (!encontrado)
    throw NotFound("Professor nao encontrado");
  
  std::ofstream file("bin/professores.txt", std::ios::trunc);
  for (const auto &p : profs)
    file << p.toFileString() << std::endl;
  professores = profs;
}

void Gerenciador::adicionarPlano(std::shared_ptr<Plano> p) {
  // carregar planos existentes para ajustar id
  planos.clear();
  std::vector<PlanoPersonalizado> planosBase;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  for (const auto &pl : planosBase)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);
  for (const auto &pl : planosPers)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));

  int maxId = 0;
  for (const auto &pl : planos)
    if (static_cast<int>(pl->getId()) > maxId)
      maxId = static_cast<int>(pl->getId());
  nextPlanoId = maxId + 1;

  if (p->getId() == 0)
    p->setId(nextPlanoId++);
  planos.push_back(p);
  Gerenciador::salvarObjetoEmArquivo(*p, "planos.txt");
}

void Gerenciador::listarPlanos() const {
  std::cout << "\n===== LISTA DE PLANOS =====\n\n";
  std::vector<PlanoPersonalizado> planosBase;
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);
  if (planosBase.empty() && planosPers.empty()) {
    std::cout << "Nenhum plano cadastrado.\n";
    return;
  }
  for (const auto &p : planosBase) {
    p.exibir(std::cout);
    std::cout << "\n";
  }
  for (const auto &p : planosPers) {
    p.exibir(std::cout);
    std::cout << "\n";
  }
}

void Gerenciador::adicionarPlanoPersonalizado(const std::string &descricao,
                                              double valor) {
  planos.clear();
  std::vector<PlanoPersonalizado> planosBase;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  for (const auto &pl : planosBase)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);
  for (const auto &pl : planosPers)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));

  int maxId = 0;
  for (const auto &pl : planos)
    if (static_cast<int>(pl->getId()) > maxId)
      maxId = static_cast<int>(pl->getId());
  nextPlanoId = maxId + 1;

  auto p = std::make_shared<PlanoPersonalizado>(descricao, valor);
  if (p->getId() == 0)
    p->setId(nextPlanoId++);
  planos.push_back(p);
  Gerenciador::salvarObjetoEmArquivo(*p, "planos_personalizados.txt");
}

std::shared_ptr<Plano>
Gerenciador::buscarPlanoPorDescricao(const std::string &descricao) {
  planos.clear();
  std::vector<PlanoPersonalizado> planosBase;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  for (const auto &pl : planosBase)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);
  for (const auto &pl : planosPers)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));

  for (auto &p : planos)
    if (p->getDescricao() == descricao)
      return p;
  return nullptr;
}

std::shared_ptr<Plano> Gerenciador::buscarPlanoPorId(int id) const {
  auto self = const_cast<Gerenciador *>(this);
  self->planos.clear();
  std::vector<PlanoPersonalizado> planosBase;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  for (const auto &pl : planosBase)
    self->planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);
  for (const auto &pl : planosPers)
    self->planos.push_back(std::make_shared<PlanoPersonalizado>(pl));

  for (const auto &p : planos)
    if (p->getId() == id)
      return p;
  return nullptr;
}

void Gerenciador::removerPlanoPorId(int id) {
  std::vector<PlanoPersonalizado> planosBase;
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);

  auto eraseById = [&](auto &vec) {
    auto it = std::remove_if(vec.begin(), vec.end(),
                             [&](const auto &p) { return p.getId() == id; });
    bool removed = it != vec.end();
    vec.erase(it, vec.end());
    return removed;
  };

  bool removedBase = eraseById(planosBase);
  bool removedPers = eraseById(planosPers);
  if (!removedBase && !removedPers)
    throw NotFound("Plano nao encontrado");

  std::ofstream f1("bin/planos.txt", std::ios::trunc);
  for (const auto &p : planosBase)
    f1 << p.toFileString() << std::endl;
  std::ofstream f2("bin/planos_personalizados.txt", std::ios::trunc);
  for (const auto &p : planosPers)
    f2 << p.toFileString() << std::endl;

  planos.clear();
  for (const auto &pl : planosBase)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  for (const auto &pl : planosPers)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
}

bool Gerenciador::editarPlano(int idPlano, const std::string &novaDescricao,
                              double novoValor) {
  std::vector<PlanoPersonalizado> planosBase;
  std::vector<PlanoPersonalizado> planosPers;
  Gerenciador::carregarObjetosDeArquivo("planos.txt", planosBase);
  Gerenciador::carregarObjetosDeArquivo("planos_personalizados.txt",
                                        planosPers);

  auto atualizar = [&](auto &vec) -> bool {
    for (auto &p : vec) {
      if (p.getId() == static_cast<size_t>(idPlano)) {
        if (!novaDescricao.empty() && novaDescricao != p.getDescricao()) {
          // checar duplicata em ambos vetores
          for (const auto &pp : planosBase)
            if (pp.getDescricao() == novaDescricao && pp.getId() != p.getId())
              return false;
          for (const auto &pp : planosPers)
            if (pp.getDescricao() == novaDescricao && pp.getId() != p.getId())
              return false;
          p.setDescricao(novaDescricao);
        }
        p.setValor(novoValor);
        return true;
      }
    }
    return false;
  };

  bool okBase = atualizar(planosBase);
  bool okPers = okBase ? false : atualizar(planosPers);
  if (!okBase && !okPers)
    return false;

  std::ofstream f1("bin/planos.txt", std::ios::trunc);
  for (const auto &p : planosBase)
    f1 << p.toFileString() << std::endl;
  std::ofstream f2("bin/planos_personalizados.txt", std::ios::trunc);
  for (const auto &p : planosPers)
    f2 << p.toFileString() << std::endl;

  planos.clear();
  for (const auto &pl : planosBase)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));
  for (const auto &pl : planosPers)
    planos.push_back(std::make_shared<PlanoPersonalizado>(pl));

  return true;
}

void Gerenciador::adicionarAula(std::shared_ptr<Aula> a) {
  aulas.clear();
  std::vector<Aula> aulasArquivo;
  Gerenciador::carregarObjetosDeArquivo("aulas.txt", aulasArquivo);
  for (const auto &au : aulasArquivo)
    aulas.push_back(std::make_shared<Aula>(au));

  auto it = std::find_if(aulasArquivo.begin(), aulasArquivo.end(),
                         [&](const Aula &au) { return au.getNome() == a->getNome(); });
  if (it != aulasArquivo.end())
    throw DuplicateEntry("Aula ja cadastrada");

  Gerenciador::salvarObjetoEmArquivo(*a, "aulas.txt");
  aulas.push_back(a);
}

void Gerenciador::listarAulas() const {
  std::cout << "\n===== LISTA DE AULAS =====\n\n";
  std::vector<Aula> aulasArquivo;
  Gerenciador::carregarObjetosDeArquivo("aulas.txt", aulasArquivo);
  if (aulasArquivo.empty()) {
    std::cout << "Nenhuma aula cadastrada.\n";
    return;
  }
  for (const auto &a : aulasArquivo) {
    a.exibir(std::cout);
    std::cout << "\n";
  }
}

void Gerenciador::removerAula(const std::string &nome) {
  std::vector<Aula> aulasArquivo;
  Gerenciador::carregarObjetosDeArquivo("aulas.txt", aulasArquivo);
  auto it = std::remove_if(aulasArquivo.begin(), aulasArquivo.end(),
                           [&](const Aula &a) { return a.getNome() == nome; });
  if (it == aulasArquivo.end())
    throw NotFound("Aula nao encontrada");
  aulasArquivo.erase(it, aulasArquivo.end());
  std::ofstream file("bin/aulas.txt", std::ios::trunc);
  for (const auto &a : aulasArquivo)
    file << a.toFileString() << std::endl;
  aulas.clear();
  for (const auto &a : aulasArquivo)
    aulas.push_back(std::make_shared<Aula>(a));
}

// adicionarEquipamento implemented earlier to assign ids
void Gerenciador::adicionarEquipamento(const Equipamento &e) {
  equipamentos.clear();
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", equipamentos);
  int maxId = 0;
  for (const auto &eq : equipamentos)
    if (static_cast<int>(eq.getId()) > maxId)
      maxId = static_cast<int>(eq.getId());
  nextEquipamentoId = maxId + 1;

  Equipamento copy = e;
  if (copy.getId() == 0)
    copy.setId(nextEquipamentoId++);

  auto it = std::find_if(equipamentos.begin(), equipamentos.end(),
                         [&](const Equipamento &eq) {
                           return eq.getId() == copy.getId();
                         });
  if (it != equipamentos.end())
    throw DuplicateEntry("Equipamento ja cadastrado (id)");

  equipamentos.push_back(copy);
  Gerenciador::salvarObjetoEmArquivo(copy, "equipamentos.txt");
}

void Gerenciador::listarEquipamentos() const {
  std::cout << "\n===== LISTA DE EQUIPAMENTOS =====\n\n";
  std::vector<Equipamento> eqs;
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", eqs);
  if (eqs.empty()) {
    std::cout << "Nenhum equipamento cadastrado.\n";
    return;
  }
  for (const auto &e : eqs)
    std::cout << e << "\n";
}

std::shared_ptr<Aula>
Gerenciador::buscarAulaPorNome(const std::string &nome) const {
  auto self = const_cast<Gerenciador *>(this);
  self->aulas.clear();
  std::vector<Aula> aulasArquivo;
  Gerenciador::carregarObjetosDeArquivo("aulas.txt", aulasArquivo);
  for (const auto &a : aulasArquivo)
    self->aulas.push_back(std::make_shared<Aula>(a));
  for (const auto &a : self->aulas)
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
  professores.clear();
  Gerenciador::carregarObjetosDeArquivo("professores.txt", professores);
  auto it = std::find_if(professores.begin(), professores.end(),
                         [&](const Professor &p) { return p.getId() == idProfessor; });
  if (it == professores.end())
    throw NotFound("Professor nao encontrado");
  aula->setProfessor(&(*it));

  std::vector<Aula> aulasArquivo;
  Gerenciador::carregarObjetosDeArquivo("aulas.txt", aulasArquivo);
  for (auto &a : aulasArquivo) {
    if (a.getNome() == nomeAula) {
      a.setProfessor(&(*it));
      break;
    }
  }
  std::ofstream file("bin/aulas.txt", std::ios::trunc);
  for (const auto &a : aulasArquivo)
    file << a.toFileString() << std::endl;

  return aula;
}

void Gerenciador::removerEquipamento(int id) {
  std::vector<Equipamento> eqs;
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", eqs);
  auto it = std::remove_if(eqs.begin(), eqs.end(),
                           [&](const Equipamento &e) { return static_cast<int>(e.getId()) == id; });
  if (it == eqs.end())
    throw NotFound("Equipamento nao encontrado");
  eqs.erase(it, eqs.end());
  std::ofstream file("bin/equipamentos.txt", std::ios::trunc);
  for (const auto &e : eqs)
    file << e.toFileString() << std::endl;
  equipamentos = eqs;
}

Equipamento *Gerenciador::buscarEquipamentoPorNome(const std::string &nome) {
  equipamentos.clear();
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", equipamentos);
  auto it = std::find_if(equipamentos.begin(), equipamentos.end(),
                         [&](const Equipamento &e) { return e.getNome() == nome; });
  if (it == equipamentos.end())
    return nullptr;
  return &(*it);
}

Equipamento *Gerenciador::buscarEquipamentoPorId(int id) {
  equipamentos.clear();
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", equipamentos);
  auto it = std::find_if(equipamentos.begin(), equipamentos.end(),
                         [&](const Equipamento &e) { return e.getId() == id; });
  if (it == equipamentos.end())
    return nullptr;
  return &(*it);
}

void Gerenciador::atualizarEquipamento(int id, const Equipamento &equipamentoAtualizado) {
  std::vector<Equipamento> equipamentosArquivo;
  Gerenciador::carregarObjetosDeArquivo("equipamentos.txt", equipamentosArquivo);
  bool encontrado = false;
  for (auto &e : equipamentosArquivo) {
    if (static_cast<int>(e.getId()) == id) {
      e = equipamentoAtualizado;
      encontrado = true;
      break;
    }
  }
  if (!encontrado)
    throw NotFound("Equipamento nao encontrado");
  
  std::ofstream file("bin/equipamentos.txt", std::ios::trunc);
  for (const auto &e : equipamentosArquivo) {
    file << e.toFileString() << std::endl;
  }
  equipamentos = equipamentosArquivo;
}

// Treinos
void Gerenciador::adicionarTreinoAoAluno(int matricula, const Treino &treino) {
  Aluno *aluno = buscarAlunoPorMatricula(matricula);
  if (!aluno)
    throw NotFound("Aluno nao encontrado");
  
  aluno->adicionarTreino(treino);
  
  // Salvar treino no arquivo
  std::filesystem::create_directories("bin");
  std::ofstream file("bin/treinos.txt", std::ios::app);
  if (file.is_open()) {
    file << std::to_string(matricula) << ";" << treino.toFileString() << std::endl;
    file.close();
  }
  
  // Atualizar aluno no arquivo
  atualizarAluno(matricula, *aluno);
}

void Gerenciador::carregarTreinosDoAluno(int matricula, Aluno *aluno) {
  if (!aluno)
    return;
  
  std::ifstream file("bin/treinos.txt");
  if (!file.is_open())
    return;
  
  std::string line;
  while (std::getline(file, line)) {
    size_t sep = line.find(';');
    if (sep == std::string::npos)
      continue;
    
    int mat = std::stoi(line.substr(0, sep));
    if (mat == matricula) {
      Treino t;
      if (t.fromFileString(line.substr(sep + 1))) {
        aluno->adicionarTreino(t);
      }
    }
  }
  file.close();
}

void Gerenciador::salvarTodosOsTreinos() {
  std::filesystem::create_directories("bin");
  std::ofstream file("bin/treinos.txt", std::ios::trunc);
  
  for (const auto &aluno : alunos) {
    for (const auto &treino : aluno.getTreinos()) {
      file << std::to_string(aluno.getMatricula()) << ";" << treino.toFileString() << std::endl;
    }
  }
  file.close();
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
  academias.clear();
  Gerenciador::carregarObjetosDeArquivo("academias.txt", academias);
  
  // Carregar filiais para cada academia
  std::vector<Filial> todasFiliais;
  Gerenciador::carregarObjetosDeArquivo("filiais.txt", todasFiliais);
  
  for (auto &a : academias) {
    if (a.getId() == id) {
      // Adicionar filiais correspondentes
      for (const auto &f : todasFiliais) {
        if (f.getAcademiaId() == id) {
          a.adicionarFilial(f);
        }
      }
      return &a;
    }
  }
  return nullptr;
}

void Gerenciador::adicionarAvaliacao(const Avaliacao &a) {
  avaliacoes.clear();
  Gerenciador::carregarObjetosDeArquivo("avaliacoes.txt", avaliacoes);
  
  // Criar cópia para garantir ID correto
  Avaliacao copy = a;
  
  avaliacoes.push_back(copy);
  Gerenciador::salvarObjetoEmArquivo(copy, "avaliacoes.txt");
}

void Gerenciador::listarAvaliacoes() const {
  std::cout << "\n===== LISTA DE AVALIACOES =====\n\n";
  std::vector<Avaliacao> avs;
  Gerenciador::carregarObjetosDeArquivo("avaliacoes.txt", avs);
  if (avs.empty()) {
    std::cout << "Nenhuma avaliacao cadastrada.\n";
    return;
  }
  for (const auto &a : avs)
    std::cout << "ID: " << a.getId() << " | Aluno: " << a.getAlunoMatricula()
              << " | Alvo: " << a.getAlvo() << " | Nota: " << a.getNota()
              << " | Comentario: " << a.getComentario() << "\n";
}

Avaliacao *Gerenciador::buscarAvaliacaoPorId(size_t id) {
  avaliacoes.clear();
  Gerenciador::carregarObjetosDeArquivo("avaliacoes.txt", avaliacoes);
  auto it = std::find_if(avaliacoes.begin(), avaliacoes.end(),
                         [&](const Avaliacao &a) { return a.getId() == id; });
  if (it == avaliacoes.end())
    return nullptr;
  return &(*it);
}

void Gerenciador::removerAvaliacao(size_t id) {
  std::vector<Avaliacao> avs;
  Gerenciador::carregarObjetosDeArquivo("avaliacoes.txt", avs);
  auto it = std::remove_if(avs.begin(), avs.end(),
                           [&](const Avaliacao &a) { return a.getId() == id; });
  if (it == avs.end())
    return;
  avs.erase(it, avs.end());
  std::ofstream file("bin/avaliacoes.txt", std::ios::trunc);
  for (const auto &a : avs)
    file << a.toFileString() << std::endl;
  avaliacoes = avs;
}

void Gerenciador::atualizarAvaliacao(size_t id, int novaNota,
                                     const std::string &novoComentario) {
  std::vector<Avaliacao> avs;
  Gerenciador::carregarObjetosDeArquivo("avaliacoes.txt", avs);
  for (auto &a : avs) {
    if (a.getId() == id) {
      a.setNota(novaNota);
      a.setComentario(novoComentario);
      break;
    }
  }
  std::ofstream file("bin/avaliacoes.txt", std::ios::trunc);
  for (const auto &a : avs)
    file << a.toFileString() << std::endl;
  avaliacoes = avs;
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
