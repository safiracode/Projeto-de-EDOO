#pragma once
#include "Pessoa.h" // Inclui a classe base
#include <string>

/*
 * Classe Derivada. Herda de 'Pessoa' e adiciona
 * atributos específicos do Paciente (prioridade, historicoMedico).
 */
class Paciente : public Pessoa {
private:
    int prioridade;
    std::string historicoMedico;

public:
    /*
     * Construtor: Coleta dados para si e para a classe base.
     * Repassa 'nome' e 'idade' para o construtor 'Pessoa'.
     * O 'historico' é opcional.
     */
    Paciente(std::string nome, int idade, int prioridade, std::string historico = "");

    /*
     * Setters: Validam e definem os atributos de Paciente.
     * 'setPrioridade' rejeita valores != 0 e != 1.
     */
    void setPrioridade(int p);
    void setHistorico(std::string historico);
    
    /*
     * Getters: Fornecem acesso de leitura.
     * 'getPrioridade' é crucial para a Fila de Atendimento
     * (de Safira) funcionar corretamente.
     */
    int getPrioridade() const;
    std::string getHistorico() const;

    /*
     * Serialização Polimórfica (Override):
     * Substitui 'toJSONString' de 'Pessoa'.
     * Irá chamar 'Pessoa::toJSONString()' e adicionar
     * 'prioridade' e 'historicoMedico' ao JSON.
     */
    std::string toJSONString() const override;

    /*
     * Método de Fábrica Estático (Desserialização):
     * Converte uma string JSON de volta em um novo objeto 'Paciente*'.
     * Usado para carregar dados do disco.
     */
    static Paciente* fromJSONString(const std::string& jsonStr);
};