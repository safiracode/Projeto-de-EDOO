# 🏥 Sistema Hospitalar em C++

## 📘 Descrição do Projeto
Este projeto implementa um **sistema hospitalar orientado a objetos em C++**, desenvolvido com o objetivo de simular o fluxo básico de um hospital: desde o **cadastro de pacientes e médicos**, passando pelo **agendamento de consultas** até o **registro do histórico de atendimentos**.

O sistema foi construído aplicando os principais conceitos da **Programação Orientada a Objetos (POO)**:
- **Encapsulamento**: controle de acesso aos atributos das classes.
- **Herança**: especialização de classes, como `Paciente` e `Medico` herdando de `Pessoa`.
- **Polimorfismo**: redefinição de métodos e comportamentos.
- **Composição e agregação**: relacionamento entre classes (`Hospital`, `Consulta`, `FilaAtendimento`, etc).

Além disso, o projeto utiliza a biblioteca **nlohmann/json** para realizar a **persistência de dados em formato JSON**, permitindo salvar e recuperar informações do sistema sem necessidade de um banco de dados real.

---

## 🧱 Estrutura de Pastas
├── .vscode/
│ ├── settings.json
│ └── tasks.json
├── classes/
│ ├── ComparadorPaciente.h
│ ├── Consulta.h
│ ├── FilaAtendimento.h
│ ├── Hospital.h
│ ├── Medico.h
│ ├── Paciente.h
│ ├── Pessoa.h
│ └── Relatorios.h
├── include/
│ └── nlohmann/
│ └── json.hpp
├── src/
│ ├── Consulta.cpp
│ ├── FilaAtendimento.cpp
│ ├── Hospital.cpp
│ ├── main.cpp
│ ├── Medico.cpp
│ ├── Paciente.cpp
│ ├── Pessoa.cpp
│ └── Relatorios.cpp
└── Makefile

---

## ⚙️ Como Compilar e Executar

### 🔹 Pré-requisitos
- **Compilador C++17** ou superior (`g++`, `clang++`, etc.)
- **Make** ou **MinGW Make**
- **Biblioteca nlohmann/json** (já incluída na pasta `include/nlohmann/json.hpp`)

---
  
### 🪟 **Windows (PowerShell ou CMD)**
1. Abra o terminal na raiz do projeto.
2. Para compilar:
   ```powershell
   mingw32-make
3. Para limpar e recompilar do zero:
   ```powershell
   mingw32-make rebuild
4. Após a compilação, o executável será gerado na pasta:
   ```powershell
   bin/hospital.exe
5. Para executar:
   ```powershell
   bin/hospital.exe

---

### 🐧 **Linux / macOS (Bash ou Terminal)**
1. Abra o terminal na raiz do projeto.
2. Para compilar:
   ```bash
   make
3. Para limpar e recompilar do zero:
   ```bash
   make rebuild
4. Após a compilação, o executável será gerado na pasta:
   ```bash
   bin/hospital
5. Para executar:
   ```bash
   ./bin/hospital

### 📄 **Licença | Autoria**
Este projeto é de uso acadêmico e livre para fins educacionais. Foi desenvolvido por:
- **Ana Laura Barboza**
- **Caio Cesar Nascimento**
- **Eduardo Alves**
- **Letícia Staudinger**
- **Safira Moraes**
