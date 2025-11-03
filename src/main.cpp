#include <iostream>
#include <string>
#include <limits>
#include "../classes/Hospital.h"

using namespace std;

// função para limpar o buffer de entrada
void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// função para ler inteiro com validação
int lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparBuffer();
            return valor;
        } else {
            cout << "❌ Entrada inválida! Digite um número.\n";
            limparBuffer();
        }
    }
}

// função para ler string
string lerString(const string& mensagem) {
    string valor;
    cout << mensagem;
    
    // checa o buffer para limpar se necessário
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    
    getline(cin, valor);
    return valor;
}

void exibirMenu() {
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║   SISTEMA DE GERENCIAMENTO HOSPITALAR  ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    cout << "  1 - Cadastrar Paciente\n";
    cout << "  2 - Cadastrar Médico\n";
    cout << "  3 - Agendar Consulta\n";
    cout << "  4 - Adicionar Paciente na Fila\n";
    cout << "  5 - Atender Próximo Paciente\n";
    cout << "  6 - Listar Pacientes\n";
    cout << "  7 - Listar Médicos\n";
    cout << "  8 - Listar Consultas\n";
    cout << "  9 - Visualizar Fila de Atendimento\n";
    cout << "  10 - Salvar Dados\n";
    cout << "  0 - Sair\n";
    cout << "────────────────────────────────────────\n";
}

void cadastrarPaciente(Hospital& hospital) {
    cout << "\n═══ CADASTRO DE PACIENTE ═══\n";
    
    string nome = lerString("Nome do paciente: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    
    int idade = lerInteiro("Idade: ");
    if (idade <= 0 || idade > 150) {
        cout << "❌ Idade inválida!\n";
        return;
    }
    
    int prioridade = lerInteiro("Prioridade (0-Normal, 1-Emergência): ");
    if (prioridade != 0 && prioridade != 1) {
        cout << "❌ Prioridade inválida! Use 0 ou 1.\n";
        return;
    }
    
    string historico = lerString("Histórico médico (opcional): ");
    
    hospital.cadastrarPaciente(nome, idade, prioridade, historico);
    cout << "✅ Paciente cadastrado com sucesso!\n";
}

void cadastrarMedico(Hospital& hospital) {
    cout << "\n═══ CADASTRO DE MÉDICO ═══\n";
    
    string nome = lerString("Nome do médico: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    
    int idade = lerInteiro("Idade: ");
    if (idade <= 0 || idade > 150) {
        cout << "❌ Idade inválida!\n";
        return;
    }
    
    string crm = lerString("CRM: ");
    if (crm.empty()) {
        cout << "❌ CRM não pode ser vazio!\n";
        return;
    }
    
    string especialidade = lerString("Especialidade: ");
    if (especialidade.empty()) {
        cout << "❌ Especialidade não pode ser vazia!\n";
        return;
    }
    
    hospital.cadastrarMedico(nome, idade, crm, especialidade);
    cout << "✅ Médico cadastrado com sucesso!\n";
}

void agendarConsulta(Hospital& hospital) {
    cout << "\n═══ AGENDAR CONSULTA ═══\n";
    
    string nomePaciente = lerString("Nome do paciente: ");
    if (nomePaciente.empty()) {
        cout << "❌ Nome do paciente não pode ser vazio!\n";
        return;
    }
    
    string nomeMedico = lerString("Nome do médico: ");
    if (nomeMedico.empty()) {
        cout << "❌ Nome do médico não pode ser vazio!\n";
        return;
    }
    
    string data = lerString("Data da consulta (ex: 2025-11-01): ");
    if (data.empty()) {
        cout << "❌ Data não pode ser vazia!\n";
        return;
    }
    
    hospital.agendarConsulta(nomePaciente, nomeMedico, data);
}

void adicionarNaFila(Hospital& hospital) {
    cout << "\n═══ ADICIONAR PACIENTE NA FILA ═══\n";
    
    string nomePaciente = lerString("Nome do paciente: ");
    if (nomePaciente.empty()) {
        cout << "❌ Nome do paciente não pode ser vazio!\n";
        return;
    }
    
    hospital.adicionarNaFila(nomePaciente);
}

void atenderProximo(Hospital& hospital) {
    cout << "\n═══ ATENDER PRÓXIMO PACIENTE ═══\n";
    hospital.atenderProximo();
}

int main() {
    Hospital hospital;
    
    // Carregar dados salvos ao iniciar
    cout << "🔄 Carregando dados salvos...\n";
    hospital.carregarDados();
    
    int opcao;
    bool continuar = true;
    
    while (continuar) {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opção: ");
        
        try {
            switch (opcao) {
                case 1:
                    cadastrarPaciente(hospital);
                    break;
                case 2:
                    cadastrarMedico(hospital);
                    break;
                case 3:
                    agendarConsulta(hospital);
                    break;
                case 4:
                    adicionarNaFila(hospital);
                    break;
                case 5:
                    atenderProximo(hospital);
                    break;
                case 6:
                    cout << "\n═══ LISTA DE PACIENTES ═══\n";
                    hospital.listarPacientes();
                    break;
                case 7:
                    cout << "\n═══ LISTA DE MÉDICOS ═══\n";
                    hospital.listarMedicos();
                    break;
                case 8:
                    cout << "\n═══ LISTA DE CONSULTAS ═══\n";
                    hospital.listarConsultas();
                    break;
                case 9:
                    cout << "\n═══ FILA DE ATENDIMENTO ═══\n";
                    hospital.listarFilaAtendimento();
                    break;
                case 10:
                    cout << "\n💾 Salvando dados...\n";
                    hospital.salvarDados();
                    cout << "✅ Dados salvos com sucesso!\n";
                    break;
                case 0:
                    cout << "\n💾 Salvando dados antes de sair...\n";
                    hospital.salvarDados();
                    cout << "✅ Dados salvos!\n";
                    cout << "👋 Encerrando sistema. Até logo!\n";
                    continuar = false;
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            cout << "❌ Erro: " << e.what() << "\n";
        }
    }
    
    return 0;
}
