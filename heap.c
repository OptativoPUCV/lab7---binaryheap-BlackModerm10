#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq) {
  if (pq->size == 0) {
    return NULL;
  }
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority) {
  if (pq->size == pq->capac) {
      pq->capac = pq->capac * 2 + 1;
      pq->heapArray = (heapElem*) realloc(pq->heapArray, pq->capac * sizeof(heapElem));
  }
  int i = pq->size;
  while(i > 0 && priority > pq->heapArray[(i - 1) / 2].priority) {
    pq->heapArray[i] = pq->heapArray[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  pq->heapArray[i].data = data;
  pq->heapArray[i].priority = priority;
  pq->size++;
}


void heap_pop(Heap* pq){
  if (pq->size == 0) {
    return;
  }
  pq->size--;
  pq->heapArray[0] = pq->heapArray[pq->size];
  int i = 0;
  while (1) {
    int hijoIzq = 2 * i + 1;
    int hijoDer = 2 * i + 2;
    int hijoMayor = i;

    if (hijoIzq < pq->size && pq->heapArray[hijoIzq].priority > pq->heapArray[hijoMayor].priority) {
      hijoMayor = hijoIzq;
  }
    if (hijoDer < pq->size && pq->heapArray[hijoDer].priority > pq->heapArray[hijoMayor].priority) {
      hijoMayor = hijoDer;

    }
    if (hijoMayor == i) {
      break;
    }
    heapElem aux = pq->heapArray[i];
    pq->heapArray[i] = pq->heapArray[hijoMayor];
    pq->heapArray[hijoMayor] = aux;
    i = hijoMayor;
  }
}
  
Heap* createHeap()
{
  Heap* pq = (Heap*) malloc(sizeof(Heap));
  if(!pq) {
    exit(1);
  }
  pq->capac = 3;
  pq->size = 0;
  pq->heapArray = (heapElem*) malloc(pq->capac * sizeof(heapElem));
  if(!pq->heapArray) {
    exit(1);
  }
  
  return pq;
}
