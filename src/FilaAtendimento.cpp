#include "FilaAtendimento.h"
#include "Paciente.h" // Necessário para pegar o nome do paciente

// Pega a próxima consulta da fila (a mais urgente)
Consulta* FilaAtendimento::chamarProxima() {
    if (fila.empty()) {
        return nullptr; // Se estiver vazia, ninguém pra chamar
    }

    Consulta* proxima = fila.top(); // Pega o de maior prioridade
    fila.pop();                     // Remove da fila
    return proxima;
}

// Mostra como está a fila no momento
void FilaAtendimento::visualizarFila() const {
    auto filaCopia = fila; // Cópia só pra visualizar sem bagunçar a original

    std::cout << "   Pacientes na fila: " << filaCopia.size() << std::endl;
    
    if (filaCopia.empty()) {
        std::cout << "   [Fila vazia]" << std::endl;
        return;
    }

    int pos = 1;
    while (!filaCopia.empty()) {
        Consulta* c = filaCopia.top();
        filaCopia.pop();

        // Pegamos o paciente DE DENTRO da consulta
        Paciente* p = c->getPaciente();

        // Definindo os textos de prioridade
        
        // Nível 1 (Triagem)
        std::string txtTriagem;
        if (c->getPrioridadeTriagem() == 1) txtTriagem = "🔴 Emergência";
        else if (c->getPrioridadeTriagem() == 2) txtTriagem = "🟡 Urgência";
        else txtTriagem = "🟢 Estável";

        // Nível 2 (Vulnerabilidade)
        std::string txtVulnerab;
        if (p->getPrioridadeVulnerabilidade() == 1) txtVulnerab = "Alto Risco";
        else txtVulnerab = "Baixo Risco";

        // Imprime o paciente e seus dois níveis de prioridade
        std::cout << "   " << pos << ". " << p->getNome() 
                  << " (Triagem: " << txtTriagem 
                  << " | Risco: " << txtVulnerab << ")" << std::endl;
        pos++;
    }
}