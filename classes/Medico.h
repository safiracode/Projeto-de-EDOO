#pragma once
#include "Pessoa.h"
#include <string>

class Medico: public Pessoa {
private:
    std::string crm;
    std::string especialidade;

public:
    Medico(std::string nome, int idade, std::string crm, std::string especialidade);

    void setCRM(std::string crm);
    void setEspecialidade (std::string especialidade);

    std::string getCRM() const;
    std::string getEspecialidade() const;

    // Serialização JSON (implementado em Medico.cpp)
    std::string toJSONString() const override;
    static Medico* fromJSONString(const std::string& jsonStr);
};