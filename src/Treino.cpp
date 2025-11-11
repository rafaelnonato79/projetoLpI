#include "../header/Treino.h"
#include "../header/Equipamento.h"
#include <algorithm>

Treino::Treino(const std::string &nome, const std::string &data) : nome(nome), data(data) {}

std::string Treino::getNome() const { return nome; }

std::string Treino::getData() const { return data; }

void Treino::adicionarEquipamento(const Equipamento &e) { equipamentos.push_back(e); }

const std::vector<Equipamento> &Treino::getEquipamentos() const { return equipamentos; }

Treino &Treino::operator+=(const Equipamento &e) {
    equipamentos.push_back(e);
    return *this;
}

void Treino::setNome(const std::string &n) { nome = n; }

void Treino::setData(const std::string &d) { data = d; }

bool Treino::removerEquipamentoPorNome(const std::string &nome) {
    auto it = std::remove_if(equipamentos.begin(), equipamentos.end(), [&](const Equipamento &e) { return e.getNome() == nome; });
    if (it == equipamentos.end()) return false;
    equipamentos.erase(it, equipamentos.end());
    return true;
}

bool Treino::editarQuantidadeEquipamento(const std::string &nome, int novaQuantidade) {
    for (auto &e : equipamentos) {
        if (e.getNome() == nome) { e.setQuantidade(novaQuantidade); return true; }
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Treino &t) {
    os << t.getNome() << " | " << t.getData();
    const auto &eqs = t.getEquipamentos();
    if (!eqs.empty()) {
        os << " | Equipamentos: ";
        for (size_t i = 0; i < eqs.size(); ++i) {
            os << eqs[i];
            if (i + 1 < eqs.size()) os << ", ";
        }
    }
    return os;
}
