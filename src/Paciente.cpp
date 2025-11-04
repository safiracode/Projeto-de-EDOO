#include "Paciente.h"
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Paciente::Paciente(std::string nome, int idade, int prioridade, std::string historico)
    : Pessoa(nome, idade),
      historicoMedico(historico),
      ordemChegada(0) // Inicializa com 0 por padrão
{
    setPrioridade(prioridade); 
}

void Paciente::setPrioridade(int p) {
    // A fila (FilaAtendimento.cpp) usa prioridades 1, 2 e 3.
    if (p < 1 || p > 3) { 
        throw std::invalid_argument("Prioridade invalida. Use 1 (Emergência), 2 (Urgência média) ou 3 (Estável).");
    }
    this->prioridade = p;
}

int Paciente::getPrioridade() const {
    return this->prioridade;
}

void Paciente::setHistorico(std::string historico) {
    this->historicoMedico = historico;
}

std::string Paciente::getHistorico() const {
    return this->historicoMedico;
}

void Paciente::setOrdemChegada(long long ordem) {
    this->ordemChegada = ordem;
}

long long Paciente::getOrdemChegada() const {
    return this->ordemChegada;
}

std::string Paciente::toJSONString() const {
    json j = json::parse(Pessoa::toJSONString());
    j["prioridade"] = prioridade;
    j["historicoMedico"] = historicoMedico;
    return j.dump();
}

Paciente* Paciente::fromJSONString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return new Paciente(
        j["nome"],
        j["idade"],
        j["prioridade"],
        j.value("historicoMedico", "")
    );
}