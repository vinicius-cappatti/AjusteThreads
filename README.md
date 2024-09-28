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

![Exemplo erro](/printsRetirados/image.png)

Neste fim de execução é possivel observar que houve um erro pois ao adicionar mais 50 ao fim após ter chegado em 1500, o saldo total foi para 1450 e o saldo final permaneceu 1500, o que demonstra o provável conflito entre diferentes threads em execução.

## Solução:

Utilizar as funções pthread_mutex_lock e pthread_mutex_unlock para proteger o acesso ao atributo pelas threads, liberando-o somente após o fim de uma operação por uma delas. Isso impede que uma operação feita por uma das threads sobrescreva a outra e soluciona o problema original.

Além disso, foi necessário alterar a ordem de criação das threads de saque para que esperassem o fim da execução das threads de depósito.

Com essas alterações, o saldo remanescente das operações é sempre 1000, visto que o mesmo número de operações de depósito e de saque são operadas.

O código ajustado pode ser consultado no arquivo solucao.c e executado pelo arquivo solucao, que é o executável compilado no ambiente Linux do Github Codespaces.

**Casos Teste**

Caso teste 1:

![Teste 1](/printsRetirados/teste1.png)
![Teste 1.1](/printsRetirados/teste1_1.png)

Caso teste 2:

![Teste 2](/printsRetirados/teste2.png)
![Teste 2.1](/printsRetirados/teste2_1.png)

