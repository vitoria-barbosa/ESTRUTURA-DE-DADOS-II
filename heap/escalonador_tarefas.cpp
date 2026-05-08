#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

class Processo {
  public:
  string nome;
  int prioridade;    // 0 = mais urgente, 9 = menos urgente
  int burst_total;
  int burst_restante;
  int tempo_chegada;
  int tempo_espera;

  Processo(string nome, int prio, int burst, int chegada) {
    this->nome = nome;
    this->prioridade = prio;
    this->burst_total = burst;
    this->burst_restante = burst;
    this->tempo_chegada = chegada;
    this->tempo_espera = 0;
  }
};


class MinHeapPrioridade {
  public:
  vector<Processo> heap;

  int pai(int i) { return (i - 1) / 2; }
  int esq(int i) { return 2 * i + 1; }
  int dir(int i) { return 2 * i + 2; }

  // Menor número = maior urgência; desempate por chegada (FIFO)
  bool mais_urgente(Processo a, Processo b) {
    if (a.prioridade != b.prioridade) {
      return a.prioridade < b.prioridade;
    }
    return a.tempo_chegada < b.tempo_chegada;
  }

  void subir(int i) {
    while (i > 0 && mais_urgente(heap[i], heap[pai(i)])) {
      swap(heap[i], heap[pai(i)]);
      i = pai(i);
    }
  }

  void descer(int i) {
    int n = heap.size();
    int melhor = i;

    if (esq(i) < n && mais_urgente(heap[esq(i)], heap[melhor])) {
      melhor = esq(i);
    }
    if (dir(i) < n && mais_urgente(heap[dir(i)], heap[melhor])) {
      melhor = dir(i);
    }

    if (melhor != i) {
      swap(heap[i], heap[melhor]);
      descer(melhor);
    }
  }

  void inserir(Processo p) {
    heap.push_back(p);
    subir(heap.size() - 1);
  }

  Processo remover() {
    Processo topo = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
      descer(0);
    }
    return topo;
  }

  // Reconstrói o heap após modificar prioridades externamente — O(n)
  void rebuild() {
    for (int i = heap.size() / 2 - 1; i >= 0; i--)
      descer(i);
  }
};

class EscalonadorPrioridade {
  MinHeapPrioridade fila;
  int tempo = 0;
  int quantum = 2;       // fatia de CPU por rodada
  int limiteAging = 5;   // ciclos de espera antes de promover

  // Aging: Percorre todos os processos na fila e eleva a urgência
  // dos que esperam há muito tempo, evitando starvation.
  void aplicar_aging() {
    for (Processo& p : fila.heap) {
      p.tempo_espera++;
      if (p.tempo_espera >= limiteAging && p.prioridade > 0) {
        cout << "\n[AGING] " << p.nome
          << ": prioridade " << p.prioridade
          << " -> " << p.prioridade - 1 << "\n\n";
        p.prioridade--;
        p.tempo_espera = 0;
      }
    }
    fila.rebuild();   // reordena após mudanças de prioridade
  }

  void executando_msg(Processo p, int exec) {
    cout << "[t=" << setw(2) << left << tempo << "] "
      << "processo=" << setw(8) << left << p.nome
      << "| prio=" << p.prioridade
      << " | exec=" << exec << "u"
      << " | restante=" << p.burst_restante - exec << "u"
      << " | burst total=" << p.burst_total
      << " [EXECUTANDO]\n";
  }

  void terminou_msg(Processo p) {
    cout << "\nprocesso " << p.nome
      << " finalizado em t = " << tempo
      << " (tempo vida = " << tempo - p.tempo_chegada << "u)"
      << " [FINALIZADO]\n\n";
  }

  public:
  void inserir(Processo p) {
    fila.inserir(p);
    cout << "[t= " << setw(2) << left << tempo << "] + "
      << setw(8) << left << p.nome
      << "prio=" << p.prioridade << " [PRONTO]\n";
  }

  void executar() {
    cout << "\n======== MAX-HEAP (PRIORIDADE + AGING) ========\n\n";;

    while (!fila.heap.empty()) {
      aplicar_aging();

      Processo atual = fila.remover();

      int exec = min(quantum, atual.burst_restante);
      executando_msg(atual, exec);

      tempo += exec;
      atual.burst_restante -= exec;

      if (atual.burst_restante > 0) {
        atual.tempo_espera = 0;
        fila.inserir(atual);
      }
      else {
        terminou_msg(atual);
      }
    }
  }
};

int main() {
  EscalonadorPrioridade escalonador;

  Processo p1 = Processo("init", 0, 4, 0);
  Processo p2 = Processo("bash", 3, 6, 0);
  Processo p3 = Processo("firefox", 5, 8, 0);
  Processo p4 = Processo("vim", 2, 3, 0);
  Processo p5 = Processo("gcc", 4, 7, 0);

  cout << "\n> Adicionando processos..." << endl;
  escalonador.inserir(p1);
  escalonador.inserir(p2);
  escalonador.inserir(p3);
  escalonador.inserir(p4);
  escalonador.inserir(p5);

  escalonador.executar();
  return 0;
}