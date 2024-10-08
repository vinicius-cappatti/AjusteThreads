/* **********************************************************************************
* PARTICIPANTES:
*   Thomaz de Souza Scopel | RA: 10417183 | Email: 10417183@mackenzista.com.br
*   Vinicius Sanches Cappatti | RA: 10418266 | Email: 10418266@mackenzista.com.br
* OBJETIVO:
*   Identificar o problema do codigo disponibilizado pela atividade, disponivel no
*   arquivo codigoOriginal.c desse repositorio, e solucionar para impedir que as
*   threads entrem em conflito.
* RESOLUÇÃO:
*   Utilizar as funções pthread_mutex_lock e pthread_mutex_unlock na execução de
*   cada saque ou depósito para evitar que múltiplas threads acessem o 'balance' da
*   conta bancária ao mesmo tempo. As alterações foram feitas nas funções 
*   transaction_dep e transaction_sac, executadas por cada thread.
*   As alterações estão nas linhas 54, 56, 65 e 67.
*   Além disso, foi necessário alterar a ordem de criação das threads de saque para
*   que esperassem o fim da execução das threads de depósito.
********************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define INITIAL_BALANCE 1000
#define NUM_THREADS 10
#define TRANSFER_AMOUNT 50

// Estrutura para armazenar informações da conta
typedef struct {
    int balance;
    pthread_mutex_t mutex;
} BankAccount;

// Função para depositar uma quantia na conta
void deposit(BankAccount *account, int amount) {
    account->balance += amount;
    printf("Depositado: %d, Saldo Atual: %d\n", amount, account->balance);
}

// Função para sacar uma quantia da conta
void withdraw(BankAccount *account, int amount) {
    if (account->balance >= amount) {
        account->balance-= amount;
        printf("Sacado: %d, Saldo Atual: %d\n", amount, account->balance);
    } else {
        printf("Saldo Insuficiente para saque: %d\n", amount);
    }
}

// Função executada pelas threads
void* transaction_dep(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    // Realiza uma série de depósitos e saques
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&account->mutex); // Proteção do balanço
        deposit(account, TRANSFER_AMOUNT);
        pthread_mutex_unlock(&account->mutex); // Liberação para as outras threads
        sleep(3); // Simula algum tempo de processamento
    }
    return NULL;
}
void* transaction_sac(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    // Realiza uma série de depósitos e saques
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&account->mutex); // Proteção do balanço
        withdraw(account, TRANSFER_AMOUNT);
        pthread_mutex_unlock(&account->mutex); // Liberação para as outras threads
        sleep(1); // Simula algum tempo de processamento
    }
    return NULL; 
}

int main() {
    pthread_t threads_dep[NUM_THREADS];
    pthread_t threads_sac[NUM_THREADS];
    BankAccount account;
    account.balance = INITIAL_BALANCE;
    pthread_mutex_init(&account.mutex, NULL);
    
    // Cria as threads de depósito
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads_dep[i], NULL, transaction_dep, &account) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Espera todas as threads de depósito terminarem terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads_dep[i], NULL) != 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
            sleep(1);
        }
    }

    // Cria as threads de saque
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads_sac[i], NULL, transaction_sac, &account) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Espera todas as threads de saque terminarem terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads_sac[i], NULL) != 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }
    
    // Destrói o mutex
    pthread_mutex_destroy(&account.mutex);
 
    // Imprime o saldo final
    printf("Saldo Final: %d\n", account.balance);
    
    return 0;
}