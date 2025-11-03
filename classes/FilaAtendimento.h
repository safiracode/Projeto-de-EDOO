#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include "Paciente.h"
#include "ComparadorPaciente.h" 

class FilaAtendimento {
private:
    std::priority_queue<
        Paciente*,
        std::vector<Paciente*>,
        ComparadorPaciente
    > fila;

public:

    void adicionarPaciente(Paciente* p) {
        fila.push(p);
    }
    bool estaVazia() const {
        return fila.empty();
    }
    int tamanho() const {
        return fila.size();
    }

    Paciente* chamarProximo();
    void visualizarFila() const; 
};