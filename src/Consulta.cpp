#include "Consulta.h"
#include "Paciente.h"
#include "Medico.h"
#include "Hospital.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string Consulta::toJSONString() const {
    json j = {
        {"id", id},
        {"paciente", paciente->getNome()},
        {"medico", medico->getNome()},
        {"data", data},
        {"status", status}
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
        return nullptr;
    }
    
    return new Consulta(j["id"], p, m, j["data"]);
}
