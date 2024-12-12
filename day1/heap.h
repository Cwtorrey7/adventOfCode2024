#ifndef MY_HEAP_H
#define MY_HEAP_H

typedef unsigned char flag;

typedef struct Heap
{
	int* array;
	int size;
	int capacity;
	flag isMaxHeap;
} Heap;

Heap *initHeap(int capacity, flag isMaxHeap);
void swap(int *a, int *b);
void heapify(Heap *heap, int index);
void heapInsert(Heap *heap, int value);
int extractHead(Heap *heap);
void deleteKey(Heap *heap, int index);
void printHeap(Heap *heap);
void heapFree(Heap *heap);

#endif
