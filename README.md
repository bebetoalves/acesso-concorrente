# Acesso Concorrente a um Array

Esta documentação fornece uma visão geral de um programa de acesso concorrente a um array implementado em C usando threads e exclusão mútua.

## Sumário

- [Introdução](#introdução)
- [Funções](#funções)
  - [Escritor](#escritor)
  - [Leitor](#leitor)
- [Uso](#uso)
- [Conclusão](#conclusão)

## Introdução

O programa de acesso concorrente a um array demonstra como lidar com operações de leitura e escrita concorrentes em um array compartilhado usando threads. Ele utiliza técnicas de exclusão mútua para garantir a sincronização das threads e evitar condições de corrida.

## Funções

### Escritor

```c
void *writer(void *thread_id)
```

A função `writer` representa a lógica para as threads escritoras. Ela escreve valores aleatórios no array compartilhado.

- `thread_id`: O identificador único da thread escritora.
- Escreve valores no array até que ele esteja cheio.
- Utiliza um bloqueio (`rwlock`) para garantir escrita exclusiva.
- Aguarda 1 segundo entre cada operação de escrita.

### Leitor

```c
void *reader(void *thread_id)
```

A função `reader` representa a lógica para as threads leitoras. Ela lê os valores do array compartilhado.

- `thread_id`: O identificador único da thread leitora.
- Lê os valores do array até que todas as threads escritoras tenham terminado.
- Utiliza um bloqueio (`rwlock`) para permitir leitura concorrente.
- Aguarda 1 segundo entre cada operação de leitura.

## Uso

1. Compile o programa C com um compilador C, por exemplo: `gcc -pthread -o acesso_concorrente acesso_concorrente.c`.
2. Execute o programa compilado: `./acesso_concorrente`.
3. Você verá um resultado similar a este:

```log
$ gcc -pthread -o acesso_concorrente acesso_concorrente.c
$ ./acesso_concorrente
$ [Thread Reader #1] Array values: - - - - - 
$ [Thread Reader #2] Array values: - - - - - 
$ [Thread Reader #3] Array values: - - - - - 
$ [Thread Reader #4] Array values: - - - - - 
$ [Thread Reader #5] Array values: - - - - - 
$ [Thread Reader #6] Array values: - - - - - 
$ [Thread Reader #7] Array values: - - - - - 
$ [Thread Reader #8] Array values: - - - - - 
$ [Thread Reader #9] Array values: - - - - - 
$ [Thread Reader #10] Array values: - - - - - 
$ [Thread Reader #11] Array values: - - - - - 
$ [Thread Reader #12] Array values: - - - - - 
$ [Thread Reader #13] Array values: - - - - - 
$ [Thread Reader #14] Array values: - - - - - 
$ [Thread Writer #1] Writing number: 82
$ [Thread Writer #2] Writing number: 25
$ [Thread Reader #1] Array values: 82 25 - - - 
$ [Thread Reader #2] Array values: 82 25 - - - 
$ [Thread Reader #3] Array values: 82 25 - - - 
$ [Thread Reader #4] Array values: 82 25 - - - 
$ [Thread Reader #5] Array values: 82 25 - - - 
$ [Thread Reader #6] Array values: 82 25 - - - 
$ [Thread Reader #7] Array values: 82 25 - - - 
$ [Thread Reader #8] Array values: 82 25 - - - 
$ [Thread Reader #9] Array values: 82 25 - - - 
$ [Thread Reader #10] Array values: 82 25 - - - 
$ [Thread Reader #11] Array values: 82 25 - - - 
$ [Thread Reader #12] Array values: 82 25 - - - 
$ [Thread Reader #13] Array values: 82 25 - - - 
$ [Thread Reader #14] Array values: 82 25 - - - 
$ [Thread Writer #1] Writing number: 28
$ [Thread Writer #2] Writing number: 67
$ [Thread Reader #1] Array values: 82 25 28 67 - 
$ [Thread Reader #2] Array values: 82 25 28 67 - 
$ [Thread Reader #3] Array values: 82 25 28 67 -
$ [Thread Reader #4] Array values: 82 25 28 67 - 
$ [Thread Reader #5] Array values: 82 25 28 67 - 
$ [Thread Reader #6] Array values: 82 25 28 67 - 
$ [Thread Reader #7] Array values: 82 25 28 67 - 
$ [Thread Reader #8] Array values: 82 25 28 67 - 
$ [Thread Reader #9] Array values: 82 25 28 67 - 
$ [Thread Reader #10] Array values: 82 25 28 67 - 
$ [Thread Reader #11] Array values: 82 25 28 67 - 
$ [Thread Reader #12] Array values: 82 25 28 67 - 
$ [Thread Reader #13] Array values: 82 25 28 67 - 
$ [Thread Reader #14] Array values: 82 25 28 67 - 
$ [Thread Writer #1] Writing number: 5
$ [Thread Reader #1] Array values: 82 25 28 67 5 
$ [Thread Reader #2] Array values: 82 25 28 67 5 
$ [Thread Reader #3] Array values: 82 25 28 67 5 
$ [Thread Reader #4] Array values: 82 25 28 67 5 
$ [Thread Reader #5] Array values: 82 25 28 67 5 
$ [Thread Reader #6] Array values: 82 25 28 67 5 
$ [Thread Reader #7] Array values: 82 25 28 67 5 
$ [Thread Reader #8] Array values: 82 25 28 67 5 
$ [Thread Reader #9] Array values: 82 25 28 67 5 
$ [Thread Reader #10] Array values: 82 25 28 67 5 
$ [Thread Reader #11] Array values: 82 25 28 67 5 
$ [Thread Reader #12] Array values: 82 25 28 67 5 
$ [Thread Reader #13] Array values: 82 25 28 67 5 
$ [Thread Reader #14] Array values: 82 25 28 67 5 
```

## Conclusão

O programa de acesso concorrente a um array demonstra como gerenciar o acesso concorrente a um array compartilhado