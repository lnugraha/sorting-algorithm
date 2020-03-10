#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void InsertionSort(int *array, int last)
{
  int hold, walker;
  for (int current=1; current<=last;current++)
  {
	hold = array[current];
	for (walker = current-1; walker >=0 && hold <array[walker]; walker--)
	  array[walker+1] = array[walker];
	array[walker+1] = hold;
  }

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

  InsertionSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
