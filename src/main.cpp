#include <iostream>
#include <memory>
#include <string>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif
#include "../header/Gerenciador.h"
#include "../header/Aluno.h"
#include "../header/Professor.h"
#include "../header/PlanoPersonalizado.h"
#include "../header/Aula.h"
#include "../header/Equipamento.h"
#include "../header/Treino.h"

using namespace std;

static double parseDoubleFromString(const std::string &s) {
    // remove currency symbols, spaces; convert comma to dot
    std::string t;
    for (char c : s) {
        if ((c >= '0' && c <= '9') || c == '.' || c == ',') t.push_back(c);
    }
    for (auto &c : t) if (c == ',') c = '.';
    if (t.empty()) return 0.0;
    try { return std::stod(t); } catch (...) { return 0.0; }
}

void submenuAcademia(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n-- Gerenciar Academia --\n";
        cout << "1. Ver nome da academia\n";
        cout << "2. Mudar nome da academia\n";
        cout << "3. Adicionar horario\n";
        cout << "4. Listar horarios\n";
    cout << "5. Definir limite maximo de alunos\n";
    cout << "6. Ver detalhes da academia\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; cin >> op; cin.ignore();
    if (op == 1) {
        cout << "=========== Nome da Academia =============\n "; 
        cout << g.getNomeAcademia();
        cout << "\n========================================";
    }
    else if (op == 2) { 
        string nome; 
        cout << " =================== Novo Nome ===================\n"; 
        cout << "Novo nome: "; 
        getline(cin, nome); 
        g.setNomeAcademia(nome); 
        cout<< "\n=====================================";
    }
    else if (op == 3) { 
        string h; 
        cout << "Horario (ex: Seg 08:00-12:00): "; 
        getline(cin, h); 
        g.adicionarHorario(h); 
    }else if (op == 4) { 
        cout << "\n===== HORARIOS =====\n\n"; g.listarHorarios(); cout << "\n====================================="; }
    else if (op == 5) {
        int max; cout << "Informe o limite maximo de alunos (0 para sem limite): "; cin >> max; cin.ignore();
        g.setMaxAlunos(max);
        cout << "Limite configurado para " << (max == 0 ? string("sem limite") : to_string(max)) << " alunos." << endl;
    }
    else if (op == 6) {
        cout << "\n===== DETALHES DA ACADEMIA =====\n\n";
        cout << "Nome: " << g.getNomeAcademia() << "\n";
        int max = g.getMaxAlunos();
        if (max == 0) cout << "Limite maximo de alunos: sem limite\n";
        else cout << "Limite maximo de alunos: " << max << "\n";
        cout << "Horarios:\n";
        g.listarHorarios();
        cout << "\n=====================================\n";
    }
    }
}

void submenuPlanos(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n====================== Gerenciar Planos =====================\n";
        cout << "1. Cadastrar plano personalizado\n";
        cout << "2. Listar planos\n";
        cout << "3. Remover plano\n";
        cout << "4. Editar plano\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; cin >> op; cin.ignore();
        if (op == 1) {
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
        } else if (op == 2) {
            cout << "\n======= LISTA DE PLANOS =======\n\n";
            g.listarPlanos();

        } else if (op == 3) {
            int id; cout << "ID do plano a remover: "; cin >> id; cin.ignore();
            try { 
                g.removerPlanoPorId(id); 
                cout << "Plano removido.\n"; 
            }catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            }
        } else if (op == 4) {
            int id; cout << "ID do plano a editar: "; cin >> id; cin.ignore();
            auto p = g.buscarPlanoPorId(id);
            if (!p) { cout << "Plano nao encontrado.\n"; }
            else {
                cout << "Nova descrição (enter para manter): "; 
                string nova; 
                getline(cin, nova);
                cout << "Novo valor (enter para manter): "; 
                string vs; 
                getline(cin, vs);
                string novaDescricao = nova.empty() ? p->getDescricao() : nova;
                double novoValor = vs.empty() ? p->calcularValor() : parseDoubleFromString(vs);
                if (g.editarPlano(id, novaDescricao, novoValor)){
                    cout << "Plano atualizado.\n"; 
                } else{
                    cout << "Falha ao atualizar (descricao duplicada?).\n";
                } 
                    
            }
        }
    }
}

