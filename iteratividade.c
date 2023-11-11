#include "algoritmos.h"


void geraIteratividade(){
    int numero;
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Bem-vindo(a) ao nosso programa para determinação de desempenho computacional para algoritmos iterativos.\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Digite um número inteiro:\n");
    scanf("%d", &numero);

    geraResultadoIterativo(numero);

}



int calculaNaturais(int numero){
    int soma = 0;
    for(int i = 1; i <= numero; i++){
        soma += i;
    }
    return soma;
}

int calculaFatorial(int numero){
    int fatorial = 1;
    for(int i = 1; i <= numero; i++){
        fatorial *= i;
    }
    return fatorial;
}

int *calculaFibonacci(int numero) {
    int *fibonacci = (int *)malloc(numero * sizeof(int));
    if (fibonacci == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    int auxiliar, fib0 = 0, fib1 = 1;
    fibonacci[0] = fib0;
    fibonacci[1] = fib1;
    for (int i = 2; i < numero; i++) {
        auxiliar = fib0 + fib1;
        fibonacci[i] = auxiliar;
        fib0 = fib1;
        fib1 = auxiliar;
    }
    return fibonacci;
}

void geraResultadoIterativo(int numero) {
    FILE *fp;
    fp = fopen("iteratividade.txt", "w");

    if (fp == NULL) {
        printf("Erro na abertura de arquivo.\n");
        exit(1);
    }
    
    clock_t inicio, fim;
    
    inicio = clock();
    int resultadoNaturais = calculaNaturais(numero);
    printf("Tempo de cálculo para números naturais com iteratividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));
    fim = clock();

    inicio = clock();
    int resultadoFatorial = calculaFatorial(numero);
    fim = clock();
    printf("Resultado Fatorial: %d\n", resultadoFatorial);
    printf("Tempo de cálculo para fatorial com iteratividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int *numerosFibonacci = calculaFibonacci(numero);
    int *resultadoFibonacci = calculaFibonacci(numero);
    fim = clock();
    printf("Resultado Fibonacci: %d\n", resultadoFibonacci[numero - 1]);
    printf("Tempo de cálculo para sequência de Fibonacci com iteratividade: %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));
       
    printf("Número: %d\n", numero);
    printf("Resultado Naturais: %d\n", resultadoNaturais);
    printf("Resultado Fatorial: %d\n", resultadoFatorial);
    printf("Resultado Fibonacci:\n");
    
    for (int i = 0; i < numero; i++) {
        printf("%d\n", numerosFibonacci[i]);
    }

    
    fprintf(fp, "Número: %d\n", numero);
    inicio = clock();
    resultadoNaturais = calculaNaturais(numero);
    fprintf(fp, "Tempo de cálculo para números naturais com iteratividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    resultadoFatorial = calculaFatorial(numero);
    fim = clock();
    fprintf(fp, "Tempo de cálculo para fatorial com iteratividade : %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    *resultadoFibonacci = calculaFibonacci(numero);
    fim = clock();
    fprintf(fp, "Tempo de cálculo para sequência de Fibonacci com iteratividade: %d ticks de clock - Tempo tomado: %f\n", (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    fclose(fp);
}