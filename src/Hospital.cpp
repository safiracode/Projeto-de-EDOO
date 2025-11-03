#include "Hospital.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Destrutor: libera memória alocada dinamicamente
Hospital::~Hospital() {
    for (auto p : pacientes) delete p; // Percorre as listas e deleta cada objeto
    for (auto m : medicos) delete m;
    for (auto c : consultas) delete c;
}

// CADASTROS
// Cria um novo paciente, adiciona à lista pacientes e imprime confirmação
void Hospital::cadastrarPaciente(std::string nome, int idade, int prioridade, std::string historico) {
    Paciente* p = new Paciente(nome, idade, prioridade, historico); // Chama construtor de Paciente
    pacientes.push_back(p); // Adiciona o ponteiro retornado à lista de pacientes do hospital
    std::cout << "Paciente cadastrado: " << p->getNome() << std::endl; // Método getter de Paciente (herdado de Pessoa) pra imprimir o nome
}
// Cria um novo médico, adiciona à lista medicos e imprime confirmação
void Hospital::cadastrarMedico(std::string nome, int idade, std::string crm, std::string especialidade) {
    Medico* m = new Medico(nome, idade, crm, especialidade); // Chama construtor de Medico
    medicos.push_back(m);
    std::cout << "Medico cadastrado: " << m->getNome() << std::endl;
}

// CONSULTAS 
void Hospital::agendarConsulta(std::string nomePaciente, std::string nomeMedico, std::string data) {
    // Retorna ponteiro para paciente/medico ou nullptr se não encontrado(s)
    Paciente* p = buscarPacientePorNome(nomePaciente);
    Medico* m = buscarMedicoPorNome(nomeMedico);

    if (!p || !m) { // Checa se ambos existem 
        std::cerr << "Erro: paciente ou medico nao encontrado." << std::endl;
        return;
    }

    // Cria um novo objeto Consulta ligando um paciente e um médico e incrementa o ID
    Consulta* c = new Consulta(proximoIdConsulta++, p, m, data); 
    consultas.push_back(c); // Adiciona na lista consultas
    std::cout << "Consulta agendada para " << p->getNome() // Imprime confirmação de agendamento
              << " com " << m->getNome() << " em " << data << std::endl;
}

// FILA (usa métodos de FilaAtendimento)
void Hospital::adicionarNaFila(std::string nomePaciente) {
    Paciente* p = buscarPacientePorNome(nomePaciente);
    if (!p) { // Checa se o paciente existe
        std::cerr << "Erro: paciente nao encontrado." << std::endl;
        return;
    }
    fila.adicionarPaciente(p); // Adiciona paciente à priority_queue, de acordo com a prioridade (0 normal, 1 emergência)
    std::cout << "Paciente " << p->getNome() << " adicionado à fila." << std::endl; // Imprime confirmação
}

void Hospital::atenderProximo() {
    if (fila.estaVazia()) { // Checa se tem pacientes na fila
        std::cout << "Nenhum paciente na fila." << std::endl;
        return;
    }

    Paciente* p = fila.chamarProximo(); // Pega o próximo paciente da fila e remove-o dela
    if (!p) return;                     // Teste extra pra checar se não tem paciente

    // Busca médico disponível (o primeiro da lista)
    if (medicos.empty()) {
        std::cerr << "Nenhum medico cadastrado." << std::endl;
        return;
    }

    Medico* m = medicos.front();

    // Cria e conclui consulta
    Consulta* c = new Consulta(proximoIdConsulta++, p, m, "hoje");
    c->concluirConsulta();
    consultas.push_back(c);

    std::cout << "Atendimento concluido: " << p->getNome()
              << " atendido por " << m->getNome() << std::endl;

    // Atualiza histórico do paciente
    std::string novoHistorico = p->getHistorico() + "\nConsulta com " + m->getNome() + " - concluida.";
    p->setHistorico(novoHistorico);
}

// BUSCAS
// Busca paciente pelo nome na lista pacientes e retorna ponteiro para o objeto ou nullptr se não for encontrado
Paciente* Hospital::buscarPacientePorNome(const std::string& nome) {
    for (auto p : pacientes) {
        if (p->getNome() == nome) return p;
    }
    return nullptr;
}
// Busca médico pelo nome na lista medicos e retorna ponteiro para o objeto ou nullptr se não for encontrado
Medico* Hospital::buscarMedicoPorNome(const std::string& nome) {
    for (auto m : medicos) {
        if (m->getNome() == nome) return m;
    }
    return nullptr;
}

// LISTAGENS
void Hospital::listarPacientes() const {
    if (pacientes.empty()) {
        std::cout << "Nenhum paciente cadastrado.\n";
        return;
    }
    
    std::cout << "Total de pacientes: " << pacientes.size() << "\n";
    std::cout << "────────────────────────────────────────\n";
    
    for (const auto& p : pacientes) {
        std::cout << "Nome: " << p->getNome() << "\n";
        std::cout << "Idade: " << p->getIdade() << " anos\n";
        std::cout << "Prioridade: " << (p->getPrioridade() == 1 ? "Emergência" : "Normal") << "\n";
        if (!p->getHistorico().empty()) {
            std::cout << "Histórico: " << p->getHistorico() << "\n";
        }
        std::cout << "────────────────────────────────────────\n";
    }
}

