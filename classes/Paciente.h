#pragma once
#include "Pessoa.h" 
#include <string>

class Paciente : public Pessoa {
private:
    int prioridade;
    std::string historicoMedico;

public:
    Paciente(std::string nome, int idade, int prioridade, std::string historico = "");

    void setPrioridade(int p);
    void setHistorico(std::string historico);
    
    int getPrioridade() const;
    std::string getHistorico() const;
};