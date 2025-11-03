#pragma once

#include <string>

class Paciente; 
class Medico;
class Hospital;

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

    // Getters públicos
    int getId() const { return id; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
    std::string getData() const { return data; }
    std::string getStatus() const { return status; }

    // O comparador de PRIORIDADE (emergência) está no ComparadorPaciente.
    // Se precisar ordenar uma lista de Consultas (talvez por data),
    // o operador seria assim:
    bool operator<(const Consulta& outra) const {
        return this->data < outra.data;
    }

    // Serialização JSON (implementado em Consulta.cpp)
    std::string toJSONString() const;
    static Consulta* fromJSONString(const std::string& jsonStr, Hospital* hospital);
};