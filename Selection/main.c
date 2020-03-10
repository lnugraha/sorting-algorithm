#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void SelectionSort(int *list, int last)
{
  int smallest, holdData;
  for (int current=0; current<last; current++)
  {
	smallest = current;
	for (int walker=current+1; walker<=last; walker++)
	{
	  if (list[walker] < list[smallest]) smallest = walker;
	}
	  holdData      = list[current];
	  list[current] = list[smallest];
	  list[smallest] = holdData;
  
  } // END-FOR current
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

  SelectionSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
