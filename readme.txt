Grupo:
    Leonardo Kaplan 1212509 
    Eric Grinstein  1310428

O projeto:

    Fizemos uma biblioteca para comunicação entre threads.
    Ela trabalha de 2 formas: síncrona e assíncronamente.
        síncrona:
            para o usuário, os pacotes são enviados diretamente, como se a operação fosse atômica, como se fosse uma chamada normal de função.
        assíncrona:
            os pacotes são enviados para um buffer, de onde podem ser lidos.
            para o usuário, a thread espera até poder ler um pacote.


Como executar:

    make 
    
    gerará 4 executaveis: 3 exemplos de comunicação assíncrona e 1 de síncrona.
    
    execute cada um com:

    ./sync
    ./async
    ./async2
    ./async3

Metodologia:

    Foram implementados dois mutexes para o canal síncrono.
    Para enviar uma mensagem, o mutex 'write' deve estar destravado.
    Ao terminar de enviar a mensagem, o mutex 'read' é destravado, sinalizando
    que o buffer pode ser consumido. 
    Para a leitura de mensagens, os mutexes devem estar na posição inversa do envio,
    explicado acima.

    A implementação é similar no buffer assíncrono, porém há 2 semáforos 


Testes:

    Testamos as 2 opções de comunicação variando os parametros numero de produtores, numero de consumidores e quantidade de elementos produzidos/consumidos. 
    No caso da comunicação assíncrona também variamos o tamanho do buffer. 
    Pode-se observar os testes feitos como comentários no Makefile.
    Era esperado que os testes em que o numero de consumidores é diferente do de produtores não terminassem, visto que os consumidores ficam bloqueados esperando para consumir (porém os produtores já produziram tudo) ou vice versa.
    Como os testes descritos acima não terminam, como esperado, não os habilitamos como exemplos.