void submenuProfessores(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n======= Gerenciar Professores =======\n";
        cout << "1. Adicionar professor\n";
        cout << "2. Remover professor\n";
        cout << "3. Listar professores\n";
        cout << "4. Atribuir professor a aula\n";
        cout << "5. Ver aulas de um professor\n";
        cout << "6. Ver alunos ligados a professor\n";
        cout << "7. Editar professor\n";
        cout << "8. Adicionar aula\n";
        cout << "9. Remover aula\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; cin >> op; cin.ignore();
        if (op == 1) {
            string nome, tel, esp; 
            cout << "Nome: "; 
            getline(cin, nome); 
            cout << "Telefone: "; 
            getline(cin, tel); 
            cout << "Especialidade: "; 
            getline(cin, esp);
            g.adicionarProfessor(Professor(0, nome, tel, esp));
            cout << "Professor adicionado com sucesso.\n";
        } else if (op == 2) {
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
        } else if (op == 3) { 
            g.listarProfessores(); 
        }
        else if (op == 4) {
            int id; string nomeAula; cout << "ID do professor: "; cin >> id; cin.ignore(); cout << "Nome da aula: "; getline(cin, nomeAula);
            try { g.atribuirProfessorAAula(id, nomeAula); cout << "Professor atribuido a aula.\n"; } catch (const exception &e) { cout << "Erro: " << e.what() << "\n"; }
        } else if (op == 5) {
            int id; cout << "ID do professor: "; cin >> id; cin.ignore(); auto aulas = g.listarAulasDoProfessor(id);
            cout << "\n===== AULAS DO PROFESSOR =====\n\n";
            if (aulas.empty()) cout << "Nenhuma aula.\n"; else for (auto &n : aulas) cout << n << "\n";
        } else if (op == 6) {
            int id; cout << "ID do professor: "; cin >> id; cin.ignore(); auto alunos = g.listarAlunosDoProfessor(id);
            cout << "\n===== ALUNOS DO PROFESSOR =====\n\n";
            if (alunos.empty()) cout << "Nenhum aluno ligado.\n"; else for (auto &a : alunos) cout << a << "\n";
        } else if (op == 7) {
            int id; cout << "ID do professor a editar: "; cin >> id; cin.ignore(); Professor *p = g.buscarProfessorPorId(id);
            if (!p) { cout << "Professor nao encontrado.\n"; }
            else {
                cout << "Novo nome (enter para manter): "; string nn; getline(cin, nn); if (!nn.empty()) p->setNome(nn);
                cout << "Novo telefone (enter para manter): "; string nt; getline(cin, nt); if (!nt.empty()) p->setTelefone(nt);
                cout << "Nova especialidade (enter para manter): "; string ne; getline(cin, ne); if (!ne.empty()) p->setEspecialidade(ne);
                cout << "Professor atualizado.\n";
            }
        } else if (op == 8) {
            string nome; 
            int id; 
            cout << "Nome da aula: "; 
            getline(cin, nome); 
            cout << "ID do professor (0 para nenhum): "; 
            cin >> id; 
            cin.ignore(); 
            Professor *p = nullptr; 
            if (id != 0) p = g.buscarProfessorPorId(id); 
            try { 
                g.adicionarAula(std::make_shared<Aula>(nome, p)); 
                cout << "Aula adicionada.\n"; 
            } catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            }
        } else if (op == 9) {
            string nome; 
            cout << "Nome da aula a remover: "; 
            getline(cin, nome); 
            try { 
                g.removerAula(nome); 
                cout << "Aula removida.\n"; 
            } catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            }
        }
    }
}

