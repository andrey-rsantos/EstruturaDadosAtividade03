#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 5
typedef struct {
    int dados[TAMANHO];
    int topo;
} Pilha;
bool isEmpty(Pilha *p){
	return p->topo == -1;
}
void inicializar(Pilha *p){
    p->topo = -1;
}
void push(Pilha *p, int dado){
	if(p->topo == TAMANHO - 1){
		printf("Pilha Cheia!");
		return;
	}
	p->topo++;
	p->dados[p->topo] = dado;
}
int imprime_pilha(Pilha *p){
	if(isEmpty(p)){
		printf("Pilha Vazia");
		return 0;
	}
	int i;
	for(i = 0; i <= p->topo; i++){
		printf("%d -> ", p->dados[i]);
	}
	printf("topo");
	return 1;
}
int pop(Pilha *p){
	if(isEmpty(p)){
		printf("Pilha Vazia!");
		return -1;
	}
	int temp = p->dados[p->topo];
	p->topo--;
	return temp;
}
void topo(Pilha *p){
	if(isEmpty(p)){
		printf("Pilha Vazia!");
		return;
	}
	printf("\n\nTopo => %d", p->dados[p->topo]);
}

void imprime_vetor(int vetor[], int tamanho) {
    printf("[");
    for(int i = 0; i < tamanho; i++) {
        printf("%d", vetor[i]);
        if(i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void inverter_vetor(int vetor[], int tamanho) {
    Pilha pilha_auxiliar;
    inicializar(&pilha_auxiliar);

    printf("Vetor original: ");
    imprime_vetor(vetor, tamanho);
    printf("\n");

    for(int i = 0; i < tamanho; i++) {
        push(&pilha_auxiliar, vetor[i]);
        printf("Empilhando elemento %d\n", vetor[i]);
    }

    printf("\nDesempilhando elementos para inverter o vetor:\n");
    for(int i = 0; i < tamanho; i++) {
        int elemento = pop(&pilha_auxiliar);
        if(elemento != -1) {
            vetor[i] = elemento;
            printf("Desempilhando elemento %d para posicao %d\n", elemento, i);
        }
    }

    printf("\nVetor invertido: ");
    imprime_vetor(vetor, tamanho);
    printf("\n");
}

main(){
    Pilha p1,p2;
    inicializar(&p1);
    inicializar(&p2);
    push(&p2, 10);
    push(&p2, 20);
    push(&p2, 30);
    push(&p1, 15);
    push(&p1, 25);
    push(&p1, 35);
    topo(&p2);

    printf("\n\n=== DEMONSTRACAO: INVERTER VETOR USANDO PILHA ===\n");

    int vetor1[] = {1, 2, 3, 4, 5};
    int tamanho1 = 5;

    printf("\nExemplo 1:\n");
    inverter_vetor(vetor1, tamanho1);

    int vetor2[] = {10, 20, 30, 40, 50};
    int tamanho2 = 5;

    printf("\nExemplo 2:\n");
    inverter_vetor(vetor2, tamanho2);

    int vetor3[] = {100, 200, 300};
    int tamanho3 = 3;

    printf("\nExemplo 3:\n");
    inverter_vetor(vetor3, tamanho3);
}
