#include <clocale>
#include <iostream>
#include <memory>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "../header/Aluno.h"
#include "../header/Aula.h"
#include "../header/Equipamento.h"
#include "../header/Exceptions.h"
#include "../header/Gerenciador.h"
#include "../header/PlanoPersonalizado.h"
#include "../header/Professor.h"
#include "../header/Treino.h"

using namespace std;

static double parseDoubleFromString(const std::string &s) {
  // remove currency symbols, spaces; convert comma to dot
  std::string t;
  for (char c : s) {
    if ((c >= '0' && c <= '9') || c == '.' || c == ',')
      t.push_back(c);
  }
  for (auto &c : t)
    if (c == ',')
      c = '.';
  if (t.empty())
    return 0.0;
  try {
    return std::stod(t);
  } catch (...) {
    return 0.0;
  }
}

static int readIntFromInput() {
  std::string s;
  if (!std::getline(std::cin, s))
    throw ValidationError("Entrada inesperada");
  // trim
  auto start = s.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    throw ValidationError("Entrada vazia");
  auto end = s.find_last_not_of(" \t\r\n");
  std::string t = s.substr(start, end - start + 1);
  try {
    size_t idx = 0;
    int v = std::stoi(t, &idx);
    if (idx != t.size())
      throw ValidationError("Entrada invalida: digite um numero");
    return v;
  } catch (...) {
    throw ValidationError("Entrada invalida: digite um numero");
  }
}

void submenuAcademias(Gerenciador &ger) {
  int op;
  do {
    std::cout << "\n===== MENU ACADEMIAS =====\n";
    std::cout << "1. Criar academia\n";
    std::cout << "2. Listar academias\n";
    std::cout << "3. Atualizar academia\n";
    std::cout << "4. Remover academia\n";
    std::cout << "0. Voltar\n";
    std::cout << "Escolha uma opcao: ";
    std::cin >> op;
    std::cin.ignore();

    if (op == 1) {
      std::string nome;
      size_t maxAlunos;
      std::cout << "Nome da academia: ";
      std::getline(std::cin, nome);
      std::cout << "Maximo de alunos: ";
      std::cin >> maxAlunos;
      std::cin.ignore();
      Academia a = Academia(nome, maxAlunos);
      size_t academiaId;
      string nomeFilial, endereco;
      cout << "Nome da filial: ";
      getline(cin, nomeFilial);
      cout << "Endereco da filial: ";
      getline(cin, endereco);
      Filial novaFilial(nome, endereco);
      ger.criarAcademia(a, novaFilial);
      std::cout << "Academia criada!\n";
    } else if (op == 2) {
      ger.listarAcademias();
    } else if (op == 3) {
      size_t id;
      std::string novoNome;
      size_t novoMaxAlunos;
      std::cout << "ID da academia a atualizar: ";
      std::cin >> id;
      std::cin.ignore();
      std::cout << "Novo nome: ";
      std::getline(std::cin, novoNome);
      std::cout << "Novo maximo de alunos: ";
      std::cin >> novoMaxAlunos;
      std::cin.ignore();
      ger.atualizarAcademia(id, novoNome, novoMaxAlunos);

      std::vector<Academia> academias;
      Gerenciador::carregarObjetosDeArquivo("academias.txt", academias);
      for (auto &a : academias) {
        if (a.getId() == id) {
          a.setNome(novoNome);
          a.setMaxAlunos(novoMaxAlunos);
          break;
        }
      }
      std::ofstream file("bin/academias.txt", std::ios::trunc);
      for (const auto &a : academias) {
        file << a.toFileString() << std::endl;
      }

      std::cout << "Academia atualizada!\n";
    } else if (op == 4) {
      std::string nome;
      std::cout << "Nome da academia a remover: ";
      std::getline(std::cin, nome);
      ger.removerAcademia(nome);
      std::cout << "Academia removida!\n";
    }
  } while (op != 0);
}

