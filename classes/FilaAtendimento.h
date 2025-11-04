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

    // Contador para garantir a ordem de chegada (FIFO)
    // Cada paciente que entrar receberá um número único e crescente.
    long long proximaOrdem;

public:
    // Construtor para inicializar nosso contador
    FilaAtendimento() : proximaOrdem(0) {}

    void adicionarPaciente(Paciente* p) {
        // Antes de adicionar, carimbamos o paciente com a "senha" (ordem) atual
        p->setOrdemChegada(proximaOrdem);
        proximaOrdem++; // E incrementamos a senha para o próximo

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