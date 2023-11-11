#include "algoritmos.h"

void geraRecursividade() {
    int numero;
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Bem-vindo(a) ao nosso programa para determinação de desempenho computacional para algoritmos recursivos.\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Digite um número inteiro:\n");
    scanf("%d", &numero);

    geraResultadoRecursivo(numero);
}

int determinaNaturais(int numero) {
    int soma = 0;
    if (numero == 1) {
        soma = 1;
    } else {
        soma = numero + determinaNaturais(numero - 1);
    }
    return soma;
}

int determinaFatorial(int numero) {
    int fatorial = 1;
    if (numero == 0 || numero == 1) {
        fatorial = 1;
    } else {
        fatorial = numero * determinaFatorial(numero - 1);
    }
    return fatorial;
}

int *determinaFibonacci(int numero) {
    int *fibonacci = (int *)malloc(numero * sizeof(int));
    if (fibonacci == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    if (numero <= 0) {
        return NULL;
    }

    for (int i = 0; i < numero; i++) {
        if (i <= 1) {
            fibonacci[i] = i;
        } else {
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }
    }

    return fibonacci;
}

void geraResultadoRecursivo(int numero) {
    FILE *fp;
    fp = fopen("recursividade.txt", "w+");

    if (fp == NULL) {
        printf("Erro na abertura de arquivo.\n");
        exit(1);
    }
    
    
    fprintf(fp, "Número: %d\n", numero);

    clock_t inicio, fim;

    inicio = clock();
    int resultadoNaturais = determinaNaturais(numero);
    fim = clock();
    printf("Tempo de cálculo para números naturais com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoFatorial = determinaFatorial(numero);
    fim = clock();
    printf("Tempo de cálculo para fatorial com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int *numerosFibonacci = determinaFibonacci(numero);
    int resultadoFibonacci = numerosFibonacci[numero - 1];
    fim = clock();
    printf("Tempo de cálculo para sequência de Fibonacci com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));
    printf("Resultado Naturais: %d\n", resultadoNaturais);
    printf("Resultado Fatorial: %d\n", resultadoFatorial);
    printf("Resultado Fibonacci:\n");
    
    for (int i = 0; i < numero; i++) {
        printf("%d\n", numerosFibonacci[i]);
    }
    printf("\n");
    
    fprintf(fp, "Resultado Naturais: %d\n", resultadoNaturais);
    fprintf(fp, "Resultado Fatorial: %d\n", resultadoFatorial);
    fprintf(fp, "Resultado Fibonacci:\n");
    for (int i = 0; i < numero; i++) {
        fprintf(fp, "%d\n", numerosFibonacci[i]);
    }

    inicio = clock();
    fim = clock();
    fprintf(fp, "Tempo de cálculo para números naturais com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    fim = clock();
    fprintf(fp, "Tempo de cálculo para fatorial com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    fim = clock();
    fprintf(fp, "Tempo de cálculo para sequência de Fibonacci com recursividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    fclose(fp);
}
