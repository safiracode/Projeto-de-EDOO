#pragma once
#include "Paciente.h"

/*
 * Este struct "ensina" a fila de prioridade como comparar dois Paciente*
 * * A std::priority_queue é uma "max heap" (fila de máximo) por padrão.
 * Isso significa que o item "maior" fica no topo (maior prioridade).
 * * Queremos que a Emergência (prioridade 1) venha antes do Normal (prioridade 0).
 * 1 > 0, então a lógica padrão de "max heap" funciona.
 * * Este operador retorna 'true' se 'a' tiver uma prioridade MENOR que 'b',
 * fazendo com que 'a' vá para o "fundo" da fila.
 */
struct ComparadorPaciente {
    bool operator()(const Paciente* a, const Paciente* b) const {
        // Compara usando o método que Eduardo vai fzr
        return a->getPrioridade() < b->getPrioridade();
    }
};