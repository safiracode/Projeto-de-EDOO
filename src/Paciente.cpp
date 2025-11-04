#include "Paciente.h"
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Paciente::Paciente(std::string nome, int idade, int prioridadeVulnerabilidade, std::string historico)
    : Pessoa(nome, idade),
      historicoMedico(historico)
{
    setPrioridadeVulnerabilidade(prioridadeVulnerabilidade); 
}

void Paciente::setPrioridadeVulnerabilidade(int p) {
    if (p < 1 || p > 2) { 
        throw std::invalid_argument("Prioridade de vulnerabilidade invalida. Use 1 (Alto Risco) ou 2 (Baixo Risco).");
    }
    this->prioridadeVulnerabilidade = p;
}

int Paciente::getPrioridadeVulnerabilidade() const {
    return this->prioridadeVulnerabilidade;
}

void Paciente::setHistorico(std::string historico) {
    this->historicoMedico = historico;
}

std::string Paciente::getHistorico() const {
    return this->historicoMedico;
}

// --- Métodos JSON ---
std::string Paciente::toJSONString() const {
    json j = json::parse(Pessoa::toJSONString());
    j["prioridadeVulnerabilidade"] = prioridadeVulnerabilidade;
    j["historicoMedico"] = historicoMedico;
    return j.dump();
}

Paciente* Paciente::fromJSONString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return new Paciente(
        j["nome"],
        j["idade"],
        j["prioridadeVulnerabilidade"],
        j.value("historicoMedico", "")
    );
}