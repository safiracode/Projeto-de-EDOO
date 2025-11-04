#pragma once
#include <list>
#include <string>
#include "Consulta.h"

namespace Relatorios {

    void gerarRelatorioMedicos(const std::list<Consulta*>& consultas); // Pacientes atendidos por médico (do maior para o menor)
    void gerarRelatorioTempoMedio(const std::list<Consulta*>& consultas); // Tempo médio de espera na fila (estimado)
    void gerarHistoricoPorPaciente(const std::list<Consulta*>& consultas, const std::string& nomePaciente); // Histórico de consultas por paciente
    void gerarHistoricoPorMedico(const std::list<Consulta*>& consultas, const std::string& nomeMedico); // Histórico de consultas por médico
    void testarRelatorios(const std::list<Consulta*>& consultas); // Função de testes
    
}
