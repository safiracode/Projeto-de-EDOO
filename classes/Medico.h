#pragma once
#include <string>

/*
 * Stub da classe Medico.
 * Eduardo deve implementar o resto depois
 */
class Medico {
private:
    std::string nome;

public:

    Medico(std::string n) : nome(n) {}

    std::string getNome() const {
        return this->nome;
    }
};