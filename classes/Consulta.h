#pragma once
#include <string>

class Paciente; 
class Medico;

class Consulta {
private:

    int id;
    Paciente* paciente;
    Medico* medico;
    std::string data;
    std::string status; // "Agendada", "Concluída", "Cancelada"

public:
    // Construtor
    Consulta(int id, Paciente* p, Medico* m, std::string data)
        : id(id), paciente(p), medico(m), data(data), status("Agendada") {}

    void concluirConsulta() {
        this->status = "Concluída";
    }

    void cancelarConsulta() {
        this->status = "Cancelada";
    }

    Medico* getMedico() const { return medico; }
    Paciente* getPaciente() const { return paciente; }

    // O comparador de PRIORIDADE (emergência) está no ComparadorPaciente.
    // Se precisar ordenar uma lista de Consultas (talvez por data),
    // o operador seria assim:
    bool operator<(const Consulta& outra) const {
        return this->data < outra.data;
    }

};