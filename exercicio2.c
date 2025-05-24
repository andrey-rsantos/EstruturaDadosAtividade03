#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO 100

typedef struct {
    int dados[TAMANHO];
    int topo;
} Pilha;

typedef struct {
    char dados[TAMANHO];
    int topo;
} PilhaChar;

bool isEmpty(Pilha *p){
	return p->topo == -1;
}

bool isEmptyChar(PilhaChar *p){
	return p->topo == -1;
}

void inicializar(Pilha *p){
    p->topo = -1;
}

void inicializarChar(PilhaChar *p){
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

void pushChar(PilhaChar *p, char dado){
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

char popChar(PilhaChar *p){
	if(isEmptyChar(p)){
		printf("Pilha Vazia!");
		return '\0';
	}
	char temp = p->dados[p->topo];
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

void limpar_string(char *origem, char *destino) {
    int j = 0;
    for(int i = 0; origem[i] != '\0'; i++) {
        if(isalpha(origem[i])) {
            destino[j] = tolower(origem[i]);
            j++;
        }
    }
    destino[j] = '\0';
}

bool verificar_palindromo(char *palavra) {
    PilhaChar pilha;
    inicializarChar(&pilha);

    char palavra_limpa[TAMANHO];
    limpar_string(palavra, palavra_limpa);

    int tamanho = strlen(palavra_limpa);

    printf("Palavra processada: '%s'\n", palavra_limpa);
    printf("Empilhando caracteres...\n");

    for(int i = 0; i < tamanho; i++) {
        pushChar(&pilha, palavra_limpa[i]);
        printf("Empilhando: '%c'\n", palavra_limpa[i]);
    }

    printf("\nDesempilhando e comparando...\n");

    for(int i = 0; i < tamanho; i++) {
        char char_desempilhado = popChar(&pilha);
        printf("Comparando posicao %d: '%c' com '%c' desempilhado\n",
               i, palavra_limpa[i], char_desempilhado);

        if(palavra_limpa[i] != char_desempilhado) {
            printf("Caracteres diferentes encontrados!\n");
            return false;
        }
    }

    return true;
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

    printf("\n\n=== VERIFICADOR DE PALINDROMO USANDO PILHA ===\n");

    char palavra[TAMANHO];

    printf("\nDigite uma palavra para verificar se e palindromo: ");
    fgets(palavra, sizeof(palavra), stdin);

    palavra[strcspn(palavra, "\n")] = '\0';

    printf("\n--- Verificando: '%s' ---\n", palavra);

    if(verificar_palindromo(palavra)) {
        printf("\n*** A palavra '%s' E um palindromo! ***\n", palavra);
    } else {
        printf("\n*** A palavra '%s' NAO e um palindromo! ***\n", palavra);
    }

    printf("\n=== Exemplos automaticos ===\n");

    char *exemplos[] = {"arara", "ovo", "ana", "osso", "casa", "radar", "A man a plan a canal Panama"};
    int num_exemplos = 7;

    for(int i = 0; i < num_exemplos; i++) {
        printf("\n--- Testando: '%s' ---\n", exemplos[i]);
        if(verificar_palindromo(exemplos[i])) {
            printf("*** '%s' E um palindromo! ***\n", exemplos[i]);
        } else {
            printf("*** '%s' NAO e um palindromo! ***\n", exemplos[i]);
        }
    }
}
