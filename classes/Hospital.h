#pragma once
#include <list>
#include <string>
#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"
#include "FilaAtendimento.h"

class Hospital {
private:
    // Listas de ponteiros que guardam os objetos instanciados de cada classe
    std::list<Paciente*> pacientes;
    std::list<Medico*> medicos;
    std::list<Consulta*> consultas;
    FilaAtendimento fila;      // Objeto que gerencia a fila 

    int proximoIdConsulta = 1; // Inicializa contador interno de IDs de consultas 

public:
    Hospital() = default;      // Construtor padrão
    ~Hospital();               // Destrutor definido em Hospital.cpp

    // CADASTROS
    void cadastrarPaciente(std::string nome, int idade, int prioridade, std::string historico = "");
    void cadastrarMedico(std::string nome, int idade, std::string crm, std::string especialidade);

    // CONSULTAS / FILA
    void agendarConsulta(std::string nomePaciente, std::string nomeMedico, std::string data);
    void adicionarNaFila(std::string nomePaciente);
    void atenderProximo();

    // BUSCAS
    Paciente* buscarPacientePorNome(const std::string& nome);
    Medico* buscarMedicoPorNome(const std::string& nome);

    // LISTAGENS
    void listarPacientes() const;
    void listarMedicos() const;
    void listarConsultas() const;
    void listarFilaAtendimento() const;

    // PERSISTÊNCIA (JSON)
    void salvarDados(const std::string& arquivo = "hospital_data.json");
    void carregarDados(const std::string& arquivo = "hospital_data.json");

    // MÉTODOS AUXILIARES
    int getTotalPacientes() const;
    int getTotalMedicos() const;
    int getTotalConsultas() const;
    const std::list<Consulta*>& getConsultas() const { return consultas; }
};

