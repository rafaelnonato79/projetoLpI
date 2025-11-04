#include <iostream>
#include "Pessoa.hpp"
#include <string>
using namespace std;

Pessoa::Pessoa() : nome(""), cpf(""), idade(0) {}

Pessoa::Pessoa(const std::string& nome, const std::string& cpf, int idade)
    : nome(nome), cpf(cpf), idade(idade) {}

void Pessoa::setNome(const std::string& nome) {
    this->nome = nome;
}

void Pessoa::setCPF(const std::string& cpf) {
    this->cpf = cpf;
}

void Pessoa::setIdade(int idade) {
    this->idade = idade;
}

std::string Pessoa::getNome() const {
    return nome;
}

std::string Pessoa::getCPF() const {
    return cpf;
}

int Pessoa::getIdade() const {
    return idade;
}

void Pessoa::exibirDados() const {
    cout << "Nome: " << nome << std::endl;
    cout << "CPF: " << cpf << std::endl;
    cout << "Idade: " << idade << std::endl;
}
