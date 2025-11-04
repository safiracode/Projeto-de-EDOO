/*
 * Implementação da lógica de 'Pessoa.h'.
 */

#include "Pessoa.h"
#include <stdexcept> // Para std::invalid_argument (lançado pelos setters)
#include <nlohmann/json.hpp> // Para a lógica de serialização JSON

using json = nlohmann::json;

/*
 * Implementação do Construtor.
 * Chama os setters para garantir que um objeto Pessoa
 * nunca seja criado com dados inválidos (ex: idade negativa).
 */
Pessoa::Pessoa(std::string nome, int idade) {
    setNome(nome);
    setIdade(idade);
}

/*
 * Implementação da regra de negócio para 'nome'.
 * Rejeita nomes vazios lançando uma exceção que
 * será capturada pelo 'main.cpp'.
 */
void Pessoa::setNome(std::string nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome nao pode ser vazio.");
    }
    this->nome = nome;
}

/*
 * Implementação da regra de negócio para 'idade'.
 * Rejeita idades <= 0, lançando uma exceção.
 */
void Pessoa::setIdade(int idade) {
    if (idade <= 0) { 
        throw std::invalid_argument("Idade deve ser maior que zero.");
    }
    this->idade = idade;
}

/*
 * Retorna o valor do atributo privado 'nome'.
 */
std::string Pessoa::getNome() const {
    return this->nome;
}

/*
 * Retorna o valor do atributo privado 'idade'.
 */
int Pessoa::getIdade() const {
    return this->idade;
}

/*
 * Implementação da serialização base.
 * Cria um objeto JSON contendo apenas 'nome' e 'idade'
 * e o retorna como uma string.
 */
std::string Pessoa::toJSONString() const {
    json j = {
        {"nome", nome},
        {"idade", idade}
    };
    return j.dump(); // Converte o objeto nlohmann::json em string
}