#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <x86intrin.h>


int *geraVetorAleatorio1(int extent);
int* geraVetorAleatorio2(int extent);
void geraIteratividade();
void geraResultadoIterativo(int numero);
void geraRecursividade();
void geraResultadoRecursivo(int numero);

/*Protótipos de funções para busca*/
void recebeKeySearch(int *array, int extent, int keySearch);
void geraResultadosBusca(int *array, int extent, int keySearch);
int buscaLinear(int *array, int extent, int keySearch, int **posicoes, int *contadorPosicoes);
int buscaLinearComSentinela(int *array, int extent, int keySearch);
int buscaBinaria(int *array, int extent, int keySearch);

/*Protótipos de funções para classificação/ordenação*/
void geraResultadosOrdenacao(int *array, int extent);
void insertionSort(int *array, int extent);
void selectionSort(int *array, int extent);
void bubbleSort(int *array, int extent);
int realizaParticao(int *array, int inicio, int fim);
void quickSort(int *array, int inicio, int fim);
void realizaMescla(int *array, int inicio, int meio, int fim);
void mergeSort(int *array, int inicio, int fim);

/*Linguagem C tinha que não possuir polimorfismo*/

/*Protótipos de funções para iteratividade*/
int calculaNaturais(int numero);
int calculaFatorial(int numero);
int *calculaFibonacci(int numero);
void salvaDados1(int numero, int resultadoNaturais, int resultadoFatorial, int resultadoFibonacci);

/*Protótipos de funções para recursividade*/
int determinaNaturais(int numero);
int determinaFatorial(int numero);
int *determinaFibonacci(int numero);
void salvaDados2(int numero, int numeroNatural, int numeroFatorial, int *numerosFibonacci, int resultadoNaturais, int resultadoFatorial, int resultadoFibonacci);



#endif