void submenuAlunos(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n-- Gerenciar Alunos --\n";
        cout << "1. Adicionar aluno\n";
        cout << "2. Listar alunos\n";
        cout << "3. Remover aluno\n";
        cout << "4. Matricular aluno em aula\n";
        cout << "5. Editar aluno\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; cin >> op; cin.ignore();
        if (op == 1) {
            string nome, tel; 
            cout << "Nome: "; 
            getline(cin, nome); 
            cout << "Telefone: "; 
            getline(cin, tel);
            Aluno a(nome, tel);
            // escolher plano
            cout << "Deseja atribuir um plano agora? (s/n): "; 
            char r; 
            cin >> r; 
            cin.ignore();
            if (r == 's' || r == 'S') {
                g.listarPlanos();
                cout << "Digite o ID do plano existente, 'novo' para criar ou 0 para nenhum: "; 
                string escolha; 
                getline(cin, escolha);
                if (escolha == "novo") {
                    string d; 
                    string vs; 
                    double v; 
                    cout << "Descricao: "; 
                    getline(cin, d); 
                    cout << "Valor: ";
                    getline(cin, vs);
                    cout << "\n===== TREINOS DO ALUNO =====\n\n";
                    v = parseDoubleFromString(vs);
                    g.adicionarPlanoPersonalizado(d, v);
                    auto p = g.buscarPlanoPorDescricao(d); 
                    if (p) a.setPlano(p.get());
                } else {
                    try {
                        int id = stoi(escolha);
                        if (id == 0) { 
                            cout << "Digite um ID válido.\n";
                         }
                        else {
                            auto p = g.buscarPlanoPorId(id);
                            if (p) {
                                a.setPlano(p.get()); 
                            }else {
                                cout << "Plano nao encontrado pelo ID.\n";
                            }
                        }
                    } catch (...) {
                        // tentar por descricao como fallback
                        auto p = g.buscarPlanoPorDescricao(escolha); 
                        if (p) a.setPlano(p.get()); else cout << "Plano nao encontrado.\n";
                    }
                }
            }
            try {
                g.adicionarAluno(a);
                cout << "Aluno adicionado.\n";
            } catch (const std::exception &e) {
                cout << "Erro ao adicionar aluno: " << e.what() << "\n";
            }
        } else if (op == 2) { 
            g.listarAlunos(); 
        }else if (op == 3) { 
            int mat; 
            cout << "Matricula: "; 
            cin >> mat; 
            cin.ignore(); 
            try { 
                g.removerAluno(mat); 
                cout << "Removido.\n"; 
            } catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            } 
        }
        else if (op == 4) {
            int mat; 
            string nomeAula; 
            cout << "Matricula: "; 
            cin >> mat; 
            cin.ignore(); 
            cout << "Nome da aula: "; 
            getline(cin, nomeAula);
            try { 
                g.matricularAlunoEmAula(mat, nomeAula); 
                cout << "Aluno matriculado.\n"; 
            } catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            }
        }
        else if (op == 5) {
            int mat; 
            cout << "Matricula do aluno a editar: "; 
            cin >> mat; 
            cin.ignore(); 
            Aluno *a = g.buscarAlunoPorMatricula(mat);
            if (!a) { 
                cout << "Aluno nao encontrado.\n"; continue; 
            }
            int eop = -1;
            while (eop != 0) {
                cout << "\n-- Editar Aluno (" << a->getMatricula() << ") --\n";
                cout << "1. Mudar nome\n";
                cout << "2. Mudar telefone\n";
                cout << "3. Mudar plano\n";
                cout << "4. Atribuir/Remover professor\n";
                cout << "0. Voltar\n";
                cout << "Opcao: "; cin >> eop; cin.ignore();
                if (eop == 1) { 
                    string nn; 
                    cout << "Novo nome: "; 
                    getline(cin, nn); 
                    a->setNome(nn); 
                    cout << "Nome atualizado.\n"; 
                }else if (eop == 2) { 
                    string nt; 
                    cout << "Novo telefone: "; 
                    getline(cin, nt); 
                    a->setTelefone(nt); 
                    cout << "Telefone atualizado.\n"; 
                }else if (eop == 3) {
                    g.listarPlanos(); 
                    cout << "Digite o ID do plano existente, 'novo' para criar ou 0 para remover: "; string escolha; 
                    getline(cin, escolha);
                    if (escolha == "novo") {
                        string d; 
                        string vs; 
                        double v; 
                        cout << "Descricao: "; 
                        getline(cin, d); 
                        cout << "Valor: "; 
                        getline(cin, vs); 
                        v = parseDoubleFromString(vs); 
                        g.adicionarPlanoPersonalizado(d, v); 
                        auto p = g.buscarPlanoPorDescricao(d); 
                        if (p) { 
                            a->setPlano(p.get()); 
                            cout << "Plano atualizado.\n"; 
                        }
                    } else {
                        try {
                            int id = stoi(escolha);
                            if (id == 0) { 
                                a->setPlano(nullptr); 
                                cout << "Plano removido do aluno.\n"; 
                            }
                            else {
                                auto p = g.buscarPlanoPorId(id);
                                if (p) { 
                                    a->setPlano(p.get()); 
                                    cout << "Plano atualizado.\n"; 
                                } else {
                                    cout << "Plano nao encontrado pelo ID.\n";
                                }
                            }
                        } catch (...) {
                            auto p = g.buscarPlanoPorDescricao(escolha); 
                            if (p) { 
                                a->setPlano(p.get()); 
                                cout << "Plano atualizado.\n"; 
                            } else {
                                cout << "Plano nao encontrado.\n";
                            }
                        }
                    }
                }
                else if (eop == 4) {
                    cout << "Professores:\n"; 
                    g.listarProfessores(); 
                    cout << "Digite ID do professor para atribuir (0 para remover): "; 
                    int id; 
                    cin >> id; 
                    cin.ignore();
                    if (id == 0) { 
                        a->setProfessor(nullptr); 
                        cout << "Professor removido do aluno.\n"; 
                    }
                    else { 
                        Professor *p = g.buscarProfessorPorId(id); 
                        if (!p) cout << "Professor nao encontrado.\n"; 
                        else { 
                            a->setProfessor(p); 
                            cout << "Professor atribuido.\n"; 
                        } 
                    }
                }
            }
        }
    }
}

