#ifndef TREINADOR_HPP
#define TREINADOR_HPP

#include "Pessoa.hpp"
#include <string>
class Treinador : public Pessoa {
private:
    std::string matriculaTreinador;

public:
    Treinador();
    Treinador(const std::string& nome, const std::string& cpf, int idade,
              const std::string& matriculaTreinador);
    void setMatriculaTreinador(const std::string& matriculaTreinador);
    std::string getMatriculaTreinador() const;
        
    void exibirDados() const override;
};
#endif // TREINADOR_HPP