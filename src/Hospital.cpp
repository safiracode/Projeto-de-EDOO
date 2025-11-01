#include "Hospital.h"
#include <iostream>
#include <stdexcept>
#include "Relatorios.h"

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
