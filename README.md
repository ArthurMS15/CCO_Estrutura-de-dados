# CCO_Estrutura-de-dados
# Resumo da Programação - Relatório
## Metodologia:

Este relatório estará apresentando diferentes conceitos atrelados a linguagem de programação em C utilizando o ambiente de desenvolvimento integrado (IDE): Visual Studio Code e Replit, para toda a programação. Será analisado os motivos e resultados da conclusão que foi determinada a partir da programação feita para o problema. Explicando a lógica e ferramentas para a construção do algoritmo.

Assim como o problema demonstra pelas imagens e textos, foi decidido começar pela listagem de aspectos obrigatórios para o algoritmo disponibilizados pelo orientador:

1-Uso de lista encadeada dupla;

2-Inserção, consulta, quantidade de elementos por chave, remoção, e outros;

3:
  1. O tratamento de colisão deve ser implementado a partir do momento em que um novo nome acaba ocupando e substituindo o mesmo local onde havia um nome anterior (dados diferentes na mesma posição);
  2. A implementação do tratamento pode ser feita através da construção da struct dos nomes, onde a mesma apresentará um ponteiro "* next", levando então para outro nome e assim em diante;
  3. O máximo que se conseguiu alcançar é um hash que apresenta um resultado aproximadamente uniforme, entretanto não é perfeito como na teoria, na realidade todos os valores de cada chave do hash apresentam apenas um valor próximo um ao outro;
  4. Histograma:
