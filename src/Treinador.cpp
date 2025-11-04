#include "Treinador.hpp"
#include <iostream>
using namespace std;

Treinador::Treinador() : Pessoa(), matriculaTreinador("") {}

Treinador::Treinador(const std::string& nome, const std::string& cpf, int idade,
                     const std::string& matriculaTreinador)
    : Pessoa(nome, cpf, idade), matriculaTreinador(matriculaTreinador) {}

void Treinador::setMatriculaTreinador(const std::string& matriculaTreinador) {
    this->matriculaTreinador = matriculaTreinador;
}

std::string Treinador::getMatriculaTreinador() const {
    return matriculaTreinador;
}

void Treinador::exibirDados() const {
    Pessoa::exibirDados();
    cout << "Matrícula do Treinador: " << matriculaTreinador << std::endl;
}
