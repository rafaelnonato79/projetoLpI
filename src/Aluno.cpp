#include "Aluno.hpp"
#include <iostream>
using namespace std;

Aluno::Aluno(const std::string& nome, const std::string& cpf, int idade,
             const std::string& endereco, const std::string& matricula)
    : Pessoa(nome, cpf, idade), endereco(endereco), matricula(matricula) {}

void Aluno::setEndereco(const std::string& endereco) {
    this->endereco = endereco;
}

void Aluno::setMatricula(const std::string& matricula) {
    this->matricula = matricula;
}

std::string Aluno::getEndereco() const {
    return endereco;
}

std::string Aluno::getMatricula() const {
    return matricula;
}

void Aluno::exibirDados() const {
    Pessoa::exibirDados();
    cout << "Endereço: " << endereco << std::endl;
    cout << "Matrícula: " << matricula << std::endl;
}