![histograma](https://github.com/ArthurMS15/CCO_Estrutura-de-dados/blob/main/Histograma.png)   
Como é possível notar os resultados aproximam-se bastante com o **maior sendo na chave 12: 3589, e o menor na chave 19: 3361.**

4-Método de ordenação: quicksort;

5-Usado a base dados com 100788 nomes;

## Construção do algoritmo e resultados:

Primeiro há definição da quantidade de chaves que a hashtable terá, sendo neste caso: 29, o motivo por trás é por 29 ser o número primo mais próximo de 26 (que é a quantidade de letras do alfabeto - feito por tentativa e erro).

Logo em seguida há a construção de duas structs "entry_t" e "ht_t", uma representando o elemento da hash contendo a key (chave), o valor em char, e um ponteiro para uma nova struct "entry_t" sendo este: "next" (evitando colisões nesse caso, porque então ele passa pra proxima posição na hashtable) e do elemento anterior "prev".

Já a struct "ht_t" é a própria hashtable, sendo praticamente um array de ponteiros para uma "entry_t".

E logo posteriormente vem a prototipação.

![struct](https://user-images.githubusercontent.com/66339390/125383790-61b39980-e36e-11eb-9c2d-8b487ae5e457.png)

Explorando agora os métodos, há o método responsável por criar a a hashtable "ht_t * ht_create(void)", que no caso irá retornar a hashtable criada. 

Ele faz alocação dinâmica de memória da hashtable em si (1 ponteiro só), e também das entradas (elementos) que serão colocados na hashtable baseando-se no tamanho das chaves para o cálculo (criando neste caso então 29 ponteiros), além disso também setará todas as entradas de cada chave para valores nulos:

![image](https://user-images.githubusercontent.com/66339390/125383927-8c055700-e36e-11eb-9dc1-fc92999690ea.png)

Outro método agora é a função modular da hashtable onde retorna um valor sempre positivo e inteiro que fica entre zero e M-1, através do "value = value % M", garantido isso.

Então ele passa calculando e acumulando o valor conseguido de cada caracter do nome até seu fim:

![funcaomodularhash](https://user-images.githubusercontent.com/66339390/125346157-c996bf80-e32f-11eb-8f6e-3e469d98282d.png)

A função "ht_pair" é responsável por alocar memória na própria entry, alocando memória para todos seus valores, setando o next e prev para null e por fim retornando a entry inicializada:

![htpair](https://user-images.githubusercontent.com/66339390/125349055-69098180-e333-11eb-8e17-9df099330124.png)

Indo para o método "ht_set", o mesmo começa fazendo o hash da key para saber em qual slot será colocado, quando já sabemos do slot, nós encontramos uma entry para aquele slot.

Vendo que todos os ponteiros inicializados são NULL. Começando então sendo null, é inserido um novo key e value (par) naquele slot. 

Mas se a entry não for null, ou já existe uma chave e devemos atualizar o valor, ou aconteceu uma colisão (duas chaves fazendo hash no mesmo slot). E isso é corrigido da seguinte maneira: é passado por cada uma das entries até que se chegue no fim, ou até que tenha achado uma chave correspondente onde então é atualizado o valor. Chegando ao fim da lista é adicionado uma nova entry

![htset](https://user-images.githubusercontent.com/66339390/125347240-0f07bc80-e331-11eb-8569-fe43bdccebbd.png)

Na função "ht_get" é procurado um valor através da chave. Onde é realizado uma hash da chave, e então é procurado um entry daquele slot criado, se a entry for null significa que a chave não foi encontrada, e se a entry não for null, é procurado as entries daquele slot em específico para ver se as key se igualam.

![htget](https://user-images.githubusercontent.com/66339390/125349621-25634780-e334-11eb-898e-d06eb4ea8eae.png)

Indo para outro método envolvendo a hashtable temos "htdumpquicksort" e "htdumpslotquicksort" (contendo poucas diferenças), que servirão para printar a hashtable inteira ou em um slot em específico respectivamente sem a ordenção e então aplicar o quicksort no final dela para então poder ser printada novamente de forma ordenada.
Além de identificar o head e o tail do slot da hashtable.

![htdump](https://user-images.githubusercontent.com/66339390/125350766-9e16d380-e335-11eb-8d53-a60ee351bb45.png)

Por fim da hash table é feito o método "destroy" e o "freeHashTable" que realizarão o free de toda a hash table conjuntamente com todas as entires que tiverem nela de forma recursiva:

![free](https://user-images.githubusercontent.com/66339390/125351033-f3eb7b80-e335-11eb-91c6-532e7ae0495d.png)

Concluindo há os métodos atrelados ao quicksort sendo eles "quicksort" e o "swap" responsáveis pela ordenação dos elementos encontrados em cada lista da hashtable.

O método do quicksort pegará de referência o head e o tail de um determinado slot da tabela hash e então começará o sort.

É criado variáveis temporárias necessárias para o funcionamento do mesmo "i = head->prev", "pivo = tail", "temp" e "j = head".

Passando então por toda a lista do head ao tail ele vai comparando os tamanhos das strings e se o valor encontrado for menor que o pivo é trocado com a variável i

![quicksort](https://user-images.githubusercontent.com/66339390/125352439-a4a64a80-e337-11eb-99f5-eaf132e8e11c.png)

No main haverá então a criação de um ponteiro file, responsável por conter os nomes, e então setar eles na tabela hash:

![main](https://user-images.githubusercontent.com/66339390/125353018-65c4c480-e338-11eb-92d2-eb4bb1583fa6.png)

# Referências

CS.UTAH. **Unsigned Integers.** Disponível em: <https://www.cs.utah.edu/~germain/PPS/Topics/unsigned_integer.html>. Acesso em: 3 jul. 2021.

GITHUB. **Hashchain.c.** Disponível em: <https://gist.github.com/chrispiccaro18/63cfce1337e71c9aac6012bf92607337>. Acesso em: 3 jul. 2021.

GITHUB. **Main_encadeada.c.** Disponível em: <https://github.com/MarlonVCendron/Trabalho-Sort-ED/blob/master/codigo/quicksort/main_encadeada.c>. Acesso em: 3 jul. 2021.

REPLIT. **ED - HASH - Exemplo.** Disponível em: <https://replit.com/@ManassesRibeiro/ED-HASH-Exemplo>. Acesso em: 9 jul. 2021.

YOUTUBE. **Data Structures: Hash Table implementation in C.** Disponível em: <https://www.youtube.com/watch?v=wg8hZxMRwcw>. Acesso em: 3 jul. 2021.

YOUTUBE. **Programar em C - Manipulação de Arquivos txt em C / Ler Dados - Aula 83.** Disponível em: <https://www.youtube.com/watch?v=USsUSMpNGsM>. Acesso em: 3 jul. 2021.