void submenuPlanos(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n====================== Gerenciar Planos =====================\n";
    cout << "1. Cadastrar plano personalizado\n";
    cout << "2. Listar planos\n";
    cout << "3. Remover plano\n";
    cout << "4. Editar plano\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      string d;
      string vs;
      double v;
      cout << "Descricao do plano: ";
      getline(cin, d);
      cout << "Valor: ";
      getline(cin, vs);
      v = parseDoubleFromString(vs);
      g.adicionarPlanoPersonalizado(d, v);
      cout << "Plano adicionado com sucesso.\n";
    } else if (opcao == 2) {
      cout << "\n======= LISTA DE PLANOS =======\n\n";
      g.listarPlanos();

    } else if (opcao == 3) {
      int id;
      cout << "ID do plano a remover: ";
      cin >> id;
      cin.ignore();
      try {
        g.removerPlanoPorId(id);
        cout << "Plano removido.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 4) {
      int id;
      cout << "ID do plano a editar: ";
      cin >> id;
      cin.ignore();
      auto plano = g.buscarPlanoPorId(id);
      if (!plano) {
        cout << "Plano nao encontrado.\n";
      } else {
        cout << "Nova descrição (enter para manter): ";
        string nova;
        getline(cin, nova);
        cout << "Novo valor (enter para manter): ";
        string vs;
        getline(cin, vs);
        string novaDescricao = nova.empty() ? plano->getDescricao() : nova;
        double novoValor =
            vs.empty() ? plano->calcularValor() : parseDoubleFromString(vs);
        if (g.editarPlano(id, novaDescricao, novoValor)) {
          cout << "Plano atualizado.\n";
        } else {
          cout << "Falha ao atualizar (descricao duplicada?).\n";
        }
      }
    }
  }
}