void submenuEquipamentos(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n-- Gerenciar Equipamentos --\n";
        cout << "1. Adicionar equipamento\n";
        cout << "2. Listar equipamentos\n";
        cout << "3. Remover equipamento\n";
        cout << "4. Editar equipamento\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; 
        cin >> op; 
        cin.ignore();
        if (op == 1) { 
            string nome; 
            int qtd; 
            cout << "Nome: "; 
            getline(cin, nome); 
            cout << "Quantidade: "; 
            cin >> qtd; 
            cin.ignore(); 
            g.adicionarEquipamento(Equipamento(nome, qtd)); 
        }else if (op == 2) {
            g.listarEquipamentos();
        } else if (op == 3) { 
            string nome; 
            cout << "Nome do equipamento: "; 
            getline(cin, nome); 
            try { 
                g.removerEquipamento(nome); 
                cout << "Removido.\n"; 
            } catch (const exception &e) { 
                cout << "Erro: " << e.what() << "\n"; 
            } 
        }
        else if (op == 4) {
            string nome; 
            cout << "Nome do equipamento a editar: "; 
            getline(cin, nome);
            Equipamento *e = g.buscarEquipamentoPorNome(nome);
            if (!e) { 
                cout << "Equipamento nao encontrado.\n"; 
            }
            else {
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
                    } catch (...) {} }
                cout << "Equipamento atualizado.\n";
            }
        }
    }
}

