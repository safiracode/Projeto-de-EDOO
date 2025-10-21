#pragma once

#include <queue>
#include <vector>
#include "Paciente.h"
#include "ComparadorPaciente.h" 

class FilaAtendimento {
private:
    /*
     * Esta é a declaração da fila.
     * 1. Tipo de dado: Paciente*
     * 2. Contêiner interno: std::vector<Paciente*>
     * 3. Classe de Comparação: ComparadorPaciente
     */
    std::priority_queue<
        Paciente*,
        std::vector<Paciente*>,
        ComparadorPaciente
    > fila;

public:
    // Adiciona um paciente à fila (respeitando a prioridade)
    void adicionarPaciente(Paciente* p) {
        fila.push(p);
    }

    // Retorna e remove o próximo paciente (o de maior prioridade)
    Paciente* chamarProximo() {
        if (fila.empty()) {
            return nullptr; // Retorna nulo se a fila estiver vazia
        }
        
        Paciente* proximo = fila.top(); // Pega o de maior prioridade
        fila.pop();                     // Remove da fila
        return proximo;
    }

    // Verifica se a fila está vazia
    bool estaVazia() const {
        return fila.empty();
    }

    int tamanho() const {
        return fila.size();
    }
};