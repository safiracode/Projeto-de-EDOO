#include "Paciente.h"
#include <stdexcept>

Paciente::Paciente(std::string nome, int idade, int prioridade, std::string historico)
    : Pessoa(nome, idade),
      historicoMedico(historico) 
{
    setPrioridade(prioridade); 
}

void Paciente::setPrioridade(int p) {
    if (p < 0 || p > 1) { 
        throw std::invalid_argument("Prioridade invalida. Use 0 (normal) ou 1 (emergencia).");
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