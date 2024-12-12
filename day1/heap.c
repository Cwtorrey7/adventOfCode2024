/*
 * Program Name: Heap
 * Author: Chris Torrey
 * Last Edited Date: 12/12/2024
 * Program Description: 
 */

/*** Included Libraries ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"

/*** Macro Definitions ***/
/*
typedef unsigned char flag;

typedef struct Heap
{
	int* array;
	int size;
	int capacity;
	flag isMaxHeap;
} Heap;
*/
/*** Helper Functions ***/

Heap *initHeap(int capacity, flag isMaxHeap)
{
	Heap *heap = (Heap*) malloc(sizeof(Heap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->array = (int*) malloc(capacity * sizeof(int));
	heap->isMaxHeap = isMaxHeap;
	return heap;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(Heap *heap, int index)
{
	int left = (2 * index) + 1;
	int right = (2 * index) + 2;

	if (heap->isMaxHeap)
	{
		int largest = index;

		if (left < heap->size && heap->array[left] > heap->array[largest])
			largest = left;

		if (right < heap->size && heap->array[right] > heap->array[largest])
			largest = right;

		if (largest != index)
		{
			swap(&heap->array[index], &heap->array[largest]);
			heapify(heap, largest);
		}
	}
	else
	{
		int smallest = index;

		if (left < heap->size && heap->array[left] < heap->array[smallest])
			smallest = left;

		if (right < heap->size && heap->array[right] < heap->array[smallest])
			smallest = right;

		if (smallest != index)
		{
			swap(&heap->array[index], &heap->array[smallest]);
			heapify(heap, smallest);
		}
	}
}

void heapInsert(Heap *heap, int value)
{
	if (heap->size == heap->capacity)
	{
		printf("ERROR: Heap Overflow\n");
		return;
	}

	int index = heap->size;
	heap->array[index] = value;
	heap->size++;

	if (heap->isMaxHeap)
		while ( index != 0 && heap->array[(index - 1) / 2] < heap->array[index])
		{
			swap(&heap->array[index], &heap->array[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	else
		while ( index != 0 && heap->array[(index - 1) / 2] > heap->array[index])
		{
			swap(&heap->array[index], &heap->array[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
}

int extractHead(Heap *heap)
{
	if (heap->size <= 0)
	{
		printf("ERROR: Empty Heap\n  (returning -1)\n");
		return -1;
	}

	if (heap->size == 1)
	{
		heap->size--;
		return heap->array[0];
	}

	int root = heap->array[0];
	heap->array[0] = heap->array[heap->size - 1];
	heap->size--;
	heapify(heap, 0);

	return root;
}

void deleteKey(Heap *heap, int index)
{
	if (index >= heap->size)
	{
		printf("ERROR: Invalid Index\n");
		return;
	}

	if (index == heap->size - 1)
	{
		heap->size--;
		return;
	}

	heap->array[index] = heap->array[heap->size - 1];
	heap->size--;
	heapify(heap, index);
}

void printHeap(Heap *heap)
{
	for (int i = 0; i < heap->size; i++)
		printf("%d ", heap->array[i]);
	printf("\n");
}

void heapFree(Heap *heap)
{
	free(heap->array);
	free(heap);
}

/*
// Simple main for debugging purposes
int main()
{
	int i; // Loop variable
	srand(time(NULL));
	Heap *minHeap = initHeap(10, 0);
	Heap *maxHeap = initHeap(10, 1);
	for (i = 0; i < 10; i++)
	{
		int temp = rand() % 50 + 1;
		heapInsert(minHeap, temp);
		heapInsert(maxHeap, temp);
	}

	printf("\n");

	printf("Max Heap array: ");
	printHeap(maxHeap);

	printf("Extraction order from maxHeap: \n");
	for (i = 0; i < 10; i++)
		printf("%d ", extractHead(maxHeap));
	printf("\n");

	printf("\n");

	printf("Min Heap array: ");
	printHeap(minHeap);

	printf("Extraction order from minHeap: \n");
	for (i = 0; i < 10; i++)
		printf("%d ", extractHead(minHeap));
	printf("\n");

	printf("\n");

	heapFree(minHeap);
	heapFree(maxHeap);
	return 0;
}
*/
