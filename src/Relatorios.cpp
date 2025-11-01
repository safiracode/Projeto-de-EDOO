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

namespace Relatorios {

    // Função auxiliar para imprimir linha de separação
    void linha() { cout << string(40, '-') << "\n"; }

    // 1. Pacientes atendidos por médico
    void gerarRelatorioMedicos(const list<Consulta*>& consultas) {
        cout << "\n=== Relatorio: Pacientes atendidos por medico ===\n";
        if (consultas.empty()) return (void)(cout << "Nenhuma consulta registrada.\n");

        map<string,int> cont;
        for (auto c : consultas)
            if (c->medico) cont[c->medico->getNome()]++;

        vector<pair<string,int>> dados(cont.begin(), cont.end());
        sort(dados.begin(), dados.end(), [](auto&a,auto&b){return a.second>b.second;});

        cout << left << setw(25) << "Medico" << "Consultas\n"; linha();
        for (auto& d : dados) cout << left << setw(25) << d.first << d.second << "\n";
        linha(); cout << "Total de medicos: " << dados.size() << "\n";
    }

    // 2. Tempo médio de espera (estimado)
    void gerarRelatorioTempoMedio(const list<Consulta*>& consultas) {
        cout << "\n=== Relatorio: Tempo medio de espera ===\n";
        if (consultas.empty()) return (void)(cout << "Nenhuma consulta registrada.\n");

        vector<int> tempos;
        for (auto c : consultas)
            if (c->paciente)
                tempos.push_back(c->paciente->getPrioridade()==1 ? 2 : 10);

        if (tempos.empty()) return (void)(cout << "Nenhum dado de tempo disponivel.\n");
        double media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
        cout << "Tempo medio estimado de espera: " << fixed << setprecision(2)
             << media << " minutos\n";
    }

    // Função genérica para histórico (paciente ou médico)
    template<typename T>
    void gerarHistorico(const list<Consulta*>& consultas, const string& nome, bool porMedico) {
        string tipo = porMedico ? "Medico" : "Paciente";
        cout << "\n=== Historico de Consultas do " << tipo << ": " << nome << " ===\n";
        int total = 0;

        for (auto c : consultas) {
            Paciente* p = c->paciente; Medico* m = c->medico;
            if (!p || !m) continue;

            if ((porMedico && m->getNome()==nome) ||
                (!porMedico && p->getNome()==nome)) {
                cout << "- " << (porMedico?"Paciente: ":"Medico: ")
                     << setw(20) << left << (porMedico? p->getNome() : m->getNome())
                     << " | Status: Concluida | Data: (?)\n";
                total++;
            }
        }
        if (!total) cout << "Nenhum historico encontrado.\n";
        else cout << "Total de consultas encontradas: " << total << "\n";
    }

    void gerarHistoricoPorPaciente(const list<Consulta*>& c, const string& n) {
        gerarHistorico<Paciente>(c, n, false);
    }

    void gerarHistoricoPorMedico(const list<Consulta*>& c, const string& n) {
        gerarHistorico<Medico>(c, n, true);
    }

    // 5. Testes unitários
    void testarRelatorios(const list<Consulta*>& consultas) {
        cout << "\n=== Testes Unitarios dos Relatorios ===\n";
        gerarRelatorioMedicos(consultas);
        gerarRelatorioTempoMedio(consultas);
        gerarHistoricoPorPaciente(consultas, "Joao");
        gerarHistoricoPorMedico(consultas, "Dra. Ana");
        cout << "=== Fim dos testes ===\n";
    }
}