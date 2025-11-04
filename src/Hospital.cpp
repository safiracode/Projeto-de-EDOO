#include "Hospital.h"
#include <iostream>
#include <stdexcept>
#include "Relatorios.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Destrutor: libera memória alocada dinamicamente
Hospital::~Hospital() {
    for (auto p : pacientes) delete p;
   for (auto m : medicos) delete m;
    for (auto c : consultas) delete c;
}

// CADASTROS
void Hospital::cadastrarPaciente(std::string nome, int idade, int prioridadeVulnerabilidade, std::string historico) {
    Paciente* p = new Paciente(nome, idade, prioridadeVulnerabilidade, historico);
   pacientes.push_back(p); 
    std::cout << "Paciente cadastrado: " << p->getNome() << std::endl;
}

void Hospital::cadastrarMedico(std::string nome, int idade, std::string crm, std::string especialidade) {
    Medico* m = new Medico(nome, idade, crm, especialidade);
   medicos.push_back(m);
    std::cout << "Medico cadastrado: " << m->getNome() << std::endl;
}

// CONSULTAS
void Hospital::agendarEEnfileirar(std::string nomePaciente, std::string nomeMedico, std::string data, int prioridadeTriagem) {
    Paciente* p = buscarPacientePorNome(nomePaciente);
   Medico* m = buscarMedicoPorNome(nomeMedico);

    if (!p || !m) { 
        std::cerr << "Erro: paciente ou medico nao encontrado." << std::endl;
        return;
    }

    Consulta* c = new Consulta(proximoIdConsulta++, p, m, data, prioridadeTriagem);
   consultas.push_back(c); // Adiciona na lista mestre de consultas

    m->getFila().adicionarConsulta(c);

    std::cout << "Consulta agendada para " << p->getNome()
              << " com " << m->getNome() << " e adicionado(a) à fila." << std::endl;
}

// Lógica de atender próximo
void Hospital::atenderProximo(std::string nomeMedico) {
    Medico* m = buscarMedicoPorNome(nomeMedico);
    if (!m) {
        std::cerr << "Erro: medico nao encontrado." << std::endl;
        return;
    }

    FilaAtendimento& filaDoMedico = m->getFila();
    Consulta* c = nullptr;

    while (!filaDoMedico.estaVazia()) {
        c = filaDoMedico.chamarProxima();
        
        // Se a consulta estiver Agendada, encontramos!
        if (c->getStatus() == "Agendada") {
            break; 
        }
        
        // Se estiver "Cancelada" ou "Concluída", apenas ignoramos
        // e o loop continua para pegar a próxima.
        c = nullptr; // Reseta o ponteiro
    }

    if (c == nullptr) { // Se 'c' ainda é nulo, a fila esvaziou
        std::cout << "Nenhum paciente 'Agendado' na fila do(a) Dr(a). " << m->getNome() << "." << std::endl;
        return;
    }

    // Se chegamos aqui, 'c' é uma consulta válida e "Agendada"
    Paciente* p = c->getPaciente();

    // Conclui a consulta
    c->concluirConsulta();
   
    std::cout << "Atendimento concluido: " << p->getNome()
              << " atendido por " << m->getNome() << std::endl;

    std::string novoHistorico = p->getHistorico() + "\nConsulta com " + m->getNome() + " - concluida.";
   p->setHistorico(novoHistorico);
}

// Implementação da função de cancelar consulta
void Hospital::cancelarConsulta(int consultaId) {
    // 1. Encontra a consulta pelo ID
    Consulta* c = buscarConsultaPorId(consultaId);
    
    if (c == nullptr) {
        std::cerr << "Erro: Consulta com ID " << consultaId << " nao encontrada." << std::endl;
        return;
    }
    
    // 2. Verifica se ela pode ser cancelada (não pode estar Concluída)
    if (c->getStatus() != "Agendada") {
        std::cerr << "Erro: Esta consulta nao pode ser cancelada (Status atual: " << c->getStatus() << ")." << std::endl;
        return;
    }
    
    // 3. Cancela a consulta (o método vem de Consulta.h)
    c->cancelarConsulta(); // Isso muda o status para "Cancelada" 
    
    std::cout << "✅ Consulta ID " << c->getId() << " (Paciente: " 
              << c->getPaciente()->getNome() 
              << ") foi cancelada com sucesso." << std::endl;
              
    // A lógica em 'atenderProximo' irá pular automaticamente esta consulta.
}

