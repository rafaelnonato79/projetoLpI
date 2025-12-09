#include "../header/PlanoPersonalizado.h"

PlanoPersonalizado::PlanoPersonalizado() : Plano(), id(0) {}

PlanoPersonalizado::PlanoPersonalizado(const std::string &descricao,
                                       double valor)
    : Plano(descricao, valor), id(0) {}

size_t PlanoPersonalizado::getId() const { return id; }

void PlanoPersonalizado::setId(size_t i) { id = i; }

double PlanoPersonalizado::calcularValor() const { return Plano::valor; }

std::string PlanoPersonalizado::toFileString() const {
    return std::to_string(getId()) + ";" + descricao + ";" +
                 std::to_string(valor);
}

bool PlanoPersonalizado::fromFileString(const std::string &line) {
    size_t sep1 = line.find(';');
    if (sep1 == std::string::npos)
        return false;
    size_t sep2 = line.find(';', sep1 + 1);
    if (sep2 == std::string::npos)
        return false;
    try {
        id = static_cast<int>(std::stoul(line.substr(0, sep1)));
        descricao = line.substr(sep1 + 1, sep2 - sep1 - 1);
        valor = std::stod(line.substr(sep2 + 1));
    } catch (...) {
        return false;
    }
    return true;
}
