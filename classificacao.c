#include "algoritmos.h"

int* geraVetorAleatorio2(int extent) {
    int* array = (int*)malloc(extent * sizeof(int)); 
    if (array == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return NULL;  
    }
    
    int *tempArray = (int*)malloc(extent * sizeof(int));
    
    if (tempArray == NULL){
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    
    FILE *file = fopen("classificacao.txt", "w");

    if (file == NULL) {
        printf("Erro na abertura de arquivo.\n");
        exit(1);
    }

    printf("Elementos gerados: ");
    for (int i = 0; i < extent; i++) {
        array[i] = rand() % 1000;
        tempArray[i] = array[i];
        fprintf(file, "%d\t", tempArray[i]);
        printf("%d ", array[i]);
    }
    fprintf(file, "\n");
    fclose(file);

    printf("\n");
    
    geraResultadosOrdenacao(array, extent);
    return array; 
}

void lerElementosDoArquivoOrdenacao2(const char *fp, int **array, int *extent) {
    FILE *file = fopen(fp, "r");
    if (file == NULL) {
        perror("Erro na abertura de arquivo");
        exit(EXIT_FAILURE);
    }

    int num;
    int size = 0;

    while (fscanf(file, "%d", &num) == 1) {
        size++;
    }

    *array = (int *)malloc(size * sizeof(int));
    if (*array == NULL) {
        perror("Erro ao alocar memória para o vetor");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &(*array)[i]);
    }

    *extent = size; 
    fclose(file);
}
void geraResultadosOrdenacao(int *array, int extent) {
   
    int *tempArray = (int *)malloc(extent * sizeof(int));

    clock_t inicio, fim;

    lerElementosDoArquivoOrdenacao2("classificacao.txt", &tempArray, &extent);


    inicio = clock();
    insertionSort(tempArray, extent);
    fim = clock();
    printf("Tempo de classificação para Insertion Sort com n=%d: %ld ticks de clock - Tempo tomado: %f segundos\n", extent, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    selectionSort(tempArray, extent);
    fim = clock();
    printf("Tempo de classificação para Selection Sort com n=%d: %ld ticks de clock - Tempo tomado: %f segundos\n", extent, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    bubbleSort(tempArray, extent);
    fim = clock();
    printf("Tempo de classificação para Bubble Sort com n=%d: %ld ticks de clock - Tempo tomado: %f segundos\n", extent, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    quickSort(tempArray, 0, extent - 1);
    fim = clock();
    printf("Tempo de classificação para Quick Sort com n=%d: %ld ticks de clock - Tempo tomado: %f segundos\n", extent, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    mergeSort(tempArray, 0, extent - 1);
    fim = clock();
    printf("Tempo de classificação para Merge Sort com n=%d: %ld ticks de clock - Tempo tomado: %f segundos\n", extent, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    
    free(tempArray);
    system("PAUSE");
}



/*Função de classificação por inserção */
void insertionSort(int *array, int extent) {
    int i, j, auxiliar;   /*Variáveis*/

    /*O indice i percorre todo o vetor*/
    for (i = 1; i < extent; i++) {
        auxiliar = array[i]; /*A variável auxiliar recebe o elemento armazenado na posição i*/
        j = i - 1;   /*O índice j é deslocado para a esquerda*/

        while ((j >= 0) && (auxiliar < array[j])) {  /*j é deslocado para a esquerda enquanto 
                                                    auxiliar for menor que o elemento armazenado em array[j] */
            array[j + 1] = array[j];  /*Os elementos da direita são ddeslocados para abir espaço para auxiliar*/
            j--;
        }

        array[j + 1] = auxiliar;  /*Auxiliar é, então, posicionada na posição certa*/
    }  /*O processo se repete para todos os elementos do array*/
}
/*Função de classificação por seleção*/
void selectionSort(int *array, int extent) {
    int i, j, menor, auxiliar;  /*Varia´veis*/
 
    for (i = 0; i < extent - 1; i++) {
        menor = i;  /*O índice i percorre todo o array
                    em busca do menor elemento e o coloca na primeira posição*/

        for (j = i + 1; j < extent; j++) {
            /*O índice j inicia em i + 1 e percorre todo o array,
            após encontrar um elemento menor que o armazenado na primeira
            realiza a troca*/
            if (array[j] < array[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            /*Se o elemento do índice i não for o menor,
            a variável auxiliar recebe este elemento, 
            e a sua posição é ocupada pelo menor encontrado, e
            então, o menor elemento se torna a variável auxiliar
            para efeitos de comparação.*/
            auxiliar = array[i];
            array[i] = array[menor];
            array[menor] = auxiliar;
        }
    }
}

/*Função de classificação por bolha*/
void bubbleSort(int *array, int extent) {
    int i, auxiliar, continua, fim = extent;  /*Variáveis e atribuição do tamanho do vetor ao fim dele;*/

    do {  
        /*A cada iteração pelo indíce i, o algoritm compara dois elementos adjacentes e em
        caso de desordem, realiza a troca de posição deles por meio da variável auxiliar*/
        for (i = 0; i < fim - 1; i++) {
            if (array[i] > array[i + 1]) {
                auxiliar = array[i];
                array[i] = array[i + 1];
                array[i + 1] = auxiliar;
                continua = i;  /*O processo continua até que seja finalizada a desordem*/
            }
        }
        fim--;  /*O fim que recebeu o tamanho do vetor é decrementado para quê o algoritmo compare até o fim*/
    } while (continua != 0);
}

/*Função para realizar a partição do vetor*/
int realizaParticao(int *array, int inicio, int fim) {
    int esquerda, direita, pivo, auxiliar; /*Variáveis*/
    esquerda = inicio;    
    direita = fim;
    pivo = array[inicio];   /*O elemento pivô é inicializado pelo início do vetor, enquanto que
                            esquerda e direita são inicializadas por inicio e fim, respectivamente*/

    while (esquerda < direita) {        /*Neste laço encadeado, os elementos menores que o pivô são
                                        inseridos à sua esquerda e os maiores à sua direita, enquanto
                                        o pivô é centralizado*/
        while (array[esquerda] <= pivo) {
            esquerda++;
        }
        while (array[direita] > pivo) {
            direita--;
        }
        if (esquerda < direita) {
            auxiliar = array[esquerda];
            array[esquerda] = array[direita];
            array[direita] = auxiliar;
        }
    }
    array[inicio] = array[direita];
    array[direita] = pivo;
    return direita;
}

void quickSort(int *array, int inicio, int fim) {
    int pivo;

    if (fim > inicio) {         /*A variável pivô é atribuída da chamada de função para realizar a partição do vetor*/
        pivo = realizaParticao(array, inicio, fim);
        quickSort(array, inicio, pivo - 1);     /*Ocorre chamada recursiva para ordenar os vetores divididos*/
        quickSort(array, pivo + 1, fim);        /*Até que o vetor esteja ordenado*/
    }
}

/*Função de realizar mescla*/
void realizaMescla(int *array, int inicio, int meio, int fim) {
    int *temporario, pont1, pont2, i, j, k, fim1 = 0, fim2 = 0;
    /*Definição de variáveis e de um vetor temporário para armazenar a mescla, além de dois indíces auxiliares (pont1 e pont2)*/

    int extent = fim - inicio + 1;
    pont1 = inicio;                 /*Inicialização de variáveis */
    pont2 = meio + 1;

    temporario = (int *)malloc(extent * sizeof(int));           /*Alocação dinâmica para este vetor temporário*/

    /*Enquanto a vetor temporário não é totalmente preenchido
    A função começa a mesclar os elementos das duas metades 
    ordenadas em ordem crescente. Ela compara os elementos em 
    array[pont1] e array[pont2] e seleciona o menor deles.
    O menor elemento é copiado para o array temporário temporario na posição i.*/

    if (temporario != NULL) {
        for (i = 0; i < extent; i++) {
            if (!fim1 && !fim2) {
                if (array[pont1] < array[pont2]) {
                    temporario[i] = array[pont1++];   
                } 
                else {
                    temporario[i] = array[pont2++];
                }

                if (pont1 > meio) {
                    fim1 = 1;
                }
                if (pont2 > fim) {
                    fim2 = 1;
                }
            } 
            else {                    /*As variáveis fim1 e fim2 são utilizadas para averiguar se uma das metades não chegou ao fim*/
                if (!fim1) {
                    temporario[i] = array[pont1++];
                } else {
                    temporario[i] = array[pont2++];
                }
            }
        }
        /*Após mesclagem completa, os elementos do vetor temporário são copiados para o vetor original*/
        for (j = 0, k = inicio; j < extent; j++, k++) {
            array[k] = temporario[j];
        }
    }
    free(temporario);           /*E então há liberação de memória*/
}

/*Função de classificação por mescla*/
void mergeSort(int *array, int inicio, int fim) {
    int meio;
    /*A função averigua se o início é menor que o fim e então divide o vetor em dois, de tal modo,
    chama-se recursivamente para classificar as duas metades do vetor, para então, chamar realizaMescla 
    e fazer a ordenação por mescla*/
    if (inicio < fim) {
        meio = floor((inicio + fim) / 2);
        mergeSort(array, inicio, meio);
        mergeSort(array, meio + 1, fim);
        realizaMescla(array, inicio, meio, fim);
    }
}
