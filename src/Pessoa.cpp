#include "Pessoa.h"
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Pessoa::Pessoa(std::string nome, int idade) {
    setNome(nome);
    setIdade(idade);
}

void Pessoa::setNome(std::string nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome nao pode ser vazio.");
    }
    this->nome = nome;
}

void Pessoa::setIdade(int idade) {
    if (idade <= 0) { 
        throw std::invalid_argument("Idade deve ser maior que zero.");
    }
    this->idade = idade;
}

std::string Pessoa::getNome() const {
    return this->nome;
}

int Pessoa::getIdade() const {
    return this->idade;
}

std::string Pessoa::toJSONString() const {
    json j = {
        {"nome", nome},
        {"idade", idade}
    };
    return j.dump();
}