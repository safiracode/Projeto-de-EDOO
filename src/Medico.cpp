#include "Medico.h"
#include <stdexcept>

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