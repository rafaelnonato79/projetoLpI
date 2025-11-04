#ifndef ALUNO_HPP
#define ALUNO_HPP  

#include "Pessoa.hpp"
#include <string>
class Aluno : public Pessoa {
private:
    std::string endereco;
    std::string matricula;

public:
    Aluno(const std::string& nome, const std::string& cpf, int idade,
          const std::string& endereco, const std::string& matricula);

    void setEndereco(const std::string& endereco);
    void setMatricula(const std::string& matricula);

    std::string getEndereco() const;
    std::string getMatricula() const;

    void exibirDados() const override;
};
#endif // ALUNO_HPP