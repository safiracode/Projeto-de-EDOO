#pragma once
#include "Pessoa.h"
#include "FilaAtendimento.h" // Incluímos a definição da Fila
#include <string>

class Medico: public Pessoa {
private:
    std::string crm;
    std::string especialidade;

    FilaAtendimento filaDeAtendimento;

public:
    Medico(std::string nome, int idade, std::string crm, std::string especialidade);

    void setCRM(std::string crm);
    void setEspecialidade (std::string especialidade);

    std::string getCRM() const;
    std::string getEspecialidade() const;

    // Métodos para acessar a fila deste médico
    // Retorna uma referência para a fila, para que possamos
    // adicionar/remover consultas dela (ex: medico->getFila().adicionarConsulta(...))
    FilaAtendimento& getFila();
    const FilaAtendimento& getFila() const; // Versão 'const'

    // Serialização JSON
    std::string toJSONString() const override;
    static Medico* fromJSONString(const std::string& jsonStr);
};