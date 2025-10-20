#pragma once
#include <string>

/*
 * Esta é uma versão "stub" (simulada) da classe Paciente.
 * Eduardo deve implementar o resto depois
 */
class Paciente {
private:
    std::string nome;
    int prioridade; // Vamos usar 0 = normal, 1 = emergência

public:
    Paciente(std::string n, int p) : nome(n), prioridade(p) {}

    int getPrioridade() const {
        return this->prioridade;
    }

    std::string getNome() const {
        return this->nome;
    }
};