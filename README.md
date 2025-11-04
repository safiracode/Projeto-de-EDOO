# 🏥 Sistema Hospitalar em C++

## 📘 Descrição do Projeto
Esse projeto implementa um **Sistema Hospitalar orientado a objetos em C++** e foi desenvolvido como parte da disciplina de Estruturas de Dados Orientadas a Objetos (EDOO), com o propósito de aplicar os conhecimentos adquiridos ao longo do semestre em um projeto prático e colaborativo.

O projeto foi desenvolvido com o objetivo de simular o fluxo interno de um hospital: desde o **cadastro de pacientes e médicos**, passando pelo **agendamento de consultas**, até o **registro do histórico de atendimentos**.

Durante o desenvolvimento do sistema, o grupo buscou criar um código com uma arquitetura clara, de forma a possibilitar observar conceitos reais da área da saúde através da lógica de programação. Além disso, o sistema mostra como a POO pode ser utilizada para estruturar aplicações que combinam organização, flexibilidade e clareza.

---

## 👥 Membros da Equipe 
<table> 
  <tr> 
    <td align="center"> 
      <a href="https://github.com/analauraboliveira"> 
        <img src="https://avatars.githubusercontent.com/u/207280291?v=4" width="115"><br> 
        <sub><b>Ana Laura Barboza</b></sub><br> <sub>(<code>analauraboliveira</code>)</sub> 
      </a> 
    </td> 
    <td align="center"> 
      <a href="https://github.com/CaioVBoas"> 
        <img src="https://avatars.githubusercontent.com/u/100202613?v=4" width="115"><br> 
        <sub><b>Caio Cesar Nascimento</b></sub><br> <sub>(<code>CaioVBoas</code>)</sub> 
      </a> 
    </td> 
    <td align="center"> 
      <a href="https://github.com/Edo-Alve5"> 
        <img src="https://media-for2-1.cdn.whatsapp.net/v/t61.24694-24/484208345_1875642679850162_6002395139070660778_n.jpg?ccb=11-4&oh=01_Q5Aa2wFiCpbyM5sNUZfNnsWtJWS89EvNuel8qniWy9wQoe5qpg&oe=691789A2&_nc_sid=5e03e0&_nc_cat=100" width="115"><br> 
        <sub><b>Eduardo Alves</b></sub><br> <sub>(<code>Edo-Alve5</code>)</sub> 
      </a> 
    </td> 
    <td align="center"> 
      <a href="https://github.com/lestrb"> 
        <img src="https://avatars.githubusercontent.com/u/193823503?v=4" width="115"><br> 
        <sub><b>Letícia Staudinger</b></sub><br> <sub>(<code>lestrb</code>)</sub> 
      </a> 
    </td> 
    <td align="center"> 
      <a href="https://github.com/safiracode"> 
        <img src="https://avatars.githubusercontent.com/u/206463303?v=4" width="115"><br> 
        <sub><b>Safira Moraes</b></sub><br> <sub>(<code>safiracode</code>)</sub> 
      </a> 
    </td> 
  </tr> 
</table> 

## 👨‍💻 Divisão de tarefas do projeto

| Time                                                  | Tarefas                                                                                |
| ----------------------------------------------------- | -------------------------------------------------------------------------------------- |
| [Ana Laura Barboza Oliveira dos Santos]                | classe Relatorio; testes; Read Me do GitHub |
| [Caio César Nascimento Vilas Boas]                  |  main; persistência de dados JSON |
| [Eduardo Pinto Alves]                               | classes Pessoa, Paciente e Medico; Makefile |
| [Letícia Staudinger Ribeiro]              | classe Hospital; relatório (entrega); testes e correções; GitHub Page |
| [Safira Moraes Gomes]               | classes Consulta e FilaAtendimento; vídeo para o Youtube |

---

## 💡 Conceitos da disciplina aplicados
Durante o desenvolvimento do **Sistema Hospitalar**, colocamos em prática diversos conceitos fundamentais da disciplina, aplicando-os diretamente na arquitetura do projeto, como:
- Os _comandos condicionais_ (`if`, `else if`, `else`) foram essenciais para controlar o fluxo das operações e definir comportamentos distintos para cada tipo de usuário ou ação do sistema.
- Os _laços de repetição_ (`for`, `while`) foram amplamente usados para percorrer listas de pacientes, médicos e consultas, além de exibir informações e processar dados de forma dinâmica.
- A _modularização_ foi aplicada ao dividir o projeto em múltiplos arquivos (`.h` e `.cpp`), separando a declaração das classes de suas implementações, o que favoreceu a organização e manutenção do código.

Além disso, o sistema foi construído aplicando os principais conceitos da **Programação Orientada a Objetos (POO)**. Cada entidade principal do sistema (como `Pessoa`, `Paciente`, `Medico`, `Consulta` e `Hospital`) foi modelada como uma classe, com atributos e métodos que reproduzem comportamentos reais, aplicando encapsulamento, herança, polimorfismo e composição:
- **Encapsulamento**: controle de acesso aos atributos das classes;
- **Herança**: especialização de classes, como `Paciente` e `Medico` herdando de `Pessoa`;
- **Polimorfismo**: redefinição de métodos e comportamentos;
- **Composição e agregação**: relacionamento entre classes (`Hospital`, `Consulta`, `FilaAtendimento`, etc).

Por fim, o projeto utiliza a biblioteca **nlohmann/json** para realizar a **persistência de dados em formato JSON**, permitindo salvar e recuperar informações do sistema sem necessidade de um banco de dados real.

## 🛠️ Ferramentas, frameworks e bibliotecas utilizados 
Para o desenvolvimento do _Sistema Hospitalar_, utilizamos um conjunto de ferramentas e tecnologias, que tornaram possível criar um projeto tecnicamente funcional. Esses recursos foram:
- **C++** — Linguagem principal do projeto, utilizada para a implementação da lógica, organização das classes e integração de todas as partes do sistema.
- **nlohmann/json** — Biblioteca usada para realizar a persistência de dados em formato JSON, permitindo salvar e recuperar informações sem um banco de dados real.
- **Visual Studio Code** — Editor de código adotado pela equipe, com extensões para depuração e integração com o GitHub.
- **Makefile** — Usado para automatizar o processo de compilação e limpeza dos arquivos gerados.
- **GitHub** — Usado para o controle de versão, acompanhamento das alterações e colaboração remota de forma organizada.  
- **Discord e WhatsApp** — Aplicativos de comunicação, utilizados para o alinhamento de equipe, com mensagens e reuniões por chamada de vídeo..
---

## 🧱 Estrutura de Pastas
```
├── .vscode/
│   ├── settings.json
│   └── tasks.json
│
├── classes/
│   ├── ComparadorPaciente.h
│   ├── Consulta.h
│   ├── FilaAtendimento.h
│   ├── Hospital.h
│   ├── Medico.h
│   ├── Paciente.h
│   ├── Pessoa.h
│   └── Relatorios.h
│
├── include/
│   └── nlohmann/
│       └── json.hpp
│
├── src/
│   ├── Consulta.cpp
│   ├── FilaAtendimento.cpp
│   ├── Hospital.cpp
│   ├── main.cpp
│   ├── Medico.cpp
│   ├── Paciente.cpp
│   ├── Pessoa.cpp
│   └── Relatorios.cpp
│
└── Makefile
```

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
   
---

### 📄 **Licença**
Este projeto é de uso acadêmico e livre para fins educacionais.