void submenuProfessores(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n======= Gerenciar Professores =======\n";
    cout << "1. Adicionar professor\n";
    cout << "2. Remover professor\n";
    cout << "3. Listar professores\n";
    // cout << "4. Atribuir professor a aula\n";
    cout << "4. Ver aulas de um professor\n";
    cout << "5. Ver alunos ligados a professor\n";
    cout << "6. Editar professor\n";
    cout << "7. Adicionar aula\n";
    cout << "8. Remover aula\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      string nome, telelefone, especialidade;
      cout << "Nome: ";
      getline(cin, nome);
      cout << "Telefone: ";
      getline(cin, telelefone);
      cout << "Especialidade: ";
      getline(cin, especialidade);
      g.adicionarProfessor(Professor(0, nome, telelefone, especialidade));
      cout << "Professor adicionado com sucesso.\n";
    } else if (opcao == 2) {
      int id;
      cout << "ID do professor: ";
      cin >> id;
      cin.ignore();
      try {
        g.removerProfessor(id);
        cout << "Professor removido com sucesso.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 3) {
      g.listarProfessores();
    }
    // else if (opcao == 4) {
    //     int id; string nomeAula;
    //     cout << "ID do professor: ";
    //     cin >> id;
    //     cin.ignore();
    //     cout << "Nome da aula: ";
    //     getline(cin, nomeAula);
    //     try {
    //         auto aula = g.atribuirProfessorAAula(id, nomeAula);
    //         cout << "Professor atribuido a aula.\n";
    //         if (aula) {
    //             cout << "Aula atualizada:\n";
    //             aula->exibir(cout);
    //             cout << "\n";
    //         }
    //     } catch (const exception &e) {
    //         cout << "Erro: " << e.what() << "\n";
    //     }
    else if (opcao == 4) {
      int id;
      cout << "ID do professor: ";
      cin >> id;
      cin.ignore();
      auto aulas = g.listarAulasDoProfessor(id);
      cout << "\n===== AULAS DO PROFESSOR =====\n\n";
      if (aulas.empty())
        cout << "Nenhuma aula.\n";
      else
        for (auto &n : aulas)
          cout << n << "\n";
    } else if (opcao == 5) {
      int id;
      cout << "ID do professor: ";
      cin >> id;
      cin.ignore();
      auto alunos = g.listarAlunosDoProfessor(id);
      cout << "\n===== ALUNOS DO PROFESSOR =====\n\n";
      if (alunos.empty())
        cout << "Nenhum aluno ligado.\n";
      else
        for (auto &a : alunos)
          cout << a << "\n";
    } else if (opcao == 6) {
      int id;
      cout << "ID do professor a editar: ";
      cin >> id;
      cin.ignore();
      Professor *p = g.buscarProfessorPorId(id);
      if (!p) {
        cout << "Professor nao encontrado.\n";
      } else {
        cout << "Novo nome (enter para manter): ";
        string novoNome;
        getline(cin, novoNome);
        if (!novoNome.empty())
          p->setNome(novoNome);
        cout << "Novo telefone (enter para manter): ";
        string novoTelefone;
        getline(cin, novoTelefone);
        if (!novoTelefone.empty())
          p->setTelefone(novoTelefone);
        cout << "Nova especialidade (enter para manter): ";
        string novaEspecialidade;
        getline(cin, novaEspecialidade);
        if (!novaEspecialidade.empty())
          p->setEspecialidade(novaEspecialidade);
        cout << "Professor atualizado.\n";
        
        try {
          g.atualizarProfessor(id, *p);
          cout << "Alteracoes salvas com sucesso.\n";
        } catch (const exception &e) {
          cout << "Erro ao salvar: " << e.what() << "\n";
        }
      }
    } else if (opcao == 7) {
      string nomeAula;
      int id;
      cout << "Nome da aula: ";
      getline(cin, nomeAula);
      cout << "ID do professor (0 para nenhum): ";
      cin >> id;
      cin.ignore();
      Professor *p = nullptr;
      if (id != 0)
        p = g.buscarProfessorPorId(id);
      try {
        g.adicionarAula(std::make_shared<Aula>(nomeAula, p));
        cout << "Aula adicionada.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 8) {
      string nomeAula;
      cout << "Nome da aula a remover: ";
      getline(cin, nomeAula);
      try {
        g.removerAula(nomeAula);
        cout << "Aula removida.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    }
  }
}

void submenuAlunos(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n-- Gerenciar Alunos --\n";
    cout << "1. Adicionar aluno\n";
    cout << "2. Listar alunos\n";
    cout << "3. Remover aluno\n";
    cout << "4. Matricular aluno em aula\n";
    cout << "5. Editar aluno\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    cin >> opcao;
    cin.ignore();
    if (opcao == 1) {
      string nome, telefone;
      cout << "Nome: ";
      getline(cin, nome);
      cout << "Telefone: ";
      getline(cin, telefone);
      Aluno a(nome, telefone);

      // escolher filial
      // First, list academias and let user pick one
      g.listarAcademias();
      cout << "Digite o ID da academia para ver filiais: ";
      size_t academiaId;
      cin >> academiaId;
      cin.ignore();
      Academia *academia = g.buscarAcademiaPorId(academiaId);
      if (!academia) {
        cout << "Academia nao encontrada.\n";
        continue;
      }
      // List filiais for selected academia
      const auto &filiais = academia->getFiliais();
      if (filiais.empty()) {
        cout << "Nenhuma filial cadastrada para esta academia.\n";
        continue;
      }
      cout << "Filiais disponíveis:\n";
      for (const auto &f : filiais)
        cout << "ID: " << f.getId() << " | " << f.getNome()
             << " | Endereço: " << f.getEndereco() << "\n";
      cout << "Digite o ID da filial para vincular o aluno: ";
      size_t filialId;
      cin >> filialId;
      cin.ignore();
      Filial *filial = academia->buscarFilialPorId(filialId);
      if (!filial) {
        cout << "Filial nao encontrada.\n";
        continue;
      }

      // escolher plano
      cout << "Deseja atribuir um plano agora? (s/n): ";
      char resposta;
      cin >> resposta;
      cin.ignore();
      if (resposta == 's' || resposta == 'S') {
        g.listarPlanos();
        cout << "Digite o ID do plano existente, 'novo' para criar ou 0 para "
                "nenhum: ";
        string escolha;
        getline(cin, escolha);
        if (escolha == "novo") {
          string descricao;
          string valorString;
          double valorDouble;
          cout << "Descricao: ";
          getline(cin, descricao);
          cout << "Valor: ";
          getline(cin, valorString);
          cout << "\n===== TREINOS DO ALUNO =====\n\n";
          valorDouble = parseDoubleFromString(valorString);
          g.adicionarPlanoPersonalizado(descricao, valorDouble);
          auto plano = g.buscarPlanoPorDescricao(descricao);
          if (plano)
            a.setPlano(plano.get());
        } else {
          try {
            int id = stoi(escolha);
            if (id == 0) {
              cout << "Digite um ID válido.\n";
            } else {
              auto plano = g.buscarPlanoPorId(id);
              if (plano) {
                a.setPlano(plano.get());
              } else {
                cout << "Plano nao encontrado pelo ID.\n";
              }
            }
          } catch (...) {
            // tentar por descricao como fallback
            auto plano = g.buscarPlanoPorDescricao(escolha);
            if (plano)
              a.setPlano(plano.get());
            else
              cout << "Plano nao encontrado.\n";
          }
        }
      }
      try {
        g.adicionarAluno(a, filialId);
        cout << "Aluno adicionado.\n";
      } catch (const std::exception &e) {
        cout << "Erro ao adicionar aluno: " << e.what() << "\n";
      }
    } else if (opcao == 2) {
      g.listarAlunos();
    } else if (opcao == 3) {
      int matricula;
      cout << "Matricula: ";
      cin >> matricula;
      cin.ignore();
      try {
        g.removerAluno(matricula);
        cout << "Removido.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 4) {
      int matricula;
      string nomeAula;
      cout << "Matricula: ";
      cin >> matricula;
      cin.ignore();
      cout << "Nome da aula: ";
      getline(cin, nomeAula);
      try {
        g.matricularAlunoEmAula(matricula, nomeAula);
        cout << "Aluno matriculado.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 5) {
      int matricula;
      cout << "Matricula do aluno a editar: ";
      cin >> matricula;
      cin.ignore();
      Aluno *a = g.buscarAlunoPorMatricula(matricula);
      if (!a) {
        cout << "Aluno nao encontrado.\n";
        continue;
      }
      int editarOpcao = -1;
      while (editarOpcao != 0) {
        cout << "\n-- Editar Aluno (" << a->getMatricula() << ") --\n";
        cout << "1. Mudar nome\n";
        cout << "2. Mudar telefone\n";
        cout << "3. Mudar plano\n";
        cout << "4. Atribuir/Remover professor\n";
        cout << "0. Voltar\n";
        cout << "Opcao: ";
        try {
          editarOpcao = readIntFromInput();
        } catch (const ValidationError &e) {
          cout << "Erro: " << e.what() << "\n";
          editarOpcao = -1;
          continue;
        }
        if (editarOpcao == 1) {
          string novoNome;
          cout << "Novo nome: ";
          getline(cin, novoNome);
          a->setNome(novoNome);
          cout << "Nome atualizado.\n";
        } else if (editarOpcao == 2) {
          string novoTelefone;
          cout << "Novo telefone: ";
          getline(cin, novoTelefone);
          a->setTelefone(novoTelefone);
          cout << "Telefone atualizado.\n";
        } else if (editarOpcao == 3) {
          g.listarPlanos();
          cout << "Digite o ID do plano existente, 'novo' para criar ou 0 para "
                  "remover: ";
          string escolha;
          getline(cin, escolha);
          if (escolha == "novo") {
            string descricao;
            string valorString;
            double valorDouble;
            cout << "Descricao: ";
            getline(cin, descricao);
            cout << "Valor: ";
            getline(cin, valorString);
            valorDouble = parseDoubleFromString(valorString);
            g.adicionarPlanoPersonalizado(descricao, valorDouble);
            auto plano = g.buscarPlanoPorDescricao(descricao);
            if (plano) {
              a->setPlano(plano.get());
              cout << "Plano atualizado.\n";
            }
          } else {
            try {
              int id = stoi(escolha);
              if (id == 0) {
                a->setPlano(nullptr);
                cout << "Plano removido do aluno.\n";
              } else {
                auto plano = g.buscarPlanoPorId(id);
                if (plano) {
                  a->setPlano(plano.get());
                  cout << "Plano atualizado.\n";
                } else {
                  cout << "Plano nao encontrado pelo ID.\n";
                }
              }
            } catch (...) {
              auto plano = g.buscarPlanoPorDescricao(escolha);
              if (plano) {
                a->setPlano(plano.get());
                cout << "Plano atualizado.\n";
              } else {
                cout << "Plano nao encontrado.\n";
              }
            }
          }
        } else if (editarOpcao == 4) {
          cout << "Professores:\n";
          g.listarProfessores();
          cout << "Digite ID do professor para atribuir (0 para remover): ";
          int id;
          cin >> id;
          cin.ignore();
          if (id == 0) {
            a->setProfessor(nullptr);
            cout << "Professor removido do aluno.\n";
          } else {
            Professor *prof = g.buscarProfessorPorId(id);
            if (!prof)
              cout << "Professor nao encontrado.\n";
            else {
              a->setProfessor(prof);
              cout << "Professor atribuido.\n";
            }
          }
        }
      }
      // Salvar alterações no arquivo
      try {
        g.atualizarAluno(matricula, *a);
        cout << "Alteracoes salvas com sucesso.\n";
      } catch (const exception &e) {
        cout << "Erro ao salvar: " << e.what() << "\n";
      }
    }
  }
}

void submenuEquipamentos(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n-- Gerenciar Equipamentos --\n";
    cout << "1. Adicionar equipamento\n";
    cout << "2. Listar equipamentos\n";
    cout << "3. Remover equipamento\n";
    cout << "4. Editar equipamento\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      string nomeEquipamento;
      int qtd;
      cout << "Nome: ";
      getline(cin, nomeEquipamento);
      cout << "Quantidade: ";
      cin >> qtd;
      cin.ignore();
      g.adicionarEquipamento(Equipamento(nomeEquipamento, qtd));
    } else if (opcao == 2) {
      g.listarEquipamentos();
    } else if (opcao == 3) {
      int idEquipamento;
      cout << "ID do equipamento: ";
      cin >> idEquipamento;
      cin.ignore();
      try {
        g.removerEquipamento(idEquipamento);
        cout << "Removido.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 4) {
      int idEquipamento;
      cout << "ID do equipamento a editar: ";
      cin >> idEquipamento;
      cin.ignore();
      Equipamento *e = g.buscarEquipamentoPorId(idEquipamento);
      if (!e) {
        cout << "Equipamento nao encontrado.\n";
      } else {
        cout << "Novo nome (enter para manter): ";
        string novoNome;
        getline(cin, novoNome);
        if (!novoNome.empty()) {
          e->setNome(novoNome);
        }
        cout << "Nova quantidade (enter para manter): ";
        string novaQuantidade;
        getline(cin, novaQuantidade);
        if (!novaQuantidade.empty()) {
          try {
            int q = stoi(novaQuantidade);
            e->setQuantidade(q);
          } catch (...) {
          }
        }
        g.atualizarEquipamento(idEquipamento, *e);
        cout << "Equipamento atualizado.\n";
      }
    }
  }
}

void submenuTreinos(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n-- Gerenciar Treinos --\n";
    cout << "1. Adicionar treino a aluno\n";
    cout << "2. Listar treinos de um aluno\n";
    cout << "3. Editar treino de um aluno\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      int matricula;
      cout << "Matricula: ";
      cin >> matricula;
      cin.ignore();
      Aluno *a = g.buscarAlunoPorMatricula(matricula);
      if (!a) {
        cout << "Aluno nao encontrado.\n";
        continue;
      }
      cout << "Nome do treino: ";
      string nomeTreino, data;
      getline(cin, nomeTreino);
      cout << "Data: ";
      getline(cin, data);
      Treino t(nomeTreino, data);
      cout << "Adicionar equipamento? (s/n): ";
      char resposta;
      cin >> resposta;
      cin.ignore();
      while (resposta == 's' || resposta == 'S') {
        string equipamentoNome;
        int quantidade;
        cout << "Nome eq: ";
        getline(cin, equipamentoNome);
        cout << "Qtd: ";
        try {
          quantidade = readIntFromInput();
        } catch (const ValidationError &e) {
          cout << "Erro: " << e.what() << "\n";
          continue;
        }
        t += Equipamento(equipamentoNome, quantidade);
        cout << "Mais? (s/n): ";
        cin >> resposta;
        cin.ignore();
      }
      try {
        g.adicionarTreinoAoAluno(matricula, t);
        cout << "Treino adicionado.\n";
      } catch (const exception &e) {
        cout << "Erro: " << e.what() << "\n";
      }
    } else if (opcao == 2) {
      int matricula;
      cout << "Matricula: ";
      cin >> matricula;
      cin.ignore();
      Aluno *a = g.buscarAlunoPorMatricula(matricula);
      if (!a) {
        cout << "Aluno nao encontrado.\n";
        continue;
      }
      const auto &tr = a->getTreinos();
      if (tr.empty()) {
        cout << "Nenhum treino.\n";
      } else {
        cout << "\n===== TREINOS DO ALUNO =====\n\n";
        for (const auto &t : tr) {
          // imprime nome, data e equipamentos com quantidades via operator<< de
          // Treino
          cout << t << "\n";
        }
      }
    } else if (opcao == 3) {
      int matricula;
      cout << "Matricula: ";
      cin >> matricula;
      cin.ignore();
      Aluno *a = g.buscarAlunoPorMatricula(matricula);
      if (!a) {
        cout << "Aluno nao encontrado.\n";
        continue;
      }
      auto &tr = const_cast<std::vector<Treino> &>(a->getTreinos());
      if (tr.empty()) {
        cout << "Nenhum treino.\n";
        continue;
      }
      for (size_t i = 0; i < tr.size(); ++i) {
        cout << i + 1 << ". " << tr[i].getNome() << " | " << tr[i].getData()
             << "\n";
      }
      cout << "Escolha o numero do treino a editar: ";
      int idx;
      cin >> idx;
      cin.ignore();
      if (idx < 1 || idx > (int)tr.size()) {
        cout << "Indice invalido.\n";
        continue;
      }
      Treino &t = tr[idx - 1];
      cout << "Novo nome (enter para manter): ";
      string novoNome;
      getline(cin, novoNome);
      if (!novoNome.empty())
        t.setNome(novoNome);
      cout << "Nova data (enter para manter): ";
      string novaData;
      getline(cin, novaData);
      if (!novaData.empty())
        t.setData(novaData);
      // editar equipamentos
      int equipamentoOp = -1;
      while (equipamentoOp != 0) {
        cout << "\nEquipamentos do treino:\n";
        const auto &eqs = t.getEquipamentos();
        for (size_t i = 0; i < eqs.size(); ++i) {
          cout << i + 1 << ". " << eqs[i].getNome() << " (" << eqs[i].getQuantidade() << " repetições)\n";
        }
        cout << "1. Adicionar equipamento\n";
        cout << "2. Remover equipamento por nome\n";
        cout << "3. Editar quantidade de equipamento\n";
        cout << "0. Concluir\n";
        cout << "Opcao: ";
        cin >> equipamentoOp;
        cin.ignore();
        if (equipamentoOp == 1) {
          string equipamentoNovo;
          int quantidade;
          cout << "Nome eq: ";
          getline(cin, equipamentoNovo);
          cout << "Qtd: ";
          cin >> quantidade;
          cin.ignore();
          t += Equipamento(equipamentoNovo, quantidade);
          cout << "Equipamento adicionado.\n";
        } else if (equipamentoOp == 2) {
          string equipamento;
          cout << "Nome do equipamento a remover: ";
          getline(cin, equipamento);
          if (t.removerEquipamentoPorNome(equipamento)) {
            cout << "Removido.\n";
          } else {
            cout << "Equipamento nao encontrado no treino.\n";
          }
        } else if (equipamentoOp == 3) {
          string equipamento;
          cout << "Nome do equipamento: ";
          getline(cin, equipamento);
          cout << "Nova quantidade: ";
          int novaQuantidade;
          cin >> novaQuantidade;
          cin.ignore();
          if (t.editarQuantidadeEquipamento(equipamento, novaQuantidade)) {
            cout << "Quantidade atualizada.\n";
          } else {
            cout << "Equipamento nao encontrado.\n";
          }
        }
      }
      g.salvarTodosOsTreinos();
      cout << "Treino atualizado.\n";
    }
  }
}

