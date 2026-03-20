#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;

typedef int Item;

typedef struct no {
    struct no *esq;
    Item item;
    struct no *dir;
} *No;

No criarNo(No esquerda, Item item, No direita) {
    No novo = (struct no*)malloc(sizeof(struct no));
    novo->esq = esquerda;
    novo->item = item;
    novo->dir = direita;

    return novo;
}

void inserir(Item valor, No &raiz){
    if(raiz == NULL){
        raiz = criarNo(NULL, valor, NULL);;
    }
    else if(valor <= raiz->item){
        if(raiz->esq == NULL){
            raiz->esq = criarNo(NULL, valor, NULL);
        }
        else{
            inserir(valor, raiz->esq);
        }
    }
    else{
        if(raiz->dir == NULL){
            raiz->dir = criarNo(NULL, valor, NULL);
        }
        else{
        inserir(valor, raiz->dir);
        }
    }
}

void percurso_em_ordem(No no) {
    if (no == NULL){
        return;
    }
    percurso_em_ordem(no->esq);
    cout << no->item << " ";
    percurso_em_ordem(no->dir);
}

void percurso_pre_ordem(No no){
    if(no == NULL){
        return;
    }
    cout << no->item << " ";
    percurso_pre_ordem(no->esq);
    percurso_pre_ordem(no->dir);
}

void percurso_pos_ordem(No no){
    if(no == NULL){
        return;
    }
    percurso_pos_ordem(no->esq);
    percurso_pos_ordem(no->dir);
    cout << no->item << " ";
}

void percurso_em_largura(No no){
    if(no == NULL){
        return;
    }
    queue<No> fila;
    fila.push(no);

    while (!fila.empty()){
        No no_atual = fila.front();
        cout << no_atual->item << " ";
        fila.pop();

        if(no_atual->esq != NULL){
            fila.push(no_atual->esq);
        }
        if(no_atual->dir != NULL){
            fila.push(no_atual->dir);
        }
    }
}