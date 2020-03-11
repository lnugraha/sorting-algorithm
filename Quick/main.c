#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void medianLeft(int *sortData, int left, int right)
{
  int mid, hold;
  mid = (left+right)/2;
  if (sortData[left] > sortData[mid])
  {
	hold           = sortData[left];
	sortData[left] = sortData[mid];
	sortData[mid]  = hold;
  }

  if (sortData[left] > sortData[right])
  {
	hold           = sortData[left];
	sortData[left] = sortData[right];
	sortData[right]= hold;
  }
  
  if (sortData[mid] > sortData[right])
  {
	hold           = sortData[mid];
	sortData[mid]  = sortData[right];
	sortData[right]= hold;
  }
  
  hold           = sortData[left];
  sortData[left] = sortData[mid];
  sortData[mid]  = hold;
}

void QuickInsertion(int *sortData, int first, int last)
{
  int hold, walker;
  for (int current=first+1; current<=last; current++)
  {
	hold = sortData[current];
	walker = current-1;
	while(walker >= first && hold<sortData[walker])
	{
	  sortData[walker+1] = sortData[walker];
	  walker = walker-1;
	}
	sortData[walker+1] = hold;
  }
}

void QuickSort(int *sortData, int left, int right)
{
  #define MIN_SIZE 16
  int sortLeft, sortRight, pivot, hold;

  if ( (right-left) > MIN_SIZE )
  {
	medianLeft(sortData, left, right);
	pivot = sortData[left];
	sortLeft = left+1;
	sortRight = right;
	while (sortLeft <= sortRight)
	{
	  while (sortData[sortLeft] < pivot) sortLeft = sortLeft + 1;
	  while (sortData[sortRight] >= pivot) sortRight = sortRight - 1;
	  if (sortLeft <= sortRight)
	  {
		hold = sortData[sortLeft];
		sortData[sortLeft] = sortData[sortRight];
		sortData[sortRight] = hold;
		sortLeft = sortLeft + 1;
		sortRight = sortRight - 1;
	  } // END-IF
	}

	sortData[left] = sortData[sortLeft-1];
	sortData[sortLeft-1] = pivot;

	if (left < sortRight) QuickSort(sortData, left, sortRight-1);
	if (sortLeft < right) QuickSort(sortData, sortLeft, right);
  
  } else QuickInsertion(sortData, left, right);
  
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
  
  QuickSort(array, 0, SIZE-1);
  
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