void submenuAvaliacoes(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n-- Gerenciar Avaliacoes --\n";
    cout << "1. Adicionar avaliacao\n";
    cout << "2. Listar avaliacoes\n";
    cout << "3. Remover avaliacao\n";
    cout << "4. Editar avaliacao\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      int matricula, nota;
      string alvo, comentario;
      g.listarAlunos();
      cout << "Matricula do aluno: ";
      cin >> matricula;
      cin.ignore();
      // Validate aluno exists
      Aluno *aluno = g.buscarAlunoPorMatricula(matricula);
      if (!aluno) {
        cout << "Aluno nao encontrado.\n";
        continue;
      }
      cout << "Alvo da avaliacao (Professor/Aula/Academia): ";
      getline(cin, alvo);

      // Validation for alvo
      if (alvo == "Professor") {
        cout << "ID do professor: ";
        int profId;
        g.listarProfessores();
        cin >> profId;
        cin.ignore();
        Professor *prof = g.buscarProfessorPorId(profId);
        if (!prof) {
          cout << "Professor nao encontrado.\n";
          continue;
        }
        alvo += " #" + std::to_string(profId);
      } else if (alvo == "Academia") {
        cout << "ID da academia: ";
        size_t acadId;
        g.listarAcademias();
        cin >> acadId;
        cin.ignore();
        Academia *acad = g.buscarAcademiaPorId(acadId);
        if (!acad) {
          cout << "Academia nao encontrada.\n";
          continue;
        }
        alvo += " #" + std::to_string(acadId);
      } else if (alvo == "Aula") {
        string nomeAula;
        g.listarAulas();
        cout << "Nome da aula: ";
        getline(cin, nomeAula);
        auto aula = g.buscarAulaPorNome(nomeAula);
        if (!aula) {
          cout << "Aula nao encontrada.\n";
          continue;
        }
        alvo += " #" + nomeAula;
      } else {
        cout << "Alvo invalido. Use Professor, Aula ou Academia.\n";
        continue;
      }

      cout << "Nota (1-5): ";
      cin >> nota;
      cin.ignore();
      cout << "Comentario: ";
      getline(cin, comentario);
      g.adicionarAvaliacao(Avaliacao(matricula, alvo, nota, comentario));
      cout << "Avaliacao adicionada.\n";
    } else if (opcao == 2) {
      g.listarAvaliacoes();
    } else if (opcao == 3) {
      size_t id;
      cout << "ID da avaliacao a remover: ";
      cin >> id;
      cin.ignore();
      g.removerAvaliacao(id);
      cout << "Avaliacao removida.\n";
    } else if (opcao == 4) {
      size_t id;
      int novaNota;
      string novoComentario;
      cout << "ID da avaliacao a editar: ";
      cin >> id;
      cin.ignore();
      cout << "Nova nota (1-5): ";
      cin >> novaNota;
      cin.ignore();
      cout << "Novo comentario: ";
      getline(cin, novoComentario);
      g.atualizarAvaliacao(id, novaNota, novoComentario);
      cout << "Avaliacao atualizada.\n";
    }
  }
}

