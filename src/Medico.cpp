#include "Medico.h"
#include <stdexcept>

Medico::Medico(std::string nome, int idade, std::string crm, std::string especialidade)
    : Pessoa(nome, idade), 
      especialidade(especialidade) 
{
    
    setCrm(crm); 
}

void Medico::setCrm(std::string crm) {
    if (crm.empty()) {
        throw std::invalid_argument("CRM nao pode ser vazio.");
    }
    this->crm = crm;
}

std::string Medico::getCrm() const {
    return this->crm;
}

std::string Medico::getEspecialidade() const {
    return this->especialidade;
}