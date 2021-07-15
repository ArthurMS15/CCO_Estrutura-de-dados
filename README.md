# CCO_Estrutura-de-dados
# Resumo da Programação - Relatório
## Metodologia:

Este relatório estará apresentando diferentes conceitos atrelados a linguagem de programação em C utilizando o ambiente de desenvolvimento integrado (IDE): Visual Studio Code e Replit, para toda a programação. Será analisado os motivos e resultados da conclusão que foi determinada a partir da programação feita para o problema. Explicando a lógica e ferramentas para a construção do algoritmo.

Assim como o problema demonstra pelas imagens e textos, foi decidido começar pela listagem de aspectos obrigatórios para o algoritmo disponibilizados pelo orientador:

1-Uso de lista encadeada dupla;

2-Inserção, consulta, quantidade de elementos por chave, remoção, e outros;

3:
  1. O tratamento de colisão deve ser implementado a partir do momento em que duas chaves diferentes acabam apresentando o mesmo valor hash, sendo consequentemente levadas pra mesma posição na tabela hash;
  2. A implementação do tratamento pode ser feita através da implementação de uma lista encadeada (onde a mesma não apresentará um limite de nomes que podem ser colocados, então através do ponteiro "* next" a mesma pode simplesmente colocar o outro nome como um next da posição onde ela inicialmente iria ocupar);
  3. O máximo que se conseguiu alcançar é um hash que apresenta um resultado aproximadamente uniforme, entretanto não é perfeito como na teoria, na realidade todos os valores de cada chave do hash apresentam apenas um valor próximo um ao outro;
  4. Histograma:
