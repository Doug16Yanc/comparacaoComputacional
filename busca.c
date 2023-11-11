#include "algoritmos.h"

int* geraVetorAleatorio1(int extent) {
    int keySearch = -1;
    int* array = (int*)malloc(extent * sizeof(int)); 
    if (array == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return NULL;  
    }

    printf("Elementos gerados: ");
    for (int i = 0; i < extent; i++) {
        array[i] = rand() % 1000;
        printf("%d ", array[i]);
    }
    printf("\n");    
    
    recebeKeySearch(array, extent, keySearch);    /*Chamada da função para receber a chave de busca*/

    return array; 


}

/*Função para receber a chave de busca*/
void recebeKeySearch(int *array, int extent, int keySearch){

    /*Caso o elemento esteja presente no vetor, a função de busca linear foi selecionada como a sentinela para mostrar,
    pois se um algoritmo já fizer o trabalho de busca do elemento e sua posição, não precisaremos dar trabalho aos outros*/
    
    int i, contadorPosicoes = 0, *posicoes = NULL;      /*Definimos o contador de posições (no caso de mais de uma) e um
                                                        ponteiro para essas posições.*/

    printf("Tudo ok! Agora o digite o elemento que desejas buscar:\n");
    scanf("%d", &keySearch);

    /*Chamadas das funções*/
    buscaLinear(array, extent, keySearch, &posicoes, &contadorPosicoes);
    buscaLinearComSentinela(array, extent, keySearch);
    buscaBinaria(array, extent, keySearch);
    
    if (contadorPosicoes > 0){              /*Aqui o caso das execuções condicionais para o encontro da chave de busca*/
        printf("Elemento encontrado na(s) posição(ões):");
        for (i = 0; i < contadorPosicoes; i++){     /*Caso haja duplicatas de um elemento*/
            printf("%d\t", posicoes[i]);
        }
        printf("\n");
    }
    else{
        printf("Elemento não encontrado.\n");
    }
    free(posicoes);         /*Liberação de memória alocada dinamicamente*/
    
    geraResultadosBusca(array, extent, keySearch);
}

void geraResultadosBusca(int *array, int extent, int keySearch) {
    FILE *file = fopen("busca.txt", "w+");

    if (file == NULL) {
        printf("Erro na abertura de arquivo.\n");
        exit(1);
    }

    clock_t inicio, fim;
    int i, contadorPosicoes = 0, *posicoes = NULL;

    fprintf(file, "Elementos gerados: ");
    for (i = 0; i < extent; i++) {
        fprintf(file, "%d\t ", array[i]);
    }
    fprintf(file, "\n");

    inicio = clock();
    int resultadoLinear = buscaLinear(array, extent, keySearch, &posicoes, &contadorPosicoes);
    fim = clock();
    fprintf(file, "Tempo de Busca Linear para n=%d: %d ticks de clock - Tempo tomado: %f\n", extent, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoSentinela = buscaLinearComSentinela(array, extent, keySearch);
    fim = clock();
    fprintf(file, "Tempo de Busca Linear com Sentinela para n=%d: %d ticks de clock - Tempo tomado: %f\n", extent, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoBinaria = buscaBinaria(array, extent, keySearch);
    fim = clock();
    fprintf(file, "Tempo de Busca Binária para n=%d: %d ticks de clock - Tempo tomado: %f\n", extent, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    if (contadorPosicoes > 0) {
        fprintf(file, "Elemento encontrado na(s) posição(ões):");
        for (i = 0; i < contadorPosicoes; i++) {
            fprintf(file, "%d\t", posicoes[i]);
        }
        fprintf(file, "\n");
    }
    else {
        fprintf(file, "Elemento não encontrado.\n");
    }

    free(posicoes);

    /*Fechar o arquivo*/
    fclose(file);
}


/*Função de busca sequencial linear simples*/
int buscaLinear(int *array, int extent, int keySearch, int **posicoes, int *contadorPosicoes) {
    /*Inicialização do contador de posições como ponteiro e alocação dinâmica para posições*/
    *contadorPosicoes = 0;
    *posicoes = (int *)malloc (extent * sizeof(int));
    
    if (*posicoes == NULL){
        printf("Erro na alocação de memória.\n");
    }
    for (int i = 0; i < extent; i++) {      /*Itera até o final do array e se encontrar a chave de busca, a posiciona no ponteiro posições*/
        if (array[i] == keySearch) {
            (*posicoes)[(*contadorPosicoes)++] = i;
        }
    }
    return -1;  /*Retorna tal valor independente da existência do elemento, haja vista que já sendo tratada sua existência 
                na função recebeKeySearch*/
    
}

/*Função de busca sequencial linear com valor sentinela*/
int buscaLinearComSentinela(int *array, int extent, int keySearch) {
    int lastElement = array[extent];        /*Coloca um valor sentinela no final do vetor*/
    array[extent] = keySearch; 
    int i = 0;
    while (array[i] != keySearch) {     /*Procura a chave de busca até encontrar*/
        i++;
    }
    if ((i < extent - 1) || (array[extent - 1] == keySearch)) {     /*Se o encontrar, talvez na última posição, retorna sua posição*/
        return i;  
    }
    return -1;      /*Elemento não encontrado*/
}

/*Função de busca binária*/
int buscaBinaria(int *array, int extent, int keySearch) {
    /*Presumindo que já haja ordenação*/
    int left = 0;
    int right = extent - 1;         /*O algoritmo divide o vetor ao meio e compara o elemento do meio com a chave de busca,
                                    em caso de a chave ser maior ou menor, o algoritmo continua a busca pela direita ou 
                                    esquerda, respectivamente.*/
    while (left <= right) {
        int half = left + (right - left) / 2;
        if (array[half] == keySearch) {
            return half;
        }
        if (array[half] < keySearch) {
            left = half + 1;
        } else {
            right = half - 1;
        }
    }
    return -1;      /*Elemento não encontrado*/
}
