#include "Medico.h"
#include <stdexcept>

Medico::Medico(std::string nome, int idade, std::string crm, std::string especialidade)
    : Pessoa(nome, idade), 
      especialidade(especialidade) 
{
    
    setCRM(crm); 
}
// FALTA SET ESPECIALIDADE -------------------
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