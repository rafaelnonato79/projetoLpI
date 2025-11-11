// #include "../header/Academia.h"
// #include "../header/LimiteExcedido.h"
// #include <stdexcept>

// Academia::Academia() : nome(""), maxAlunos(0) {}

// Academia::Academia(const std::string &nome, size_t maxAlunos,
//                    const std::vector<Treinador *> &treinadores,
//                    const std::vector<Aluno *> &alunos,
//                    const std::vector<Treino *> &treinos,
//                    const std::vector<Plano *> &planos)
//     : nome(nome), maxAlunos(maxAlunos), treinadores(treinadores),
//       alunos(alunos), treinos(treinos), planos(planos) {}

// void Academia::setAcademia(const std::string &nome, size_t maxAlunos,
//                            const std::vector<Treinador *> &treinadores,
//                            const std::vector<Aluno *> &alunos,
//                            const std::vector<Treino *> &treinos,
//                            const std::vector<Plano *> &planos) {
//   // this->nome = nome;
//   this->maxAlunos = maxAlunos;
//   this->treinadores = treinadores;
//   this->alunos = alunos;
//   this->treinos = treinos;
//   this->planos = planos;
// }

// std::string Academia::getNome() const { return nome; }

// void Academia::setNome(const std::string &nome) { this->nome = nome; }

// size_t Academia::getMaxAlunos() const { return maxAlunos; }

// void Academia::setMaxAlunos(size_t maxAlunos) { this->maxAlunos = maxAlunos; }



// void Academia::adicionarAluno(Aluno *aluno) {

//   if (alunos.size() >= maxAlunos) {
//     throw LimiteExcedido("Número máximo de alunos atingido!");
//   }

//   alunos.push_back(aluno);
// }

// void Academia::adicionarFormaPagamento(FormaPagamento *fp) {
//   formasPagamento.push_back(fp);
// }

// bool Academia::removerFormaPagamento(const std::string &nome) {
//    for (auto it = formasPagamento.begin(); it != formasPagamento.end(); ++it) {
//      if ((*it)->getNome() == nome) {
//         delete *it;
//         formasPagamento.erase(it);
//         return true;
//      }
//    }
//    return false;
// }

// FormaPagamento *Academia::buscarFormaPagamento(const std::string &nome) const {
//   for (auto *fp : formasPagamento) {
//       if (fp->getNome() == nome) {
//      return fp;
//     }
//   }
//   return nullptr;
// }

// void Academia::adicionarTreino(Treino *treino) { treinos.push_back(treino); }

// void Academia::adicionarPlano(Plano *plano) { planos.push_back(plano); }

// bool Academia::removerTreinador(const std::string &nome) {
//   for (auto it = treinadores.begin(); it != treinadores.end(); ++it) {
//     if ((*it)->getNome() == nome) {
//       delete *it;
//       treinadores.erase(it);
//       return true;
//     }
//   }
//   return false;
// }

// bool Academia::removerAluno(const std::string &nome) {
//   for (auto it = alunos.begin(); it != alunos.end(); ++it) {
//     if ((*it)->getNome() == nome) {
//       delete *it;
//       alunos.erase(it);
//       return true;
//     }
//   }
//   return false;
// }

// bool Academia::removerTreino(const std::string &nome) {
//   for (auto it = treinos.begin(); it != treinos.end(); ++it) {
//     if ((*it)->getNome() == nome) {
//       delete *it;
//       treinos.erase(it);
//       return true;
//     }
//   }
//   return false;
// }

// bool Academia::removerPlano(const std::string &nome) {
//   for (auto it = planos.begin(); it != planos.end(); ++it) {
//     if ((*it)->getNome() == nome) {
//       delete *it;
//       planos.erase(it);
//       return true;
//     }
//   }
//   return false;
// }


// Treinador *Academia::buscarTreinador(const std::string &nome) const {
//   for (auto *treinador : treinadores) {
//     if (treinador->getNome() == nome) {
//       return treinador;
//     }
//   }
//   return nullptr;
// }

// Aluno *Academia::buscarAluno(const std::string &nome) const {
//   for (auto *aluno : alunos) {
//     if (aluno->getNome() == nome) {
//       return aluno;
//     }
//   }
//   return nullptr;
// }

// Treino *Academia::buscarTreino(const std::string &nome) const {
//   for (auto *treino : treinos) {
//     if (treino->getNome() == nome) {
//       return treino;
//     }
//   }
//   return nullptr;
// }

// Plano *Academia::buscarPlano(const std::string &nome) const {
//   for (auto *plano : planos) {
//     if (plano->getNome() == nome) {
//       return plano;
//     }
//   }
//   return nullptr;
// }


