#pragma once

#include <queue>
#include <vector>
#include <iostream>
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

    // Visualiza a fila em ordem de prioridade sem esvaziá-la
    void visualizarFila() const {
        // 1. Cria uma cópia da fila original.
        //    Como este método é 'const', 'fila' não pode ser modificada.
        auto filaCopia = fila; 

        std::cout << "--- Fila de Atendimento Atual (" << filaCopia.size() << " pacientes) ---" << std::endl;
        
        if (filaCopia.empty()) {
            std::cout << "[Fila Vazia]" << std::endl;
            return;
        }

        // 2. Itera sobre a CÓPIA, removendo e imprimindo cada elemento.
        int posicao = 1;
        while (!filaCopia.empty()) {
            // Pega o paciente do topo (maior prioridade)
            Paciente* p = filaCopia.top();
            
            // Remove o paciente da cópia
            filaCopia.pop(); 

            // Imprime as informações
            // (Assumindo que Paciente tem um método getNome())
            std::cout << posicao << ". "
                      << "Nome: " << p->getNome()
                      << " (Prioridade: " << p->getPrioridade() << ")" 
                      << std::endl;
            
            posicao++;
        }
    }
};