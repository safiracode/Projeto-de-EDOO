// FilaAtendimento.cpp

// Inclui o cabeçalho da própria classe. Ele já traz todas as dependências (queue, vector, Paciente.h, etc.)
#include "FilaAtendimento.h" 


Paciente* FilaAtendimento::chamarProximo() {
    if (fila.empty()) {
        return nullptr; // Retorna nulo se a fila estiver vazia
    }
    
    Paciente* proximo = fila.top(); // Pega o de maior prioridade
    fila.pop();                     // Remove da fila
    return proximo;
}

void FilaAtendimento::visualizarFila() const {
    // 1. Cria uma cópia da fila original.
    // O 'auto' garante que a cópia terá o tipo completo da fila de prioridade.
    auto filaCopia = fila; 

    std::cout << "--- Fila de Atendimento Atual (" << filaCopia.size() << " pacientes) ---" << std::endl;
    
    if (filaCopia.empty()) {
        std::cout << "[Fila Vazia]" << std::endl;
        return;
    }

    // 2. Itera sobre a CÓPIA, removendo e imprimindo cada elemento.
    int posicao = 1;
    while (!filaCopia.empty()) {
        Paciente* p = filaCopia.top();
        filaCopia.pop(); 

        // Imprime as informações
        std::cout << posicao << ". "
                  << "Nome: " << p->getNome()
                  << " (Prioridade: " << p->getPrioridade() << ")" 
                  << std::endl;
        
        posicao++;
    }
}