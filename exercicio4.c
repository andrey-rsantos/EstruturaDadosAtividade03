#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 10
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

void imprime_pilha_formatada(Pilha *p, char *nome) {
    printf("%s: ", nome);
    if(isEmpty(p)) {
        printf("Vazia\n");
        return;
    }
    printf("[");
    for(int i = 0; i <= p->topo; i++) {
        printf("%d", p->dados[i]);
        if(i < p->topo) printf(", ");
    }
    printf("] (base -> topo)\n");
}

void remover_pares(Pilha *pilha_original) {
    Pilha pilha_auxiliar;
    inicializar(&pilha_auxiliar);

    printf("\n=== REMOVENDO ELEMENTOS PARES ===\n");

    printf("Pilha original: ");
    imprime_pilha_formatada(pilha_original, "");

    printf("\nEtapa 1: Desempilhando elementos e filtrando pares...\n");

    while(!isEmpty(pilha_original)) {
        int elemento = pop(pilha_original);
        printf("Elemento desempilhado: %d ", elemento);

        if(elemento % 2 == 0) {
            printf("(PAR - removido)\n");
        } else {
            printf("(IMPAR - mantido)\n");
            push(&pilha_auxiliar, elemento);
        }
    }

    printf("\nPilha auxiliar apos filtragem: ");
    imprime_pilha_formatada(&pilha_auxiliar, "");

    printf("\nEtapa 2: Restaurando ordem original dos impares...\n");

    while(!isEmpty(&pilha_auxiliar)) {
        int elemento = pop(&pilha_auxiliar);
        printf("Reempilhando: %d\n", elemento);
        push(pilha_original, elemento);
    }

    printf("\nResultado final: ");
    imprime_pilha_formatada(pilha_original, "");
    printf("=== PROCESSO CONCLUIDO ===\n");
}

void demonstrar_remocao_pares() {
    printf("\n=== DEMONSTRACAO: REMOVER PARES ===\n");

    Pilha exemplo1;
    inicializar(&exemplo1);

    int valores1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int tamanho1 = 8;

    printf("\nExemplo 1: Pilha com numeros consecutivos\n");
    printf("Empilhando valores: ");
    for(int i = 0; i < tamanho1; i++) {
        push(&exemplo1, valores1[i]);
        printf("%d ", valores1[i]);
    }
    printf("\n");

    remover_pares(&exemplo1);

    Pilha exemplo2;
    inicializar(&exemplo2);

    int valores2[] = {10, 15, 20, 25, 30};
    int tamanho2 = 5;

    printf("\n\nExemplo 2: Pilha mista\n");
    printf("Empilhando valores: ");
    for(int i = 0; i < tamanho2; i++) {
        push(&exemplo2, valores2[i]);
        printf("%d ", valores2[i]);
    }
    printf("\n");

    remover_pares(&exemplo2);

    Pilha exemplo3;
    inicializar(&exemplo3);

    int valores3[] = {2, 4, 6, 8};
    int tamanho3 = 4;

    printf("\n\nExemplo 3: Pilha apenas com pares\n");
    printf("Empilhando valores: ");
    for(int i = 0; i < tamanho3; i++) {
        push(&exemplo3, valores3[i]);
        printf("%d ", valores3[i]);
    }
    printf("\n");

    remover_pares(&exemplo3);

    Pilha exemplo4;
    inicializar(&exemplo4);

    int valores4[] = {1, 3, 5, 7, 9};
    int tamanho4 = 5;

    printf("\n\nExemplo 4: Pilha apenas com impares\n");
    printf("Empilhando valores: ");
    for(int i = 0; i < tamanho4; i++) {
        push(&exemplo4, valores4[i]);
        printf("%d ", valores4[i]);
    }
    printf("\n");

    remover_pares(&exemplo4);
}

void menu_interativo() {
    Pilha pilha_usuario;
    inicializar(&pilha_usuario);

    int opcao, valor;

    do {
        printf("\n=== MENU REMOVER PARES ===\n");
        printf("1. Adicionar elemento na pilha\n");
        printf("2. Remover elemento da pilha\n");
        printf("3. Exibir pilha\n");
        printf("4. Remover todos os pares\n");
        printf("5. Limpar pilha\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o valor a adicionar: ");
                scanf("%d", &valor);
                push(&pilha_usuario, valor);
                printf("Valor %d adicionado!\n", valor);
                break;

            case 2:
                if(!isEmpty(&pilha_usuario)) {
                    valor = pop(&pilha_usuario);
                    printf("Valor %d removido!\n", valor);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;

            case 3:
                printf("Estado atual da ");
                imprime_pilha_formatada(&pilha_usuario, "pilha");
                break;

            case 4:
                if(!isEmpty(&pilha_usuario)) {
                    remover_pares(&pilha_usuario);
                } else {
                    printf("Pilha vazia! Adicione elementos primeiro.\n");
                }
                break;

            case 5:
                inicializar(&pilha_usuario);
                printf("Pilha limpa!\n");
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
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

    demonstrar_remocao_pares();

    menu_interativo();
}
