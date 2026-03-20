#include <../arvores/arvore-struct.h>

int qtd_nos(No raiz){
    if(raiz == NULL){
        return 0;
    }
    int contador = 0;
    queue<No> fila;
    fila.push(raiz);

    while (!fila.empty()){
        No no_atual = fila.front();
        contador += 1;
        fila.pop();

        if(no_atual->esq != NULL){
            fila.push(no_atual->esq);
        }
        if(no_atual->dir != NULL){
            fila.push(no_atual->dir);
        }
    }
    return contador;
}

int altura(No raiz) {
    if (raiz == NULL) {
        return 0; 
    }

    int alt_esq = altura(raiz->esq);
    int alt_dir = altura(raiz->dir);

    if (alt_esq > alt_dir)
        return alt_esq + 1;
    else
        return alt_dir + 1;
}

// Indice - no vetor heap binário
bool arvore_eh_completa(No raiz, int indice, int qtd_nos) {
    if (raiz == NULL)
        return true;

    if (indice >= qtd_nos)
        return false;

    return arvore_eh_completa(raiz->esq, 2 * indice + 1, qtd_nos) &&
           arvore_eh_completa(raiz->dir, 2 * indice + 2, qtd_nos);
}

bool arvore_eh_cheia(No raiz){

    if(raiz == NULL)
        return true;

    if(raiz->esq == NULL && raiz->dir == NULL)
        return true;

    if(raiz->esq != NULL && raiz->dir != NULL)
        return arvore_eh_cheia(raiz->esq) && arvore_eh_cheia(raiz->dir);

    return false;
}

int main() {
    No raiz = NULL;

    inserir(50, raiz);    
    inserir(30, raiz);
    inserir(40, raiz);
    inserir(10, raiz);
    inserir(20, raiz);
    inserir(60, raiz);
    inserir(70, raiz);
    inserir(5, raiz);
    inserir(35, raiz);
    inserir(45, raiz);
    inserir(55, raiz);

    cout << "Quantidade de nos na arvore: " << qtd_nos(raiz) << endl;
    cout << "Altura da arvore: " << altura(raiz) << endl;

    if (arvore_eh_completa(raiz, 0, qtd_nos(raiz)))
        cout << "A arvore e completa";
    else
        cout << "A arvore NAO e completa";

    cout << endl;

    if(arvore_eh_cheia(raiz))
        cout << "A arvore e cheia";
    else
        cout << "A arvore NAO e cheia";
}