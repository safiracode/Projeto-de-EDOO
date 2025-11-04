#pragma once
#include "Consulta.h" // Agora comparamos Consultas
#include "Paciente.h" // Precisamos do Paciente para a prioridade 2

struct ComparadorPaciente {

    bool operator()(const Consulta* a, const Consulta* b) const {
        
        // NÍVEL 1: PRIORIDADE DA TRIAGEM (Emergência 1-3
        // (1 = Emergência, 2 = Média, 3 = Estável)
        // Quem tem o número MENOR (1) é atendido primeiro.
        if (a->getPrioridadeTriagem() != b->getPrioridadeTriagem()) {
            return a->getPrioridadeTriagem() > b->getPrioridadeTriagem();
        }

        // NÍVEL 2: PRIORIDADE DE VULNERABILIDADE
        // (1 = Alto Risco, 2 = Baixo Risco)
        // Se a triagem for igual, quem é mais vulnerável (1) é atendido primeiro.
        int prioVulnerabilidadeA = a->getPaciente()->getPrioridadeVulnerabilidade();
        int prioVulnerabilidadeB = b->getPaciente()->getPrioridadeVulnerabilidade();

        if (prioVulnerabilidadeA != prioVulnerabilidadeB) {
            return prioVulnerabilidadeA > prioVulnerabilidadeB;
        }

        // NÍVEL 3: ORDEM DE CHEGADA
        // Se a triagem E a vulnerabilidade são iguais, 
        // quem chegou antes é atendido primeiro.
        return a->getOrdemChegada() > b->getOrdemChegada();
    }
};