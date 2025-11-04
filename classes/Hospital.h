#pragma once
#include <list>
#include <string>
#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"
#include "FilaAtendimento.h"
#include "Medico.h" 

class Hospital {
private:
    std::list<Paciente*> pacientes;
    std::list<Medico*> medicos;
    std::list<Consulta*> consultas;    

    int proximoIdConsulta = 1;

public:
    Hospital() = default;
   ~Hospital();              

    // CADASTROS
    void cadastrarPaciente(std::string nome, int idade, int prioridadeVulnerabilidade, std::string historico = "");
   void cadastrarMedico(std::string nome, int idade, std::string crm, std::string especialidade);

    // EDIÇÃO
    void editarPaciente(const std::string& nomeAtual);
    void editarMedico(const std::string& nomeAtual);
    void editarConsulta(int consultaId);

    // REMOÇÃO
    bool removerPaciente(const std::string& nome);
    bool removerMedico(const std::string& nome);
    bool removerConsulta(int consultaId);

    // CONSULTAS / FILA
    void agendarEEnfileirar(std::string nomePaciente, std::string nomeMedico, std::string data, int prioridadeTriagem);
    void atenderProximo(std::string nomeMedico);
    
    // Função para cancelar uma consulta
    void cancelarConsulta(int consultaId);

    // BUSCAS
    Paciente* buscarPacientePorNome(const std::string& nome);
    Medico* buscarMedicoPorNome(const std::string& nome);
    // Precisamos de uma forma de buscar consulta por ID
    Consulta* buscarConsultaPorId(int id);

    // VALIDAÇÃO
    bool pacientePossuiConsultas(const std::string& nomePaciente) const;
    bool medicoPossuiConsultas(const std::string& nomeMedico) const;

    // LISTAGENS
    void listarPacientes() const;
    void listarMedicos() const;
    void listarConsultas() const;
    void listarFilasDeAtendimento() const;

    // PERSISTÊNCIA (JSON)
    void salvarDados(const std::string& arquivo = "hospital_data.json");
    void carregarDados(const std::string& arquivo = "hospital_data.json");

    // MÉTODOS AUXILIARES
    int getTotalPacientes() const;
    int getTotalMedicos() const;
    int getTotalConsultas() const;
   const std::list<Consulta*>& getConsultas() const { return consultas; }
};