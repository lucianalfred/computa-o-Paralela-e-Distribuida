# Computação Paralela e Distribuída (CPD)

## Descrição
Este repositório contém materiais, códigos e documentação relacionados à disciplina de **Computação Paralela e Distribuída (CPD)**. Aqui, serão armazenados exemplos de código, relatórios de laboratório e implementações de exercícios práticos para auxiliar no aprendizado sobre processamento paralelo e distribuído.

## Estrutura do Repositório
```
CPD/
├── Lab-1/                  # Laboratório 1 - Introdução ao Ambiente Unix e Ferramentas de Desenvolvimento
│   ├── src/                # Códigos-fonte em C
│   ├── Makefile            # Arquivo para compilação automatizada
│   ├── Relatorio.md        # Relatório sobre a prática
│   └── README.md           # Instruções específicas do Lab-1
├── Lab-2/                  # Laboratório 2 - Introdução a Threads e OpenMP
│   ├── src/
│   ├── Makefile
│   ├── Relatorio.md
│   └── README.md
├── Exercicios/             # Lista de exercícios resolvidos
│   ├── exercicio1/
│   ├── exercicio2/
│   └── ...
├── Projetos/               # Projetos práticos da disciplina
│   ├── Projeto-1/
│   ├── Projeto-2/
│   └── ...
└── README.md               # Este arquivo
```

## Tecnologias Utilizadas
- **Linguagem:** C
- **Compilador:** GCC (GNU Compiler Collection)
- **Depurador:** GDB (GNU Debugger)
- **Ferramenta de Automação:** Make
- **Controle de Versão:** Git
- **Programação Paralela:** OpenMP, Pthreads

## Como Executar os Laboratórios
1. Clone o repositório:
   ```sh
   git clone https://github.com/seu-usuario/CPD.git
   cd CPD/Lab-1
   ```
2. Compile os arquivos:
   ```sh
   make
   ```
3. Execute o programa:
   ```sh
   ./main
   ```
4. Para depuração com GDB:
   ```sh
   gdb ./main
   ```
5. Para limpar os arquivos compilados:
   ```sh
   make clean
   ```

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir um **Pull Request** ou sugerir melhorias na **Issues**.

## Autor
Desenvolvido por [Seu Nome].

## Licença
Este projeto é licenciado sob a MIT License - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

