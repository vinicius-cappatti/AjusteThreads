# AjusteThreads

## Participantes:

Thomaz de Souza Scopel | RA: 10417183 | Email: 10417183@mackenzista.com.br

Vinicius Sanches Cappatti | RA: 10418266 | Email: 10418266@mackenzista.com.br

## Objetivo:

Tendo sido disponibilizado um código em C (arquivo codigoOrinal.c) contendo um erro no uso das threads e que simula uma sequência de transações bancárias. O objetivo é encontrar o erro causado e concertá-lo.

## Problema encontrado:

O código original não protegia o acesso ao atributo 'balance' da conta bancária, o que permitia que múltiplas threads o acessassem de forma simultânea e, ocasionalmente, houvesse erros no cálculo do saldo bancário e na exibição do extrato.

## Solução:

Utilizar as funções pthread_mutex_lock e pthread_mutex_unlock para proteger o acesso ao atributo pelas threads, liberando-o somente após o fim de uma operação por uma delas. Isso impede que uma operação feita por uma das threads sobrescreva a outra e soluciona o problema original.

O código ajustado pode ser consultado no arquivo solucao.c e executado pelo arquivo solucao, que é o executável compilado no ambiente Linux do Github Codespaces.