![image](https://user-images.githubusercontent.com/66339390/125474924-59164bcb-81b0-4a54-9458-9a67a1571ef9.png)
Como é possível notar os resultados aproximam-se bastante com o **maior sendo na chave 12: 3589, e o menor na chave 19: 3361.**
E com **média: 3475** (linha vermelha do histograma)

4-Método de ordenação: quicksort;

5-Usado a base dados com 100788 nomes;

## Construção do algoritmo e resultados:

Primeiro há definição da quantidade de chaves que a hashtable terá, sendo neste caso: 29, o motivo por trás é por 29 ser o número primo mais próximo de 26 (que é a quantidade de letras do alfabeto - feito por tentativa e erro).

Logo em seguida há a construção de duas structs "entry_t" e "ht_t", uma representando o elemento da hash contendo o valor em ponteiro char, e um ponteiro para uma nova struct "entry_t" sendo este: "next" e do elemento anterior "prev".

Já a struct "ht_t" é a própria hashtable, sendo praticamente um array de ponteiros para uma "entry_t".

E logo posteriormente vem a prototipação.

![struct](https://user-images.githubusercontent.com/66339390/125795304-529e397d-d81f-4a69-a6c6-6d6f436e42dc.png)

Explorando agora os métodos, o primeiro a ser realizado é a criação do file para inserir os nomes na hashtable.

![file](https://user-images.githubusercontent.com/66339390/125795518-91949eff-9d1e-4c40-836b-a8c6d91b14d9.png)

Adiante há o método responsável por criar a a hashtable "ht_t * ht_create(void)", que no caso irá retornar a hashtable criada. 

Ele faz alocação dinâmica de memória da hashtable em si (1 ponteiro só), e também das entradas (elementos) que serão colocados na hashtable baseando-se no tamanho das chaves para o cálculo (criando neste caso então 29 ponteiros), além disso também setará todas as entradas de cada chave para valores nulos:

![image](https://user-images.githubusercontent.com/66339390/125383927-8c055700-e36e-11eb-9dc1-fc92999690ea.png)

Outro método agora é a função modular da hashtable onde retorna um valor sempre positivo e inteiro que fica entre zero e M-1, através do "value = value % M", garantido isso.

Então ele passa calculando e acumulando o valor conseguido de cada caracter do nome até seu fim:

![funcaomodularhash](https://user-images.githubusercontent.com/66339390/125795763-4e9641a9-7be9-4278-903b-faabb6f2f1dd.png)

A função "ht_pair" é responsável por alocar memória na própria entry, alocando memória para todos seus valores, setando o next e prev para null e por fim retornando a entry inicializada:

![htpair](https://user-images.githubusercontent.com/66339390/125795882-4737514b-c3f9-4bc5-8182-8a3d82f685ac.png)

Indo para o método "ht_set", o mesmo começa fazendo o hash da int bucket para saber em qual slot será colocado, quando já sabemos do slot, nós encontramos uma entry para aquele slot.

Vendo que todos os ponteiros inicializados são NULL. Começando então sendo null, é inserido um novo value naquele slot. 

Mas se a entry não for null, ou já existe uma chave e devemos atualizar o valor, ou aconteceu uma colisão (duas chaves fazendo hash no mesmo slot). E isso é corrigido da seguinte maneira: é passado por cada uma das entries até que se chegue no fim, ou até que tenha achado uma chave correspondente onde então é atualizado o valor. Chegando ao fim da lista é adicionado uma nova entry

![htset](https://user-images.githubusercontent.com/66339390/125796136-ef19cf5e-b8d2-47bc-8efe-2bae3faa2bfe.png)

Na função "ht_get" é procurado um valor através do nome. Onde é realizado uma hash da chave, e então é procurado um entry daquele slot criado, se a entry for null significa que o nome não foi encontrada, e se a entry não for null, é procurado as entries daquele slot em específico para ver se os nomes se igualam.

![htget](https://user-images.githubusercontent.com/66339390/125796289-18c8ae7f-b6c7-4849-8bec-9d7c3a37d4cd.png)

Indo para outro método envolvendo a hashtable temos "htdumpquicksort", serve para identificar o head e o tail de cada um dos slots sem a ordenação e então aplicar o quicksort no final de cada um dos slots para então deixar tudo ordenado.

![htdump](https://user-images.githubusercontent.com/66339390/125801674-d5d2df01-d32a-4dec-b319-f21b8f5414d3.png)

A função "printHt" irá printar a hashtable, mostrando quantos nomes tem no total da hashtable e quantos nomes tem em cada slot.

![printht](https://user-images.githubusercontent.com/66339390/125796782-026df251-ca9d-4685-b05d-37640b171c79.png)

Por fim da hash table é feito o método "destroy" e o "freeHashTable" que realizarão o free de toda a hash table conjuntamente com todas as entries que estiverem nela de forma recursiva:

![free](https://user-images.githubusercontent.com/66339390/125351033-f3eb7b80-e335-11eb-91c6-532e7ae0495d.png)

Concluindo há os métodos atrelados ao quicksort sendo eles "quicksort", "midFind" "swap" responsáveis pela ordenação dos elementos encontrados em cada lista da hashtable.

O método do quicksort pegará de referência o head e o tail de um determinado slot da tabela hash e então começará o sort.

É criado variáveis temporárias necessárias para o funcionamento do mesmo "i = head->prev", "pivo = midFind(hashtable, head)", "temp" e "j = head".

O método "midFind" determinará o valor do elemento pivo, encontrando no determinado slot da hashtable o elemento do meio da lista.

![midFind](https://user-images.githubusercontent.com/66339390/125797200-a0edac80-0ecc-4cab-bf4d-37be51b9b120.png)

Passando então pela a lista ele vai comparando os tamanhos das strings e se o valor encontrado for menor que o pivo é trocado com a variável i.

![quicksort](https://user-images.githubusercontent.com/66339390/125797410-1fcccc89-aa54-47b0-9366-2fa3e5471358.png)

No main haverá então o processo dos métodos para o funcionamento do código:

![main](https://user-images.githubusercontent.com/66339390/125797515-fd485d94-4315-4ba9-8d89-a0563410bd81.png)

# Referências

CS.UTAH. **Unsigned Integers.** Disponível em: <https://www.cs.utah.edu/~germain/PPS/Topics/unsigned_integer.html>. Acesso em: 3 jul. 2021.

GITHUB. **Hashchain.c.** Disponível em: <https://gist.github.com/chrispiccaro18/63cfce1337e71c9aac6012bf92607337>. Acesso em: 3 jul. 2021.

GITHUB. **Main_encadeada.c.** Disponível em: <https://github.com/MarlonVCendron/Trabalho-Sort-ED/blob/master/codigo/quicksort/main_encadeada.c>. Acesso em: 3 jul. 2021.

REPLIT. **ED - HASH - Exemplo.** Disponível em: <https://replit.com/@ManassesRibeiro/ED-HASH-Exemplo>. Acesso em: 9 jul. 2021.

YOUTUBE. **Data Structures: Hash Table implementation in C.** Disponível em: <https://www.youtube.com/watch?v=wg8hZxMRwcw>. Acesso em: 3 jul. 2021.

YOUTUBE. **Programar em C - Manipulação de Arquivos txt em C / Ler Dados - Aula 83.** Disponível em: <https://www.youtube.com/watch?v=USsUSMpNGsM>. Acesso em: 3 jul. 2021.
