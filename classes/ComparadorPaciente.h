#pragma once
#include "Paciente.h"

// Define como comparar dois pacientes na fila
struct ComparadorPaciente {
    bool operator()(const Paciente* a, const Paciente* b) const {
        
        // 1. Critério Primário: Prioridade (1-Emergência, 2-Média, 3-Estável)
        //    Quem tem o número de prioridade MENOR (ex: 1) é atendido primeiro.
        if (a->getPrioridade() != b->getPrioridade()) {
            return a->getPrioridade() > b->getPrioridade();
        }

        // 2. Critério de Desempate
        //    Se as prioridades são IGUAIS, olhamos a ordem de chegada.
        //    Quem tem o número de ordem (senha) MENOR (chegou antes) 
        //    é atendido primeiro.
        return a->getOrdemChegada() > b->getOrdemChegada();
    }
};