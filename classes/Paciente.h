#pragma once
#include "Pessoa.h" 
#include <string>

/*
 * Classe Derivada. Herda de 'Pessoa' e adiciona
 * atributos específicos do Paciente (prioridade, historicoMedico).
 */
class Paciente : public Pessoa {
private:
    // Esta é a prioridade ESTRUTURAL (Nível 1 ou 2).
    // (1 = Crianças/Idosos/Alto Risco, 2 = Baixo Risco)
    int prioridadeVulnerabilidade;
    
    std::string historicoMedico;

public:
    /*
     * Construtor: Coleta dados para si e para a classe base.
     * Repassa 'nome' e 'idade' para o construtor 'Pessoa'.
     * O 'historico' é opcional.
     */
    Paciente(std::string nome, int idade, int prioridadeVulnerabilidade, std::string historico = "");

    // Métodos para a prioridade de vulnerabilidade (faixa etária)
    void setPrioridadeVulnerabilidade(int p);
    int getPrioridadeVulnerabilidade() const;

    void setHistorico(std::string historico);
    std::string getHistorico() const;

    // Serialização JSON
    std::string toJSONString() const override;
    static Paciente* fromJSONString(const std::string& jsonStr);
};