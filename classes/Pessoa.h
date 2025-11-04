#pragma once
#include <string>

/*
 * Classe Base. Define os dados comuns (nome, idade) que
 * 'Paciente' e 'Medico' irão herdar.
 */
class Pessoa {
    private:
        std::string nome;
        int idade;

    public:
        /*
         * Construtor: Chamado pelas classes filhas (Paciente, Medico;
         * Força a validação dos dados no momento da criação ao chamar os setters 'setNome' e 'setIdade';
         */
        Pessoa(std::string nome, int idade);

        /*
         * Destrutor Virtual: Garante que, se um 'Paciente' ou 'Medico' for deletado através de um ponteiro 'Pessoa*', o destrutor correto da classe filha seja chamado;
         */
        virtual ~Pessoa() = default;

        /*
         * Setters: Implementam as regras de validação;
         * 'setNome' rejeita nomes vazios;
         * 'setIdade' rejeita idades não-positivas;
         */
        void setNome(std::string nome);
        void setIdade(int idade);

        /*
         * Getters: Fornecem acesso de leitura aos dados privados;
         */
        virtual std::string getNome() const;
        int getIdade() const;

        /*
         * Serialização Base: Converte *apenas* os dados de Pessoa (nome, idade)para uma string JSON;
         * É 'virtual' para que 'Paciente' e 'Medico' possam sobrescrevê-la e adicionar seus próprios dados;
         */
        virtual std::string toJSONString() const;
};