// BUSCAS
Paciente* Hospital::buscarPacientePorNome(const std::string& nome) {
    for (auto p : pacientes) {
        if (p->getNome() == nome) return p;
   }
    return nullptr;
}
Medico* Hospital::buscarMedicoPorNome(const std::string& nome) {
    for (auto m : medicos) {
        if (m->getNome() == nome) return m;
   }
    return nullptr;
}

// Função auxiliar para encontrar consulta por ID
Consulta* Hospital::buscarConsultaPorId(int id) {
    for (auto c : consultas) {
        if (c->getId() == id) return c;
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
        std::cout << "Prioridade Risco: " << (p->getPrioridadeVulnerabilidade() == 1 ? "Alto Risco" : "Baixo Risco") << "\n";
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
        std::cout << "Status: " << c->getStatus() << "\n"; // (Agendada, Concluída ou Cancelada)
        std::cout << "Prioridade Triagem: " << c->getPrioridadeTriagem() << "\n";
        std::cout << "────────────────────────────────────────\n";
   }
}

void Hospital::listarFilasDeAtendimento() const {
    if (medicos.empty()) {
        std::cout << "Nenhum médico cadastrado para ter filas.\n";
        return;
    }
    
    std::cout << "--- FILAS DE ATENDIMENTO POR MÉDICO ---\n";
    for (const auto& m : medicos) {
        std::cout << "\nDr(a). " << m->getNome() << " (" << m->getEspecialidade() << ")\n";
        m->getFila().visualizarFila();
    }
}

// PERSISTÊNCIA JSON
void Hospital::salvarDados(const std::string& arquivo) {
    try {
        json j;
       j["pacientes"] = json::array();
       for (const auto& p : pacientes) {
            j["pacientes"].push_back(json::parse(p->toJSONString()));
       }
        j["medicos"] = json::array();
       for (const auto& m : medicos) {
            j["medicos"].push_back(json::parse(m->toJSONString()));
       }
        j["consultas"] = json::array();
       for (const auto& c : consultas) {
            j["consultas"].push_back(json::parse(c->toJSONString()));
       }
        j["proximoIdConsulta"] = proximoIdConsulta;
       std::ofstream arquivo_saida(arquivo);
       if (!arquivo_saida.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + arquivo);
       }
        arquivo_saida << j.dump(4);
       arquivo_saida.close();
       std::cout << "✅ Dados salvos em: " << arquivo << std::endl;
   } catch (const std::exception& e) {
        std::cerr << "❌ Erro ao salvar dados: " << e.what() << std::endl;
   }
}

void Hospital::carregarDados(const std::string& arquivo) {
    try {
        std::ifstream arquivo_entrada(arquivo);
       if (!arquivo_entrada.is_open()) {
            std::cout << "ℹ️  Nenhum arquivo de dados encontrado. Iniciando com dados vazios.\n";
           return;
        }
        json j;
       arquivo_entrada >> j;
        arquivo_entrada.close();
        
        for (auto p : pacientes) delete p;
       for (auto m : medicos) delete m;
        for (auto c : consultas) delete c;
        pacientes.clear();
        medicos.clear();
        consultas.clear();
       if (j.contains("pacientes")) {
            for (const auto& jp : j["pacientes"]) {
                Paciente* p = Paciente::fromJSONString(jp.dump());
               if (p) pacientes.push_back(p);
            }
        }
        if (j.contains("medicos")) {
            for (const auto& jm : j["medicos"]) {
                Medico* m = Medico::fromJSONString(jm.dump());
               if (m) medicos.push_back(m);
            }
        }
        if (j.contains("consultas")) {
            for (const auto& jc : j["consultas"]) {
                Consulta* c = Consulta::fromJSONString(jc.dump(), this);
               if (c) {
                    consultas.push_back(c);
                    // Recria as filas dos médicos ao carregar
                    // Só adiciona na fila se estiver AGENDADA
                    if (c->getStatus() == "Agendada" && c->getMedico()) {
                        c->getMedico()->getFila().adicionarConsulta(c);
                    }
                }
            }
        }
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