void submenuTreinos(Gerenciador &g) {
    int op = -1;
    while (op != 0) {
        cout << "\n-- Gerenciar Treinos --\n";
        cout << "1. Adicionar treino a aluno\n";
        cout << "2. Listar treinos de um aluno\n";
        cout << "3. Editar treino de um aluno\n";
        cout << "0. Voltar\n";
        cout << "Opcao: "; 
        cin >> op; 
        cin.ignore();
        if (op == 1) {
            int mat; 
            cout << "Matricula: "; 
            cin >> mat; 
            cin.ignore(); 
            Aluno *a = g.buscarAlunoPorMatricula(mat);
            if (!a) { 
                cout << "Aluno nao encontrado.\n"; 
                continue; 
            }
            string nome, data; 
            cout << "Nome do treino: "; 
            getline(cin, nome); 
            cout << "Data: "; 
            getline(cin, data);
            Treino t(nome, data);
            cout << "Adicionar equipamento? (s/n): "; 
            char resposta; 
            cin >> resposta; 
            cin.ignore(); 
            while (resposta =='s'||resposta=='S') {
                 string en; int q; 
                 cout << "Nome eq: "; 
                 getline(cin, en); 
                 cout << "Qtd: "; 
                 cin >> q; 
                 cin.ignore(); t += Equipamento(en,q); 
                 cout << "Mais? (s/n): "; 
                 cin >> resposta; 
                 cin.ignore(); 
                }
            a->adicionarTreino(t);
            cout << "Treino adicionado.\n";
        } else if (op == 2) {
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
            }else { 
                for (const auto &t : tr) { 
                    cout << t.getNome() << " | " << t.getData() << "\n"; 
                } 
            }
        } else if (op == 3) {
                int matricula; 
                cout << "Matricula: "; 
                cin >> matricula; 
                cin.ignore(); 
                Aluno *a = g.buscarAlunoPorMatricula(matricula);
                if (!a) { 
                    cout << "Aluno nao encontrado.\n"; 
                    continue; 
                }
                auto &tr = const_cast<std::vector<Treino>&>(a->getTreinos());
                if (tr.empty()) { 
                    cout << "Nenhum treino.\n"; 
                    continue; 
                }
                for (size_t i = 0; i < tr.size(); ++i) {
                    cout << i+1 << ". " << tr[i].getNome() << " | " << tr[i].getData() << "\n";
                }
                cout << "Escolha o numero do treino a editar: "; 
                int idx; 
                cin >> idx; 
                cin.ignore(); 
                if (idx < 1 || idx > (int)tr.size()) { 
                    cout << "Indice invalido.\n"; 
                    continue; 
                }
                Treino &t = tr[idx-1];
                cout << "Novo nome (enter para manter): "; 
                string novoNome; 
                getline(cin, novoNome); 
                if (!novoNome.empty()) t.setNome(novoNome);
                cout << "Nova data (enter para manter): "; 
                string novaData; getline(cin, novaData); if (!novaData.empty()) t.setData(novaData);
                // editar equipamentos
                int equipamentoOp = -1;
                while (equipamentoOp != 0) {
                    cout << "\nEquipamentos do treino:\n";
                    const auto &eqs = t.getEquipamentos();
                    for (size_t i = 0; i < eqs.size(); ++i) {
                        cout << i+1 << ". " << eqs[i] << "\n";
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
                        t += Equipamento(equipamentoNovo,quantidade); 
                        cout << "Equipamento adicionado.\n"; }
                    else if (equipamentoOp == 2) { 
                        string equipamento; 
                        cout << "Nome do equipamento a remover: "; 
                        getline(cin, equipamento); 
                        if (t.removerEquipamentoPorNome(equipamento)) {
                            cout << "Removido.\n";
                        } else {
                            cout << "Equipamento nao encontrado no treino.\n"; 
                        }
                    }else if (equipamentoOp == 3) { 
                        string equipamento; 
                        cout << "Nome do equipamento: "; 
                        getline(cin, equipamento); 
                        cout << "Nova quantidade: "; 
                        int novaQuantidade; 
                        cin >> novaQuantidade; 
                        cin.ignore(); 
                        if (t.editarQuantidadeEquipamento(equipamento, novaQuantidade)){ 
                            cout << "Quantidade atualizada.\n"; 
                        }else {
                            cout << "Equipamento nao encontrado.\n"; 
                        }
                    }
                }
                cout << "Treino atualizado.\n";
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
        cout << "0. Sair\n";
        cout << "Escolha: "; cin >> opcao; cin.ignore();
        if (opcao == 1) submenuAcademia(g);
        else if (opcao == 2) submenuAlunos(g);
        else if (opcao == 3) submenuProfessores(g);
        else if (opcao == 4) submenuPlanos(g);
        else if (opcao == 5) submenuEquipamentos(g);
        else if (opcao == 6) submenuTreinos(g);
    }
    return 0;
}