void submenuFiliais(Gerenciador &g) {
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n-- Gerenciar Filiais --\n";
    cout << "1. Adicionar filial\n";
    cout << "2. Listar filiais de uma academia\n";
    cout << "3. Remover filial\n";
    cout << "4. Editar filial\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1) {
      size_t academiaId;
      string nome, endereco;
      g.listarAcademias();
      cout << "ID da academia: ";
      cin >> academiaId;
      cin.ignore();
      cout << "Nome da filial: ";
      getline(cin, nome);
      cout << "Endereco da filial: ";
      getline(cin, endereco);
      Filial novaFilial(academiaId, nome, endereco);
      g.adicionarFilial(novaFilial, academiaId);
      cout << "Filial adicionada.\n";
    } else if (opcao == 2) {
      size_t academiaId;
      g.listarAcademias();
      cout << "ID da academia: ";
      cin >> academiaId;
      cin.ignore();
      g.listarFiliais(academiaId);
    } else if (opcao == 3) {
      size_t academiaId, filialId;
      g.listarAcademias();
      cout << "ID da academia: ";
      cin >> academiaId;
      cin.ignore();
      g.listarFiliais(academiaId);
      cout << "ID da filial a remover: ";
      cin >> filialId;
      cin.ignore();
      g.removerFilial(academiaId, filialId);
      cout << "Filial removida.\n";
    } else if (opcao == 4) {
      size_t academiaId, filialId;
      g.listarAcademias();
      cout << "ID da academia: ";
      cin >> academiaId;
      g.listarFiliais(academiaId);
      cin.ignore();
      cout << "ID da filial a editar: ";
      cin >> filialId;
      cin.ignore();
      cout << "Novo nome da filial: ";
      string novoNome;
      getline(cin, novoNome);
      cout << "Novo endereco da filial: ";
      string novoEndereco;
      getline(cin, novoEndereco);
      g.atualizarFilial(academiaId, filialId, novoNome, novoEndereco);
      cout << "Filial atualizada.\n";
    }
  }
}

