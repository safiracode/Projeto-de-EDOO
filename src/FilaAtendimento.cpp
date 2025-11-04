// FilaAtendimento.cpp
#include "FilaAtendimento.h"

// Pega o próximo paciente da fila (o mais urgente)
Paciente* FilaAtendimento::chamarProximo() {
    if (fila.empty()) {
        return nullptr; // Se estiver vazia, ninguém pra chamar
    }

    Paciente* proximo = fila.top(); // Pega o de maior prioridade
    fila.pop();                     // Remove da fila
    return proximo;
}

// Mostra como está a fila no momento
void FilaAtendimento::visualizarFila() const {
    auto filaCopia = fila; // Cópia só pra visualizar sem bagunçar a original

    std::cout << "--- Fila de Atendimento (" << filaCopia.size() << " pacientes) ---" << std::endl;
    
    if (filaCopia.empty()) {
        std::cout << "[Fila vazia]" << std::endl;
        return;
    }

    int pos = 1;
    while (!filaCopia.empty()) {
        Paciente* p = filaCopia.top();
        filaCopia.pop();

        // Mostra nome e prioridade com a cor simbólica da triagem
        std::string cor;
        if (p->getPrioridade() == 1) cor = "🔴 Emergência";
        else if (p->getPrioridade() == 2) cor = "🟡 Urgência média";
        else cor = "🟢 Estável";

        std::cout << pos << ". " << p->getNome() 
                  << " - " << cor << std::endl;
        pos++;
    }
}
