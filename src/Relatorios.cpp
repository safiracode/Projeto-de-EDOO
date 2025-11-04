#include "Relatorios.h"
#include "Medico.h"
#include "Paciente.h"
#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>

using namespace std;

// relatório (com namespace)
namespace Relatorios {

    // função para imprimir uma linha com 40 traços (-)
    void linha() { 
        cout << string(40, '-') << "\n"; 
    }

    // função 1: gerarRelatorioMedicos (de quantos pacientes cada médico atendeu)
    void gerarRelatorioMedicos(const list<Consulta*>& consultas) {
        cout << "\n=== Relatorio: Pacientes atendidos por medico ===\n";

        // se não tiver nenhuma consulta, sai da função 
        if (consultas.empty()) 
            return (void)(cout << "Nenhuma consulta registrada.\n");

        map<string,int> cont; // mapa para salvar médico -> qtde. de consultas

        // vê todas as consultas
        for (auto c : consultas)
            // se tiver algum médico ligado à consulta
            if (c->getMedico()) 
                // incrementa o contador de atendimentos do médico
                cont[c->getMedico()->getNome()]++;

        // converter o mapa para um vetor de pares (nome, quantidade)
        vector<pair<string,int>> dados(cont.begin(), cont.end());

        // ordena o vetor dos médicos, do maior número de atendimentos para o menor (para organizar)
        sort(dados.begin(), dados.end(), [](auto&a,auto&b){return a.second > b.second;});

        // cabeçalho do relatório
        cout << left << setw(25) << "Medico" << "Consultas\n"; 
        linha(); // linha de separação

        // mostra os dados formatados
        for (auto& d : dados) 
            cout << left << setw(25) << d.first << d.second << "\n";

        // linha final e total de médicos contabilizados
        linha(); 
        cout << "Total de medicos: " << dados.size() << "\n";
    }

    // função 2: gerarRelatorioTempoMedio (calcula o tempo médio de espera estimado dos pacientes)
    void gerarRelatorioTempoMedio(const list<Consulta*>& consultas) {
        cout << "\n=== Relatorio: Tempo medio de espera ===\n";

        // se não tiver consultas, retorna
        if (consultas.empty()) 
            return (void)(cout << "Nenhuma consulta registrada.\n");

        vector<int> tempos; // armazenar tempos individuais de espera

        // percorre todas as consultas
        for (auto c : consultas)
            // define tempo de espera: 2 min para prioridade 1 (alta), 10 min para 2 (baixa)
            tempos.push_back(c->getPrioridadeTriagem() == 1 ? 2 : 10);

        // se não tiver tempos válidos, sai da função
        if (tempos.empty()) 
            return (void)(cout << "Nenhum dado de tempo disponivel.\n");

        // média dos tempos
        double media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
        cout << "Tempo medio estimado de espera: " // resultado
             << fixed << setprecision(2) << media << " minutos\n"; // duas casas decimais
    }

    // função auxiliar genérica: gerarHistorico (mostra o histórico de consultas de um médico ou de um paciente)
    template<typename T>
    void gerarHistorico(const list<Consulta*>& consultas, const string& nome, bool porMedico) {
        // define se é "Medico" ou "Paciente"
        string tipo = porMedico ? "Medico" : "Paciente";
        cout << "\n=== Historico de Consultas do " << tipo << ": " << nome << " ===\n";

        int total = 0; // contador de consultas encontradas

        // percorre todas as consultas
        for (auto c : consultas) {
            // acessa o paciente e o médico da consulta
            Paciente* p = c->getPaciente(); 
            Medico* m = c->getMedico();

            // se algum for nulo, ignora
            if (!p || !m) continue;

            // se o nome informado está no sistema (é médico ou paciente)
            if ((porMedico && m->getNome() == nome) ||
                (!porMedico && p->getNome() == nome)) {

                // exibição da consulta formatada
                cout << "- " << (porMedico ? "Paciente: " : "Medico: ")
                     << setw(20) << left << (porMedico ? p->getNome() : m->getNome())
                     << " | Status: " << c->getStatus() 
                     << " | Data: " << c->getData() << "\n";

                // contador de consultas exibidas
                total++;
            }
        }

        // nenhuma consulta encontrada
        if (!total) 
            cout << "Nenhum historico encontrado.\n";
        else 
            cout << "Total de consultas encontradas: " << total << "\n";
    }

    // função 3: gerarHistoricoPorPaciente (chama a função genérica para mostrar o histórico de um paciente)
    void gerarHistoricoPorPaciente(const list<Consulta*>& c, const string& n) {
        // gerarHistorico com porMedico = false
        gerarHistorico<Paciente>(c, n, false);
    }

    // função 4: gerarHistoricoPorMedico (chama a função genérica para mostrar o histórico de um médico)
    void gerarHistoricoPorMedico(const list<Consulta*>& c, const string& n) {
        // gerarHistorico com porMedico = true
        gerarHistorico<Medico>(c, n, true);
    }

    // função 5: testarRelatorios (opcional para validação)
    void testarRelatorios(const list<Consulta*>& consultas) {
        cout << "\n=== Testes Unitarios dos Relatorios ===\n";
        gerarRelatorioMedicos(consultas);
        gerarRelatorioTempoMedio(consultas);
        
        // testa histórico com pacientes e médicos do sistema
        if (!consultas.empty()) {
            // pega o primeiro paciente e médico das consultas existentes
            for (auto c : consultas) {
                if (c->getPaciente() && c->getMedico()) {
                    gerarHistoricoPorPaciente(consultas, c->getPaciente()->getNome());
                    gerarHistoricoPorMedico(consultas, c->getMedico()->getNome());
                    break; // testa apenas com um exemplo de cada
                }
            }
        }
        cout << "=== Fim dos testes ===\n";
    }
}
