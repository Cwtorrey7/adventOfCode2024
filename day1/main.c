/*
 * Program Name: Historian Hysteria
 * Author: Chris Torrey
 * Last Edited Date: 12/12/2024
 * Program Description: This is the my solution to the Advent of Code
 *   (henceforth referred to as AoC) Day 1 question.
 */

/*** Included Libraries ***/
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Problem at hand: 
// Two groups of historians are trying to create lists of all
//   the location ID's the chief historian might be at. Unfortunately, their
//   lists are not similar. To this point we need to calculate the total distance
//   apart the two lists are. 
// To do this, we need to compare the difference between the smallest number of
//   the left list against the smallest number in the right list, continuing
//   on to the next smallest pair, and so on. Then add the calculated 
//   distances all toghether.


int main(int argc, char** argv)
{
	// Variable Decleration
	int list1In, list2In;
	Heap *list1Heap = initHeap(1000, 0);
	Heap *list2Heap = initHeap(1000, 0);

	// First, Read in and create each list as a min heap so that the smallest
	//   component is always the head of the tree
	FILE *input = fopen("input.txt", "r");

	while (fscanf(input, "%d %d", &list1In, &list2In) != EOF)
	{
		heapInsert(list1Heap, list1In);
		heapInsert(list2Heap, list2In);	
	}

	printf("Creation of list heaps is complete!\n");

	// Second, Begin taking the head values of both lists and find the
	// difference between them and begin creating the total distance
	int totDistance = 0;
	for (int i = 0; i < 1000; i++)
		totDistance += abs(extractHead(list1Heap) - extractHead(list2Heap));

	printf("Calculated total distance between the lists to be %d\n", totDistance);

	// Memory Management
	heapFree(list1Heap);
	heapFree(list2Heap);

	return 0;
}