void Hospital::listarMedicos() const {
    if (medicos.empty()) {
        std::cout << "Nenhum médico cadastrado.\n";
        return;
    }
    
    std::cout << "Total de médicos: " << medicos.size() << "\n";
    std::cout << "────────────────────────────────────────\n";
    
    for (const auto& m : medicos) {
        std::cout << "Nome: " << m->getNome() << "\n";
        std::cout << "Idade: " << m->getIdade() << " anos\n";
        std::cout << "CRM: " << m->getCRM() << "\n";
        std::cout << "Especialidade: " << m->getEspecialidade() << "\n";
        std::cout << "────────────────────────────────────────\n";
    }
}

void Hospital::listarConsultas() const {
    if (consultas.empty()) {
        std::cout << "Nenhuma consulta agendada.\n";
        return;
    }
    
    std::cout << "Total de consultas: " << consultas.size() << "\n";
    std::cout << "────────────────────────────────────────\n";
    
    for (const auto& c : consultas) {
        std::cout << "ID: " << c->getId() << "\n";
        std::cout << "Paciente: " << c->getPaciente()->getNome() << "\n";
        std::cout << "Médico: " << c->getMedico()->getNome() << "\n";
        std::cout << "Data: " << c->getData() << "\n";
        std::cout << "Status: " << c->getStatus() << "\n";
        std::cout << "────────────────────────────────────────\n";
    }
}

void Hospital::listarFilaAtendimento() const {
    if (fila.estaVazia()) {
        std::cout << "Nenhum paciente na fila de atendimento.\n";
        return;
    }
    
    std::cout << "Pacientes na fila: " << fila.tamanho() << "\n";
    fila.visualizarFila();
}

// PERSISTÊNCIA JSON
void Hospital::salvarDados(const std::string& arquivo) {
    try {
        json j;
        
        // Salvar pacientes
        j["pacientes"] = json::array();
        for (const auto& p : pacientes) {
            j["pacientes"].push_back(json::parse(p->toJSONString()));
        }
        
        // Salvar médicos
        j["medicos"] = json::array();
        for (const auto& m : medicos) {
            j["medicos"].push_back(json::parse(m->toJSONString()));
        }
        
        // Salvar consultas
        j["consultas"] = json::array();
        for (const auto& c : consultas) {
            j["consultas"].push_back(json::parse(c->toJSONString()));
        }
        
        // Salvar próximo ID de consulta
        j["proximoIdConsulta"] = proximoIdConsulta;
        
        // Escrever no arquivo
        std::ofstream arquivo_saida(arquivo);
        if (!arquivo_saida.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + arquivo);
        }
        
        arquivo_saida << j.dump(4); // 4 = identação para melhor legibilidade
        arquivo_saida.close();
        
        std::cout << "✅ Dados salvos em: " << arquivo << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erro ao salvar dados: " << e.what() << std::endl;
    }
}

void Hospital::carregarDados(const std::string& arquivo) {
    try {
        std::ifstream arquivo_entrada(arquivo);
        
        // Se o arquivo não existe, não é um erro (primeira execução)
        if (!arquivo_entrada.is_open()) {
            std::cout << "ℹ️  Nenhum arquivo de dados encontrado. Iniciando com dados vazios.\n";
            return;
        }
        
        json j;
        arquivo_entrada >> j;
        arquivo_entrada.close();
        
        // Limpar dados existentes antes de carregar
        for (auto p : pacientes) delete p;
        for (auto m : medicos) delete m;
        for (auto c : consultas) delete c;
        pacientes.clear();
        medicos.clear();
        consultas.clear();
        
        // Carregar pacientes
        if (j.contains("pacientes")) {
            for (const auto& jp : j["pacientes"]) {
                Paciente* p = Paciente::fromJSONString(jp.dump());
                if (p) pacientes.push_back(p);
            }
        }
        
        // Carregar médicos
        if (j.contains("medicos")) {
            for (const auto& jm : j["medicos"]) {
                Medico* m = Medico::fromJSONString(jm.dump());
                if (m) medicos.push_back(m);
            }
        }
        
        // Carregar consultas
        if (j.contains("consultas")) {
            for (const auto& jc : j["consultas"]) {
                Consulta* c = Consulta::fromJSONString(jc.dump(), this);
                if (c) consultas.push_back(c);
            }
        }
        
        // Carregar próximo ID de consulta
        if (j.contains("proximoIdConsulta")) {
            proximoIdConsulta = j["proximoIdConsulta"];
        }
        
        std::cout << "✅ Dados carregados com sucesso!\n";
        std::cout << "   - " << pacientes.size() << " paciente(s)\n";
        std::cout << "   - " << medicos.size() << " médico(s)\n";
        std::cout << "   - " << consultas.size() << " consulta(s)\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erro ao carregar dados: " << e.what() << std::endl;
        std::cerr << "   Continuando com dados vazios.\n";
    }
}

// MÉTODOS AUXILIARES
int Hospital::getTotalPacientes() const {
    return pacientes.size();
}

int Hospital::getTotalMedicos() const {
    return medicos.size();
}

int Hospital::getTotalConsultas() const {
    return consultas.size();
}
