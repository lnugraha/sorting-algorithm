#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void reheapUp(int *heap, int newNode)
{
  int parent, hold;
  if(newNode)
  {
	parent = (newNode-1)/2;
	if( heap[newNode] > heap[parent] )
	{
	  hold = heap[parent];
	  heap[parent] = heap[newNode];
	  heap[newNode] = heap[newNode];
	  heap[newNode] = hold;
	  reheapUp(heap, parent);
	}
  } // END-IF
}

void reheapDown(int *heap, int root, int last)
{
  int hold, leftKey, rightKey, largeChildKey, largeChildIndex;
  if( ((root*2+1))<=last )
  {
	leftKey = heap[root*2+1];
	if( (root*2+2)<=last )
	{
	  rightKey = heap[root*2+2];
	} else {
	  rightKey = -1;
	}

	if( leftKey>rightKey )
	{
	  largeChildKey = leftKey;
	  largeChildIndex = root*2 + 1;
	} else {
	  largeChildKey = rightKey;
	  largeChildIndex = root*2 + 2;
	}

	if( heap[root]<heap[largeChildIndex] )
	{
	  hold = heap[root];
	  heap[root] = heap[largeChildIndex];
	  heap[largeChildIndex] = hold;
	  reheapDown(heap, largeChildIndex, last);
	}

  } // END-IF root
}

void HeapSort(int *list, int last)
{
  int sorted, holdData;
  for (int walker=1; walker<=last; walker++) reheapUp(list, walker);
  sorted = last;
  while(sorted>0)
  {
	holdData = list[0];
	list[0] = list[sorted];
	list[sorted] = holdData;
	sorted--;
	reheapDown(list, 0, sorted);
  } // END-WHILE
}

void printArray(int *array)
{ 
  for (int i=0; i<SIZE; ++i) printf("%d ", array[i]); 
}

int main(int argc, char *argv[]){

  int array[SIZE] = {8, 12, 0, -2, 1, 6, -7, 5};
  printf("PRE-Sorting:\n");
  printArray(array); 
  printf("\n");

  HeapSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
