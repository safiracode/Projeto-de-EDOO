#pragma once

#include <queue>  // Para std::priority_queue
#include <deque>  // <<< A Solução! O contêiner substituto do std::vector
#include "Paciente.h"
#include "ComparadorPaciente.h"

class FilaAtendimento {
private:
    /*
     * Estamos definindo nossa fila
     * de prioridade com 3 argumentos de template:
     * 1. Tipo de dado: Paciente*
     * 2. Contêiner interno: std::deque<Paciente*> (NÃO o std::vector padrão) pois assim evitamos o uso de vector
     * 3. Classe de Comparação: ComparadorPaciente
     */
    std::priority_queue<
        Paciente*,
        std::deque<Paciente*>, // << IMPORTANTE: Substitui o std::vector
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

    // (Opcional: Letícia pode usar esta função para ver o tamanho)
    int tamanho() const {
        return fila.size();
    }
};