#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm> // swap
using namespace std;

// Max Heap
class Heap {
  private:
  vector<int> heap;

  int pai(int i) { return (i - 1) / 2; }
  int esq(int i) { return 2 * i + 1; }
  int dir(int i) { return 2 * i + 2; }

  public:
    // construtor que recebe um array e tranforma em um heap (build-heap)
  Heap(vector<int>& array) {
    this->heap = array;

    for (int i = array.size() / 2 - 1; i >= 0; i--) {     //Último nó interno sem ser folha = (n/2 - 1)
      heapify(i);
    }
  }

  void heapify(int i) {
    int maior = i;            // o indice fornecido é o 'maior'


    if (esq(i) < (int)this->heap.size() && heap[esq(i)] > heap[maior]) {
      maior = esq(i);
    }

    if (dir(i) < (int)this->heap.size() && heap[dir(i)] > heap[maior]) {
      maior = dir(i);
    }

    if (maior != i) {
      swap(heap[i], heap[maior]);
      heapify(maior);             //verifica se é mesmo o maior depois de trocar até estar no lugar certo
    }
  }

  void inserir(int valor) {
    heap.push_back(valor);
    int i = heap.size() - 1;

    // Sobe o elemento enquanto for maior que seu pai
    while (i > 0 && heap[pai(i)] < heap[i]) {
      swap(heap[i], heap[pai(i)]);
      i = pai(i);
    }
  }

  int remover_max() {
    if (heap.empty()) {
      cout << "Heap vazio!" << endl;
      return -1;
    }

    int maximo = heap[0];
    heap[0] = heap.back();  // move o último para a raiz
    heap.pop_back();
    heapify(0);             // restaura a propriedade
    return maximo;
  }

  void imprimir() {
    cout << "[ ";

    for (int x : heap) {
      cout << x << " ";
    }
    cout << "]\n";
  }
};

int main() {
  vector<int> dados = { 3, 9, 2, 1, 4, 5, 8, 7, 6 };

  Heap* heap = new Heap(dados);
  cout << ">> Build-Heap <<" << endl;
  cout << "Antes:  [ ";
  for (int n : dados) {
    cout << n << " ";
  }
  cout << "]" << endl;

  cout << "Depois: "; heap->imprimir();

  cout << "\n>> Insercao <<\n";
  heap->inserir(10);
  heap->imprimir();

  cout << "\n>>> Extrair Maximo <<<\n";
  for (int i = 0; i < 10; i++) {
    cout << "Max removido: " << heap->remover_max() << endl;
  }

  return 0;
}