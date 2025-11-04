#include "Consulta.h"
#include "Paciente.h"
#include "Medico.h"
#include "Hospital.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string Consulta::toJSONString() const {
    json j = {
        {"id", id},
        {"paciente", paciente->getNome()}, // Salva o nome para busca
        {"medico", medico->getNome()},     // Salva o nome para busca
        {"data", data},
        {"status", status},

        {"prioridadeTriagem", prioridadeTriagem} 
    };
    return j.dump();
}

Consulta* Consulta::fromJSONString(const std::string& jsonStr, Hospital* hospital) {
    json j = json::parse(jsonStr);
    
    std::string nomePaciente = j["paciente"];
    std::string nomeMedico = j["medico"];
    
    Paciente* p = hospital->buscarPacientePorNome(nomePaciente);
    Medico* m = hospital->buscarMedicoPorNome(nomeMedico);
    
    if (p == nullptr || m == nullptr) {
        // Se não achar o paciente ou médico (ex: foram deletados),
        // não podemos recriar a consulta.
        return nullptr;
    }
    
    return new Consulta(
        j["id"], 
        p, 
        m, 
        j["data"],
        j["prioridadeTriagem"]
    );
}