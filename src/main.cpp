#include <iostream>
#include <string>
#include <limits>
#include "../classes/Hospital.h"
#include "../classes/Relatorios.h"

// Configuração para suportar caracteres UTF-8 no console, em qualquer sistema operacional
#ifdef _WIN32

    #define NOMINMAX 

    #include <windows.h> // Para SetConsoleOutputCP 
#endif

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

// Menu e Funções de Cadastro

void exibirMenu() {
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║   SISTEMA DE GERENCIAMENTO HOSPITALAR  ║\n";
cout << "╚════════════════════════════════════════╝\n";
    cout << "  1 - Cadastrar Paciente\n";
    cout << "  2 - Cadastrar Médico\n";
   cout << "  3 - Agendar Consulta (e pôr na fila)\n";
    cout << "  4 - Atender Próximo Paciente (por Médico)\n";
   cout << "  5 - Cancelar Consulta\n";
   cout << "  6 - Listar Pacientes\n";
    cout << "  7 - Listar Médicos\n";
   cout << "  8 - Listar Consultas\n";
    cout << "  9 - Visualizar Filas de Atendimento\n";
   cout << "  10 - Salvar Dados\n";
    cout << "  11 - Carregar Dados\n";
   cout << "  ───── RELATÓRIOS ─────\n";
    cout << "  12 - Pacientes Atendidos por Médico\n";
   cout << "  13 - Tempo Médio de Espera\n";
    cout << "  14 - Histórico por Paciente\n";
   cout << "  15 - Histórico por Médico\n";
    cout << "  16 - Executar Testes dos Relatórios\n";
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
    
    int prioridadeVulnerabilidade = lerInteiro("Prioridade de Risco (1-Alto Risco [Idoso/Criança], 2-Baixo Risco): ");
   if (prioridadeVulnerabilidade != 1 && prioridadeVulnerabilidade != 2) {
        cout << "❌ Prioridade inválida! Use 1 ou 2.\n";
       return;
    }
    
    string historico = lerString("Histórico médico (opcional): ");
    
    hospital.cadastrarPaciente(nome, idade, prioridadeVulnerabilidade, historico);
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
}

void agendarEEnfileirar(Hospital& hospital) {
    cout << "\n═══ AGENDAR CONSULTA E ENFILEIRAR ═══\n";
    
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
    
    int prioridadeTriagem = lerInteiro("Prioridade de Triagem (1-Emergência, 2-Urgência, 3-Estável): ");
    if (prioridadeTriagem < 1 || prioridadeTriagem > 3) {
        cout << "❌ Prioridade de triagem inválida! Use 1, 2 ou 3.\n";
        return;
    }
    
    hospital.agendarEEnfileirar(nomePaciente, nomeMedico, data, prioridadeTriagem);
}

void atenderProximo(Hospital& hospital) {
    cout << "\n═══ ATENDER PRÓXIMO PACIENTE ═══\n";
    string nomeMedico = lerString("Nome do médico que irá atender: ");
    if (nomeMedico.empty()) {
        cout << "❌ Nome do médico não pode ser vazio!\n";
        return;
    }
    hospital.atenderProximo(nomeMedico);
}

// Função para cancelar consulta
void cancelarConsulta(Hospital& hospital) {
    cout << "\n═══ CANCELAR CONSULTA ═══\n";
    hospital.listarConsultas(); // Mostra a lista para o usuário saber o ID
    cout << "────────────────────────────────────────\n";
    int consultaId = lerInteiro("Digite o ID da consulta que deseja cancelar: ");
    if (consultaId <= 0) {
        cout << "❌ ID inválido!\n";
        return;
    }
    hospital.cancelarConsulta(consultaId);
}


// Configurações para suportar UTF-8 no console
void configurarUTF8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
#endif
}

// Loop Principal (main)
int main() {
    configurarUTF8(); 

    Hospital hospital;
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
                    agendarEEnfileirar(hospital);
                   break;
                case 4:
                    atenderProximo(hospital);
                   break;
                case 5: // NOVO
                    cancelarConsulta(hospital);
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
                    hospital.listarFilasDeAtendimento();
                    break;
                case 10:
                    cout << "\n💾 Salvando dados...\n";
                    hospital.salvarDados();
                    break;
                case 11:
                    cout << "\n🔄 Carregando dados...\n";
                    hospital.carregarDados();
                    break;
                case 12:
                    Relatorios::gerarRelatorioMedicos(hospital.getConsultas());
                   break;
                case 13:
                    Relatorios::gerarRelatorioTempoMedio(hospital.getConsultas());
                   break;
                case 14: {
                    string nomePac = lerString("Digite o nome do paciente: ");
                   Relatorios::gerarHistoricoPorPaciente(hospital.getConsultas(), nomePac);
                    break;
                }
                case 15: {
                    string nomeMed = lerString("Digite o nome do médico: ");
                   Relatorios::gerarHistoricoPorMedico(hospital.getConsultas(), nomeMed);
                    break;
                }
                case 16:
                    Relatorios::testarRelatorios(hospital.getConsultas());
                   break;
                case 0:
                    cout << "\n💾 Salvando dados antes de sair...\n";
                   hospital.salvarDados();
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