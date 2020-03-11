// Programa: programa para ordenação de um vetor

// Manipulação de tempo em c,c++
// Programa: programa que usa manipuladores de tempo para 
// medir o desempenho de algoritmos de ordenação

#include <iostream>
#include <cstdlib>   //qsort
#include <time.h>    // clock(),time()
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()

using namespace std;

//Vetores usados pelos métodos de ordenação
int *vetorQuickSort;
int *vetorBubbleSort;
int tamanho;

//Função usada pelo qsort para comparar dois numeros
int compare_ints( const void* a, const void* b ) {
	int* arg1 = (int*) a;
	int* arg2 = (int*) b;
	if( *arg1 < *arg2 ) return -1;
	else if( *arg1 == *arg2 ) return 0;
	else return 1;
}

//Algoritmos de ordenação bubble sort
void bubbleSort(int *vetor, int tamanho) {
	int aux;
	for (int i = 0; i < tamanho-1; i++) {
		for (int j = 0; j < tamanho-1; j++) {
			if (vetor[j] > vetor[j+1]) {
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
}


//Observe que os números são gerados aleatoriamente baseados
//em uma semente. Se for passado a mesma semente, os 
//números aleatórios serão os mesmos
void criarVetor(int tamanhoVetor, int semente){
	srand (semente);
	vetorQuickSort = new int[tamanhoVetor];
	vetorBubbleSort = new int[tamanhoVetor];
	for (int i=0;i<tamanhoVetor;i++){
		vetorQuickSort[i] =  rand()%100000;
        vetorBubbleSort[i] = vetorQuickSort[i]; // utilizar os mesmos valores
		//vetorBubbleSort[i] = rand()%100000;
	}
}

int main (){
    int n, seed;
    clock_t time_1, time_2;
    int saida;
    double saida2;

    cout << "Coloque um valor para n: " << '\n';
    cin >> n;
    cout << "Coloque um valor para a semente: " << '\n';
    cin >> seed;
	//Tamanho do vetor
	// int n = 10000;
	//Criar vetor com elementos aleatorios[0,100000] 
	criarVetor(n,seed);
	//Ordenar utilizando quickSort
    time_1 = clock();
	qsort (vetorQuickSort, n, sizeof(int), compare_ints);
    time_2 = clock();
    saida = (int) (time_2) - (time_1);
    saida2 = (double) ((saida) / (double) CLOCKS_PER_SEC);
    cout << "Tempo de uso de CPU em segundos (quicksort): " << saida2 << '\n';
	//Ordenar utilizando bubleSort
    time_1 = clock();
	bubbleSort(vetorBubbleSort,n);
    time_2 = clock();
    saida = (int) (time_2) - (time_1);
    saida2 = (double) ((saida) / (double) CLOCKS_PER_SEC);
    cout << "Tempo de uso de CPU em segundos (bubblesort): " << saida2 << '\n';
    // printf("terminou");
	exit(0);
}


