#pragma once
#include "Pessoa.h" // Inclui a classe base
#include <string>

/*
 * Classe Derivada. Herda de 'Pessoa' e adiciona
 * atributos específicos do Médico (crm, especialidade).
 */
class Medico: public Pessoa {
private:
    std::string crm;
    std::string especialidade;

public:
    /*
     * Construtor: Coleta dados para si e para a classe base.
     * Repassa 'nome' e 'idade' para o construtor 'Pessoa'.
     */
    Medico(std::string nome, int idade, std::string crm, std::string especialidade);

    /*
     * Setters: Validam e definem os atributos de Medico.
     * 'setCRM' e 'setEspecialidade' rejeitam strings vazias.
     */
    void setCRM(std::string crm);
    void setEspecialidade (std::string especialidade);

    /*
     * Getters: Fornecem acesso de leitura aos atributos de Medico.
     */
    std::string getCRM() const;
    std::string getEspecialidade() const;

    /*
     * Serialização Polimórfica (Override):
     * Substitui 'toJSONString' de 'Pessoa'.
     * Sua implementação irá *primeiro* chamar 'Pessoa::toJSONString()'
     * e *depois* adicionar 'crm' e 'especialidade' ao JSON.
     */
    std::string toJSONString() const override;

    /*
     * Método de Fábrica Estático (Desserialização):
     * 'static' significa que é chamado na classe (Medico::fromJSONString)
     * e não em um objeto. Converte uma string JSON de volta
     * em um novo objeto 'Medico*'. Usado para carregar dados do disco.
     */
    static Medico* fromJSONString(const std::string& jsonStr);
};