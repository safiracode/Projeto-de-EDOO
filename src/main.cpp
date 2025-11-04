#include <iostream>
#include <string>
#include <limits>
#include "../classes/Hospital.h"
#include "../classes/Relatorios.h"

// Configuração para suportar caracteres UTF-8 no console, em qualquer sistema operacional
#ifdef _WIN32
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

// Função de UI: Apenas exibe as opções
void exibirMenu() { /* ... (código do menu omitido para breveidade) ... */ }

/*
 * A função 'cadastrarPaciente' possui duas camadas de validação:
 * Verifica se o nome está vazio ou se a idade faz sentido.
 * Validação das classes: Mesmo que esta validação falhe, as classes Paciente/Pessoa farão sua própria validação para garantir a integridade dos dados.
 */
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
    
    // Delega a lógica de negócios para a classe Hospital
    hospital.cadastrarPaciente(nome, idade, prioridade, historico);
    cout << "✅ Paciente cadastrado com sucesso!\n";
}

// Fluxo para cadastrar médico
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

// Fluxo para agendar consulta
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

// Fluxo para adicionar na fila
void adicionarNaFila(Hospital& hospital) {
    cout << "\n═══ ADICIONAR PACIENTE NA FILA ═══\n";
    
    string nomePaciente = lerString("Nome do paciente: ");
    if (nomePaciente.empty()) {
        cout << "❌ Nome do paciente não pode ser vazio!\n";
        return;
    }
    
    hospital.adicionarNaFila(nomePaciente);
}

// Fluxo para atender próximo paciente na fila de espera
void atenderProximo(Hospital& hospital) {
    cout << "\n═══ ATENDER PRÓXIMO PACIENTE ═══\n";
    hospital.atenderProximo();
}

// Configurações para suportar UTF-8 no console
void configurarUTF8() {
#ifdef _WIN32
    // habilita UTF-8 no console do Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// Ponto de entrada do programa
int main() {
    configurarUTF8(); // Configura o console para UTF-8

    Hospital hospital; // A "Classe Controladora" que gerencia todo o sistema
    
    // PERSISTÊNCIA (Carregamento / Load)
    // Tenta carregar o estado anterior do sistema a partir de arquivos JSON
    cout << "🔄 Carregando dados salvos...\n";
    hospital.carregarDados();
    
    int opcao;
    bool continuar = true;
    
    // O loop principal do aplicativo
    while (continuar) {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opção: ");
        
        // TRY-CATCH
        // Aqui temos a "rede de segurança" que impede o programa de quebrar caso alguma classe (Pessoa, Paciente, Hospital) lance uma exceção (throw)
        try {
            switch (opcao) {
                // (Casos do menu...)
                case 1:
                    cadastrarPaciente(hospital);
                    break;
                case 2:
                    cadastrarMedico(hospital);
                    break;
                // ... (outros casos)
                case 10:
                    // Salvamento / Save
                    // Salva o estado atual (pacientes, médicos) em JSON
                    cout << "\n💾 Salvando dados...\n";
                    hospital.salvarDados();
                    cout << "✅ Dados salvos com sucesso!\n";
                    break;
                // ... (casos dos relatórios)
                case 0:
                    // Graceful Shutdown
                    // Garante que os dados sejam salvos antes do programa fechar
                    cout << "\n💾 Salvando dados antes de sair...\n";
                    hospital.salvarDados();
                    cout << "✅ Dados salvos!\n";
                    cout << "👋 Encerrando sistema. Até logo!\n";
                    continuar = false; // Sinaliza o fim do 'while' loop
                    break;
                default:
                    cout << "❌ Opção inválida! Tente novamente.\n";
            }
        } catch (const exception& e) {
            // Se um erro (exceção) foi lançado em qualquer lugar,
            // ele é pego aqui e sua mensagem ('e.what()') é exibida.
            cout << "❌ Erro: " << e.what() << "\n";
        }
    }
    
    return 0;
}