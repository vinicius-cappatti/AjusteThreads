# AjusteThreads

## Participantes:

|Nome|RA|Email|
|---|---|---|
Thomaz de Souza Scopel | 10417183 | 10417183@mackenzista.com.br
Vinicius Sanches Cappatti | 10418266 |10418266@mackenzista.com.br

## Objetivo:

Tendo sido disponibilizado um código em C (arquivo codigoOrinal.c) contendo um erro no uso das threads e que simula uma sequência de transações bancárias. O objetivo é encontrar o erro causado e concertá-lo.

## Problema encontrado:

O código original não protegia o acesso ao atributo 'balance' da conta bancária, o que permitia que múltiplas threads o acessassem de forma simultânea e, ocasionalmente, houvesse erros no cálculo do saldo bancário e na exibição do extrato.

Exemplo do erro encontrado:
![Exemplo erro](/workspaces/AjusteThreads/printsRetirados/image.png)

Neste fim de execução é possivel observar que houve um erro pois ao adicionar mais 50 ao fim após ter chegado em 1500, o saldo total foi para 1450 e o saldo final permaneceu 1500, o que demonstra o provável conflito entre diferentes threads em execução.

## Solução:

Utilizar as funções pthread_mutex_lock e pthread_mutex_unlock para proteger o acesso ao atributo pelas threads, liberando-o somente após o fim de uma operação por uma delas. Isso impede que uma operação feita por uma das threads sobrescreva a outra e soluciona o problema original.

O código ajustado pode ser consultado no arquivo solucao.c e executado pelo arquivo solucao, que é o executável compilado no ambiente Linux do Github Codespaces.

**Casos Teste**
Caso teste 1:
![Teste1](/workspaces/AjusteThreads/printsRetirados/image-1.png)
![Teste1.1](/workspaces/AjusteThreads/printsRetirados/image-2.png)
Caso teste 2:
![Teste2](/workspaces/AjusteThreads/printsRetirados/image-3.png)
![Teste2.1](/workspaces/AjusteThreads/printsRetirados/image-4.png)