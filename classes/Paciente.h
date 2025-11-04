#pragma once
#include "Pessoa.h" 
#include <string>

class Paciente : public Pessoa {
private:
    int prioridade;
    std::string historicoMedico;

    // Prioridade pra quem chega antes quem chegou antes.
    long long ordemChegada;

public:
    Paciente(std::string nome, int idade, int prioridade, std::string historico = "");

    void setPrioridade(int p);
    void setHistorico(std::string historico);
    
    int getPrioridade() const;
    std::string getHistorico() const;

    // Métodos para controlar a ordem de chegada
    void setOrdemChegada(long long ordem);
    long long getOrdemChegada() const;


    // Serialização JSON (implementado em Paciente.cpp)
    std::string toJSONString() const override;
    static Paciente* fromJSONString(const std::string& jsonStr);
};