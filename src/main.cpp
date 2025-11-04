#include <iostream>
#include <string>
#include <limits>
#include "../classes/Hospital.h"
#include "../classes/Relatorios.h"

// Configuração para suportar caracteres UTF-8 no console, em qualquer sistema operacional
#ifdef _WIN32
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
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
    cout << "  1 - 👥 Gerenciar Pacientes\n";
    cout << "  2 - 👨‍⚕️ Gerenciar Médicos\n";
    cout << "  3 - 📋 Gerenciar Consultas\n";
    cout << "  4 - 🚑 Visualizar Filas de Atendimento\n";
    cout << "  5 - 💾 Salvar Dados\n";
    cout << "  6 - 🔄 Carregar Dados\n";
    cout << "  7 - 📊 Relatórios\n";
    cout << "  0 - 🚪 Sair\n";
    cout << "────────────────────────────────────────\n";
}

// Funções de cadastro
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

// Funções de consulta e fila
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

// Funções de edição

void editarPacienteMenu(Hospital& hospital) {
    cout << "\n═══ EDITAR PACIENTE ═══\n";
    hospital.listarPacientes(); // Listagem dos pacientes para referência
    cout << "────────────────────────────────────────\n";
    string nome = lerString("Digite o nome do paciente a editar: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    hospital.editarPaciente(nome);
}

void editarMedicoMenu(Hospital& hospital) {
    cout << "\n═══ EDITAR MÉDICO ═══\n";
    hospital.listarMedicos(); // Listagem dos médicos para referência
    cout << "────────────────────────────────────────\n";
    string nome = lerString("Digite o nome do médico a editar: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    hospital.editarMedico(nome);
}

void editarConsultaMenu(Hospital& hospital) {
    cout << "\n═══ EDITAR CONSULTA ═══\n";
    hospital.listarConsultas(); // Listagem das consultas para referência
    cout << "────────────────────────────────────────\n";
    int consultaId = lerInteiro("Digite o ID da consulta a editar: ");
    if (consultaId <= 0) {
        cout << "❌ ID inválido!\n";
        return;
    }
    hospital.editarConsulta(consultaId);
}

// Funções de remoção

void removerPacienteMenu(Hospital& hospital) {
    cout << "\n═══ REMOVER PACIENTE ═══\n";
    hospital.listarPacientes(); // Listagem dos pacientes para referência
    cout << "────────────────────────────────────────\n";
    string nome = lerString("Digite o nome do paciente a remover: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    
    // Confirmação de remoção
    string confirmacao = lerString("⚠️  Confirma a remoção? (s/n): ");
    if (confirmacao == "s" || confirmacao == "S") {
        hospital.removerPaciente(nome);
    } else {
        cout << "❌ Operação cancelada.\n";
    }
}

void removerMedicoMenu(Hospital& hospital) {
    cout << "\n═══ REMOVER MÉDICO ═══\n";
    hospital.listarMedicos(); // Listagem dos médicos para referência
    cout << "────────────────────────────────────────\n";
    string nome = lerString("Digite o nome do médico a remover: ");
    if (nome.empty()) {
        cout << "❌ Nome não pode ser vazio!\n";
        return;
    }
    
    // Confirmação
    string confirmacao = lerString("⚠️  Confirma a remoção? (s/n): ");
    if (confirmacao == "s" || confirmacao == "S") {
        hospital.removerMedico(nome);
    } else {
        cout << "❌ Operação cancelada.\n";
    }
}

void removerConsultaMenu(Hospital& hospital) {
    cout << "\n═══ REMOVER CONSULTA ═══\n";
    hospital.listarConsultas(); // Listagem das consultas para referência
    cout << "────────────────────────────────────────\n";
    cout << "⚠️  Atenção: Remover é diferente de Cancelar!\n";
    cout << "   - Cancelar: Mantém a consulta com status 'Cancelada'\n";
    cout << "   - Remover: Apaga completamente a consulta do sistema\n\n";
    
    int consultaId = lerInteiro("Digite o ID da consulta a remover: ");
    if (consultaId <= 0) {
        cout << "❌ ID inválido!\n";
        return;
    }
    
    // Confirmação de remoção
    string confirmacao = lerString("⚠️  Confirma a remoção? (s/n): ");
    if (confirmacao == "s" || confirmacao == "S") {
        hospital.removerConsulta(consultaId);
    } else {
        cout << "❌ Operação cancelada.\n";
    }
}

// Exibição dos submenus

void submenuPacientes(Hospital& hospital) {
    int opcao;
    do {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║       👥 GERENCIAR PACIENTES           ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "  1 - ➕ Cadastrar Paciente\n";
        cout << "  2 - 📋 Listar Pacientes\n";
        cout << "  3 - ✏️  Editar Paciente\n";
        cout << "  4 - 🗑️  Remover Paciente\n";
        cout << "  0 - ↩️  Voltar ao Menu Principal\n";
        cout << "────────────────────────────────────────\n";
        
        opcao = lerInteiro("Escolha uma opção: ");
        
        try {
            switch (opcao) {
                case 1:
                    cadastrarPaciente(hospital);
                    break;
                case 2:
                    cout << "\n═══ LISTA DE PACIENTES ═══\n";
                    hospital.listarPacientes();
                    break;
                case 3:
                    editarPacienteMenu(hospital);
                    break;
                case 4:
                    removerPacienteMenu(hospital);
                    break;
                case 0:
                    cout << "↩️  Voltando ao menu principal...\n";
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            cout << "❌ Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}

void submenuMedicos(Hospital& hospital) {
    int opcao;
    do {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║       👨‍⚕️ GERENCIAR MÉDICOS             ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "  1 - ➕ Cadastrar Médico\n";
        cout << "  2 - 📋 Listar Médicos\n";
        cout << "  3 - ✏️  Editar Médico\n";
        cout << "  4 - 🗑️  Remover Médico\n";
        cout << "  0 - ↩️  Voltar ao Menu Principal\n";
        cout << "────────────────────────────────────────\n";
        
        opcao = lerInteiro("Escolha uma opção: ");
        
        try {
            switch (opcao) {
                case 1:
                    cadastrarMedico(hospital);
                    break;
                case 2:
                    cout << "\n═══ LISTA DE MÉDICOS ═══\n";
                    hospital.listarMedicos();
                    break;
                case 3:
                    editarMedicoMenu(hospital);
                    break;
                case 4:
                    removerMedicoMenu(hospital);
                    break;
                case 0:
                    cout << "↩️  Voltando ao menu principal...\n";
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            cout << "❌ Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}

void submenuConsultas(Hospital& hospital) {
    int opcao;
    do {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║       📋 GERENCIAR CONSULTAS           ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "  1 - ➕ Agendar Consulta\n";
        cout << "  2 - 📋 Listar Consultas\n";
        cout << "  3 - ✏️  Editar Consulta\n";
        cout << "  4 - ❌ Cancelar Consulta\n";
        cout << "  5 - 🗑️  Remover Consulta\n";
        cout << "  6 - 🏥 Atender Próximo Paciente\n";
        cout << "  0 - ↩️  Voltar ao Menu Principal\n";
        cout << "────────────────────────────────────────\n";
        
        opcao = lerInteiro("Escolha uma opção: ");
        
        try {
            switch (opcao) {
                case 1:
                    agendarEEnfileirar(hospital);
                    break;
                case 2:
                    cout << "\n═══ LISTA DE CONSULTAS ═══\n";
                    hospital.listarConsultas();
                    break;
                case 3:
                    editarConsultaMenu(hospital);
                    break;
                case 4:
                    cancelarConsulta(hospital);
                    break;
                case 5:
                    removerConsultaMenu(hospital);
                    break;
                case 6:
                    atenderProximo(hospital);
                    break;
                case 0:
                    cout << "↩️  Voltando ao menu principal...\n";
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            cout << "❌ Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}

void submenuRelatorios(Hospital& hospital) {
    int opcao;
    do {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║           📊 RELATÓRIOS                ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "  1 - 📈 Pacientes Atendidos por Médico\n";
        cout << "  2 - ⏱️  Tempo Médio de Espera\n";
        cout << "  3 - 👤 Histórico por Paciente\n";
        cout << "  4 - 👨‍⚕️ Histórico por Médico\n";
        cout << "  5 - 🧪 Executar Testes dos Relatórios\n";
        cout << "  0 - ↩️  Voltar ao Menu Principal\n";
        cout << "────────────────────────────────────────\n";
        
        opcao = lerInteiro("Escolha uma opção: ");
        
        try {
            switch (opcao) {
                case 1:
                    Relatorios::gerarRelatorioMedicos(hospital.getConsultas());
                    break;
                case 2:
                    Relatorios::gerarRelatorioTempoMedio(hospital.getConsultas());
                    break;
                case 3: {
                    string nomePac = lerString("Digite o nome do paciente: ");
                    Relatorios::gerarHistoricoPorPaciente(hospital.getConsultas(), nomePac);
                    break;
                }
                case 4: {
                    string nomeMed = lerString("Digite o nome do médico: ");
                    Relatorios::gerarHistoricoPorMedico(hospital.getConsultas(), nomeMed);
                    break;
                }
                case 5:
                    Relatorios::testarRelatorios(hospital.getConsultas());
                    break;
                case 0:
                    cout << "↩️  Voltando ao menu principal...\n";
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            cout << "❌ Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
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
                    submenuPacientes(hospital);
                   break;
                case 2:
                    submenuMedicos(hospital);
                   break;
                case 3:
                    submenuConsultas(hospital);
                   break;
                case 4:
                    cout << "\n═══ FILA DE ATENDIMENTO ═══\n";
                    hospital.listarFilasDeAtendimento();
                    break;
                case 5:
                    cout << "\n💾 Salvando dados...\n";
                    hospital.salvarDados();
                    break;
                case 6:
                    cout << "\n🔄 Carregando dados...\n";
                    hospital.carregarDados();
                    break;
                case 7:
                    submenuRelatorios(hospital);
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