int main() {
  setlocale(LC_ALL, "");
  Gerenciador g;
  // configurar saída e entrada do console para UTF-8 no Windows
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
  // ajustar locale C/C++ para facilitar formatação/uso de caracteres locais
  std::setlocale(LC_ALL, "");
  int opcao = -1;
  while (opcao != 0) {
    cout << "\n=== Sistema Academia (" << g.getNomeAcademia() << ") ===\n";
    cout << "1. Gerenciar Academia\n";
    cout << "2. Gerenciar Alunos\n";
    cout << "3. Gerenciar Professores\n";
    cout << "4. Gerenciar Planos\n";
    cout << "5. Gerenciar Equipamentos\n";
    cout << "6. Gerenciar Treinos\n";
    cout << "7. Gerenciar Avaliacoes\n";
    cout << "8. Gerenciar Filiais\n";
    cout << "0. Sair\n";
    cout << "Escolha: ";
    try {
      opcao = readIntFromInput();
    } catch (const ValidationError &e) {
      cout << "Erro: " << e.what() << "\n";
      opcao = -1;
      continue;
    }
    if (opcao == 1)
      submenuAcademias(g);
    else if (opcao == 2)
      submenuAlunos(g);
    else if (opcao == 3)
      submenuProfessores(g);
    else if (opcao == 4)
      submenuPlanos(g);
    else if (opcao == 5)
      submenuEquipamentos(g);
    else if (opcao == 6)
      submenuTreinos(g);
    else if (opcao == 7)
      submenuAvaliacoes(g);
    else if (opcao == 8)
      submenuFiliais(g);
  }
}
