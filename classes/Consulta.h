#pragma once
#include <stdexcept>
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

    int prioridadeTriagem;
    long long ordemChegada;

public:
    Consulta(int id, Paciente* p, Medico* m, std::string data, int prioridadeTriagem)
        : id(id), 
          paciente(p), 
          medico(m), 
          data(data), 
          status("Agendada"), // Status inicial
          ordemChegada(0)  // Ordem inicial
    {
        // Validação da prioridade de triagem
        setPrioridadeTriagem(prioridadeTriagem);
    }

    void concluirConsulta() {
        this->status = "Concluída";
    }

    void cancelarConsulta() {
        this->status = "Cancelada";
    }

    // --- Getters públicos ---
    int getId() const { return id; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
    std::string getData() const { return data; }
    std::string getStatus() const { return status; }
    
    void setData(const std::string& novaData) { this->data = novaData; }
    
    void setPrioridadeTriagem(int p) {
        if (p < 1 || p > 3) {
            throw std::invalid_argument("Prioridade de triagem invalida. Use 1 (Emergência), 2 (Urgência) ou 3 (Estável).");
        }
        this->prioridadeTriagem = p;
    }
    
    int getPrioridadeTriagem() const { 
        return prioridadeTriagem; 
    }

    void setOrdemChegada(long long ordem) {
        this->ordemChegada = ordem;
    }
    
    long long getOrdemChegada() const {
        return ordemChegada;
    }
    
    // Serialização JSON
    std::string toJSONString() const;
    static Consulta* fromJSONString(const std::string& jsonStr, Hospital* hospital);
};