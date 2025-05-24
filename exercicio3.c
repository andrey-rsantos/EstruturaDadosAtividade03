#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TAMANHO 10
#define MAX_TEXTO 100

typedef struct {
    int dados[TAMANHO];
    int topo;
} Pilha;

typedef struct {
    char texto[MAX_TEXTO];
    char operacao[20];
} Acao;

typedef struct {
    Acao dados[TAMANHO];
    int topo;
} PilhaAcao;

bool isEmpty(Pilha *p){
	return p->topo == -1;
}

bool isEmptyAcao(PilhaAcao *p){
	return p->topo == -1;
}

void inicializar(Pilha *p){
    p->topo = -1;
}

void inicializarAcao(PilhaAcao *p){
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

void pushAcao(PilhaAcao *p, char *texto, char *operacao){
	if(p->topo == TAMANHO - 1){
		printf("Pilha de acoes cheia!");
		return;
	}
	p->topo++;
	strcpy(p->dados[p->topo].texto, texto);
	strcpy(p->dados[p->topo].operacao, operacao);
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

Acao popAcao(PilhaAcao *p){
	Acao vazia = {"", ""};
	if(isEmptyAcao(p)){
		printf("Pilha de acoes vazia!");
		return vazia;
	}
	Acao temp = p->dados[p->topo];
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

typedef struct {
    char conteudo[MAX_TEXTO];
    PilhaAcao pilha_undo;
    PilhaAcao pilha_redo;
} EditorTexto;

void inicializar_editor(EditorTexto *editor) {
    strcpy(editor->conteudo, "");
    inicializarAcao(&editor->pilha_undo);
    inicializarAcao(&editor->pilha_redo);
    printf("Editor de texto inicializado!\n");
}

void exibir_estado(EditorTexto *editor) {
    printf("\n=== ESTADO ATUAL ===\n");
    printf("Texto: \"%s\"\n", editor->conteudo);
    printf("Undo disponivel: %s\n", isEmptyAcao(&editor->pilha_undo) ? "Nao" : "Sim");
    printf("Redo disponivel: %s\n", isEmptyAcao(&editor->pilha_redo) ? "Nao" : "Sim");
    printf("===================\n");
}

void adicionar_texto(EditorTexto *editor, char *novo_texto) {
    char estado_anterior[MAX_TEXTO];
    strcpy(estado_anterior, editor->conteudo);

    strcat(editor->conteudo, novo_texto);

    pushAcao(&editor->pilha_undo, estado_anterior, "adicionar");

    inicializarAcao(&editor->pilha_redo);

    printf("Texto adicionado: \"%s\"\n", novo_texto);
    printf("Novo conteudo: \"%s\"\n", editor->conteudo);
}

void remover_ultimos_chars(EditorTexto *editor, int quantidade) {
    char estado_anterior[MAX_TEXTO];
    strcpy(estado_anterior, editor->conteudo);

    int tamanho = strlen(editor->conteudo);
    if(quantidade > tamanho) quantidade = tamanho;

    editor->conteudo[tamanho - quantidade] = '\0';

    pushAcao(&editor->pilha_undo, estado_anterior, "remover");

    inicializarAcao(&editor->pilha_redo);

    printf("Removidos %d caracteres\n", quantidade);
    printf("Novo conteudo: \"%s\"\n", editor->conteudo);
}

void undo(EditorTexto *editor) {
    if(isEmptyAcao(&editor->pilha_undo)) {
        printf("Nada para desfazer!\n");
        return;
    }

    char estado_atual[MAX_TEXTO];
    strcpy(estado_atual, editor->conteudo);

    Acao acao = popAcao(&editor->pilha_undo);

    pushAcao(&editor->pilha_redo, estado_atual, "undo");

    strcpy(editor->conteudo, acao.texto);

    printf("UNDO executado - operacao '%s' desfeita\n", acao.operacao);
    printf("Conteudo restaurado: \"%s\"\n", editor->conteudo);
}

void redo(EditorTexto *editor) {
    if(isEmptyAcao(&editor->pilha_redo)) {
        printf("Nada para refazer!\n");
        return;
    }

    char estado_atual[MAX_TEXTO];
    strcpy(estado_atual, editor->conteudo);

    Acao acao = popAcao(&editor->pilha_redo);

    pushAcao(&editor->pilha_undo, estado_atual, "redo");

    strcpy(editor->conteudo, acao.texto);

    printf("REDO executado\n");
    printf("Conteudo restaurado: \"%s\"\n", editor->conteudo);
}

void demonstrar_sistema() {
    EditorTexto editor;
    inicializar_editor(&editor);

    printf("\n=== DEMONSTRACAO DO SISTEMA UNDO/REDO ===\n");

    exibir_estado(&editor);

    printf("\n1. Adicionando 'Ola '...\n");
    adicionar_texto(&editor, "Ola ");
    exibir_estado(&editor);

    printf("\n2. Adicionando 'mundo'...\n");
    adicionar_texto(&editor, "mundo");
    exibir_estado(&editor);

    printf("\n3. Adicionando '!'...\n");
    adicionar_texto(&editor, "!");
    exibir_estado(&editor);

    printf("\n4. Executando UNDO...\n");
    undo(&editor);
    exibir_estado(&editor);

    printf("\n5. Executando UNDO novamente...\n");
    undo(&editor);
    exibir_estado(&editor);

    printf("\n6. Executando REDO...\n");
    redo(&editor);
    exibir_estado(&editor);

    printf("\n7. Adicionando ' lindo'...\n");
    adicionar_texto(&editor, " lindo");
    exibir_estado(&editor);

    printf("\n8. Tentando REDO (deve falhar - pilha redo foi limpa)...\n");
    redo(&editor);
    exibir_estado(&editor);

    printf("\n9. Removendo 6 caracteres...\n");
    remover_ultimos_chars(&editor, 6);
    exibir_estado(&editor);

    printf("\n10. Executando UNDO...\n");
    undo(&editor);
    exibir_estado(&editor);
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

    demonstrar_sistema();

    printf("\n\n=== MENU INTERATIVO ===\n");
    EditorTexto editor_interativo;
    inicializar_editor(&editor_interativo);

    int opcao;
    char texto[MAX_TEXTO];
    int quantidade;

    do {
        printf("\n--- EDITOR COM UNDO/REDO ---\n");
        printf("1. Adicionar texto\n");
        printf("2. Remover caracteres\n");
        printf("3. Undo\n");
        printf("4. Redo\n");
        printf("5. Exibir estado\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Digite o texto a adicionar: ");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0';
                adicionar_texto(&editor_interativo, texto);
                break;

            case 2:
                printf("Quantos caracteres remover: ");
                scanf("%d", &quantidade);
                remover_ultimos_chars(&editor_interativo, quantidade);
                break;

            case 3:
                undo(&editor_interativo);
                break;

            case 4:
                redo(&editor_interativo);
                break;

            case 5:
                exibir_estado(&editor_interativo);
                break;

            case 0:
                printf("Encerrando editor...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}
