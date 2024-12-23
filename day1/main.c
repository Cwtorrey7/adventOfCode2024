/*
 * Program Name: Historian Hysteria
 * Author: Chris Torrey
 * Last Edited Date: 12/16/2024
 * Program Description: This is the my solution to the Advent of Code
 *   (henceforth referred to as AoC) Day 1 question.
 */

/*** Included Libraries ***/
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct KVPair
{
	int key;
	int value;
} KVPair;

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
	/*** START OF PART 1 ***/

	// Variable Decleration
	int i, j; // Loop Variables
	int list1In, list2In;
	Heap *list1Heap = initHeap(1000, 0);
	Heap *list2Heap = initHeap(1000, 0);

	int *list1 = (int *) malloc(1000 * sizeof(int));
	int *list2 = (int *) malloc(1000 * sizeof(int));

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
	{
		int list1HeapHead = extractHead(list1Heap);
		list1[i] = list1HeapHead; // This will effectively reorder the list in order from smallest to largest
		int list2HeapHead = extractHead(list2Heap);
		list2[i] = list2HeapHead; // This will effectively reorder the list in order from smallest to largest
		totDistance += abs(list1HeapHead - list2HeapHead);
	}

	printf("Calculated total distance between the lists to be %d\n", totDistance);

	// Memory Management
	heapFree(list1Heap);
	heapFree(list2Heap);

	/*** END OF PART 1 ***/

	/*** START OF PART 2 ***/
	// Now I need to caclualate a total simularity score by summing the left
	//   list (list1) after multiplying each element by the number of times it
	//   appeared in the second list. The effecient way in my mind is to create
	//   a hashtable for the right list with each sample id as the key and the 
	//	 number of occurences being the value. Then iterate through left list
	//	 and calculate the simularity score.
	// Unfortunately, I don't have my hash table code created yet unlike my
	//   heap. So I'm going to be less effecient with this implementation then
	//   the envisioned plan was. Perhaps I'll come back and make the effecient
	//   implementation.

	/*
	printf("List1: \n");
	for (i = 0; i < 1000; i++)
		printf(" %d", list1[i]);
	printf("\n");

	printf("\n");

	printf("List2: \n");
	for (i = 0; i < 1000; i++)
		printf(" %d", list2[i]);
	printf("\n");
	*/

	int simScore = 0;

	j = 0; // List 2 index
	for (i = 0; i < 1000; i++)
	{
		int temp = list1[i];

		while (list2[j] != temp)
		{
			if (list2[j] < temp) // Increment j
				j++;
			else // Increment i
			{
				i++; temp = list1[i];
			}
		}

		if (i >= 1000 || j >= 1000)
			break;

		printf("  Sim score calculations for list1 entry %d...\n", temp);

		int list2recurrences = 0;
		while (list2[j] == temp)
		{
			list2recurrences++;
			j++;
		}

		printf("  Found number of recurrences in list2 to be %d...\n", list2recurrences);

		int k = i;
		while (list1[k] == temp)
		{
			simScore += temp * list2recurrences;
			k++;
		}

		printf("  Found number of recurrences in list1 to be %d...\n", (k-i));

		i = k-1;
	}

	printf("At the end of simularity score calculations, the simularity score between the two lists was found to be %d\n", simScore);


	/*** END OF PART 2 ***/
	// Memory Management
	free(list1);
	free(list2);
	return 0;
}
