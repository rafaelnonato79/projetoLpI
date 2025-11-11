// src/FormaPagamento.cpp
#include "../header/FormaPagamento.h"
#include <iostream>

FormaPagamento::FormaPagamento() : nome("") {}

FormaPagamento::FormaPagamento(const std::string& nome) : nome(nome) {}

std::string FormaPagamento::getNome() const {
    return nome;
}

void FormaPagamento::setNome(const std::string& nome) {
    if (nome.empty()) {
        throw MesmoIdExcecao("O nome da forma de pagamento não pode ser vazio.");
    }
    this->nome = nome;
}

// Implementação da sobrecarga do operador << (Requisito 5b)
std::ostream& operator<<(std::ostream& os, const FormaPagamento& fp) {
    os << "Forma de Pagamento: " << fp.nome;
    return os;
}