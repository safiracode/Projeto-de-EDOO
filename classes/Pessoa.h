#pragma once
#include <string>

class Pessoa {
    private:
        std::string nome;
        int idade;

    public:
        //Função construtora
        Pessoa(std::string nome, int idade);

        //Função destrutora
        virtual ~Pessoa() = default;

        //Funções setters para definir o nome e a idade do objeto, respectivamente
        void setNome(std::string nome);
        void setIdade(int idade);

        //Funções getter para retornar um valor atribuido ao nome ou idade de um objeto
        virtual std::string getNome() const;
        int getIdade() const;

        // Serialização JSON (implementado em Pessoa.cpp)
        virtual std::string toJSONString() const;
};