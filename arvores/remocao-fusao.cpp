#include "arvore-struct.h"

// remoção por fusão
void remover(No &no) {
    No temp = no;
    if (no->esq == NULL){
        no = no->dir;
    }
    else if (no->dir == NULL){
        no = no->esq;
    }
    else{
        No temp_esq = no->esq;

        while (temp_esq->dir != NULL){
            temp_esq = temp_esq->dir;
        }
        temp_esq->dir = no->dir;
        no = no->esq;
    }
    delete temp;
}

void buscar_e_remover(No &raiz, Item n){
    No atual = raiz;
    if (atual == NULL)
    {
        cout << "A arvore esta vazia!";
        return;
    }
    
    No pai = NULL;
    while (atual != NULL){
        if (atual->item == n) break;

        pai = atual;
        if (n <= atual->item) atual = atual->esq;
        else atual = atual->dir;
    }
    
    if (atual != NULL && atual->item == n){
        if(atual == raiz){
            remover(raiz);
        }
        else if (pai->esq == atual){
            remover(pai->esq);
        }
        else remover(pai->dir);
    }
    else{
        cout << "O elemento nao esta na arvore!";
    }
}

int main(){
    No raiz = NULL;

    inserir(10, raiz);    
    inserir(5, raiz);
    inserir(20, raiz);
    inserir(4, raiz);
    inserir(6, raiz);
    inserir(15, raiz);
    inserir(30, raiz);

    percurso_em_ordem(raiz);
    cout << endl;
    buscar_e_remover(raiz, 10);
    cout << endl;
    percurso_em_ordem(raiz);

    return 0;
}