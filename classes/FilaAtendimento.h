#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include "Consulta.h"
#include "ComparadorPaciente.h"

class FilaAtendimento {
private:
    std::priority_queue<
        Consulta*,
        std::vector<Consulta*>,
        ComparadorPaciente
    > fila;

    // Contador para garantir a ordem de chegada
    long long proximaOrdem;

public:
    // Construtor para inicializar nosso contador
    FilaAtendimento() : proximaOrdem(0) {}

    void adicionarConsulta(Consulta* c) {
        // Carimbamos a CONSULTA com a "senha" (ordem) atual
        c->setOrdemChegada(proximaOrdem);
        proximaOrdem++; // E incrementamos a senha para o próximo

        fila.push(c);
    }
    
    bool estaVazia() const {
        return fila.empty();
    }
    
    int tamanho() const {
        return fila.size();
    }

    Consulta* chamarProxima();
    
    void visualizarFila() const; 
};