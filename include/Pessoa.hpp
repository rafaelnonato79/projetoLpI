#ifindef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include <string>
using namespace std;

class Pessoa {
protected:
    std::string nome;
    std::string cpf;
    int idade;

public:
    Pessoa();
    Pessoa(const std::string& nome, const std::string& cpf, int idade);

    void setNome(const std::string& nome);
    void setCPF(const std::string& cpf);
    void setIdade(int idade);

    std::string getNome() const;
    std::string getCPF() const;
    int getIdade() const;

    virtual void exibirDados() const;
    virtual ~Pessoa() {}
};
