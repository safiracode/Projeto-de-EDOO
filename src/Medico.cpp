#include "Medico.h"
#include <stdexcept> // Para std::invalid_argument (lançado pelos setters)
#include <nlohmann/json.hpp> // Para a lógica de serialização/desserialização

using json = nlohmann::json;

/*
 * Implementação do Construtor de Medico.
 * A sintaxe ': Pessoa(nome, idade)' chama o construtor da
 * classe base (Pessoa) ANTES que o corpo deste construtor execute.
 * O corpo então usa 'setCRM' para validar seus próprios dados.
 */
Medico::Medico(std::string nome, int idade, std::string crm, std::string especialidade)
    : Pessoa(nome, idade), // Chama o construtor da base
      especialidade(especialidade) // Inicializa o membro
{
    setCRM(crm); // Usa o setter para validar o CRM
}

/*
 * Implementação da regra de negócio para 'especialidade'.
 * Rejeita strings vazias, lançando uma exceção.
 */
void Medico::setEspecialidade(std::string especialidade) {
    if (especialidade.empty()) {
        throw std::invalid_argument("Especialidade nao pode ser vazia.");
    }
    this->especialidade = especialidade;
}

/*
 * Implementação da regra de negócio para 'crm'.
 * Rejeita strings vazias, lançando uma exceção.
 */
void Medico::setCRM(std::string crm) {
    if (crm.empty()) {
        throw std::invalid_argument("CRM nao pode ser vazio.");
    }
    this->crm = crm;
}

/*
 * Retorna o valor do atributo privado 'crm'.
 */
std::string Medico::getCRM() const {
    return this->crm;
}

/*
 * Retorna o valor do atributo privado 'especialidade'.
 */
std::string Medico::getEspecialidade() const {
    return this->especialidade;
}

/*
 * Implementação da Serialização (Override).
 * 1. Chama 'Pessoa::toJSONString()' para obter o JSON de 'nome' e 'idade'.
 * 2. Analisa (parse) essa string de volta para um objeto JSON.
 * 3. Adiciona os campos 'crm' e 'especialidade' a esse objeto.
 * 4. Retorna o JSON combinado como uma string.
 */
std::string Medico::toJSONString() const {
    json j = json::parse(Pessoa::toJSONString()); // Reutiliza a lógica da base
    j["crm"] = crm;
    j["especialidade"] = especialidade;
    return j.dump();
}

/*
 * Implementação da Fábrica (Desserialização).
 * 1. Analisa (parse) a string JSON.
 * 2. Extrai os valores usando as chaves ("nome", "idade", etc.).
 * 3. Cria e retorna um 'new Medico' na memória (heap)
 * usando os valores extraídos.
 */
Medico* Medico::fromJSONString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return new Medico(
        j["nome"],
        j["idade"],
        j["crm"],
        j["especialidade"]
    );
}