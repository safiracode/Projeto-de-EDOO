#include "Paciente.h"
#include <stdexcept> // Para std::invalid_argument (lançado por setPrioridade)
#include <nlohmann/json.hpp> // Para a lógica de serialização/desserialização

using json = nlohmann::json;

/*
 * Implementação do Construtor de Paciente.
 * A sintaxe ': Pessoa(nome, idade)' chama o construtor da
 * classe base (Pessoa) ANTES que o corpo deste construtor execute.
 * O corpo então usa 'setPrioridade' para validar seus próprios dados.
 */
Paciente::Paciente(std::string nome, int idade, int prioridade, std::string historico)
    : Pessoa(nome, idade), // Chama o construtor da base
      historicoMedico(historico) // Inicializa o membro (opcional)
{
    setPrioridade(prioridade); // Usa o setter para validar a prioridade
}

/*
 * Implementação da regra de negócio para 'prioridade'.
 * Rejeita valores que não sejam 0 (normal) ou 1 (emergência),
 * lançando uma exceção que será capturada pelo 'main.cpp'.
 */
void Paciente::setPrioridade(int p) {
    if (p < 0 || p > 1) { 
        throw std::invalid_argument("Prioridade invalida. Use 0 (normal) ou 1 (emergencia).");
    }
    this->prioridade = p;
}

/*
 * Retorna o valor do atributo privado 'prioridade'.
 */
int Paciente::getPrioridade() const {
    return this->prioridade;
}

/*
 * Define o atributo 'historicoMedico'. Não há validação (vazio é ok).
 */
void Paciente::setHistorico(std::string historico) {
    this->historicoMedico = historico;
}

/*
 * Retorna o valor do atributo privado 'historicoMedico'.
 */
std::string Paciente::getHistorico() const {
    return this->historicoMedico;
}

/*
 * Implementação da Serialização (Override).
 * 1. Chama 'Pessoa::toJSONString()' para obter o JSON de 'nome' e 'idade'.
 * 2. Analisa (parse) essa string de volta para um objeto JSON.
 * 3. Adiciona os campos 'prioridade' e 'historicoMedico' a esse objeto.
 * 4. Retorna o JSON combinado como uma string.
 */
std::string Paciente::toJSONString() const {
    json j = json::parse(Pessoa::toJSONString()); // Reutiliza a lógica da base
    j["prioridade"] = prioridade;
    j["historicoMedico"] = historicoMedico;
    return j.dump();
}

/*
 * Implementação da Fábrica (Desserialização).
 * 1. Analisa (parse) a string JSON.
 * 2. Extrai os valores, usando 'j.value("historicoMedico", "")'
 * para tratar 'historicoMedico' como opcional (se não existir
 * no JSON, usa "" como padrão, evitando um erro).
 * 3. Cria e retorna um 'new Paciente' na memória (heap).
 */
Paciente* Paciente::fromJSONString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return new Paciente(
        j["nome"],
        j["idade"],
        j["prioridade"],
        j.value("historicoMedico", "") // .value() é seguro para chaves opcionais
    );
}