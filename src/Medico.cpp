#include "Medico.h"
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Medico::Medico(std::string nome, int idade, std::string crm, std::string especialidade)
    : Pessoa(nome, idade), 
      especialidade(especialidade) 
{
    
    setCRM(crm); 
}

void Medico::setEspecialidade(std::string especialidade) {
    if (especialidade.empty()) {
        throw std::invalid_argument("Especialidade nao pode ser vazia.");
    }
    this->especialidade = especialidade;
}

void Medico::setCRM(std::string crm) {
    if (crm.empty()) {
        throw std::invalid_argument("CRM nao pode ser vazio.");
    }
    this->crm = crm;
}

std::string Medico::getCRM() const {
    return this->crm;
}

std::string Medico::getEspecialidade() const {
    return this->especialidade;
}

std::string Medico::toJSONString() const {
    json j = json::parse(Pessoa::toJSONString());
    j["crm"] = crm;
    j["especialidade"] = especialidade;
    return j.dump();
}

Medico* Medico::fromJSONString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return new Medico(
        j["nome"],
        j["idade"],
        j["crm"],
        j["especialidade"]
    );
}