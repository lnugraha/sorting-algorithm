// gcc main.cpp -o main

#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void BubbleSort(int *list, int last_idx)
{
  int temp;
  for (int current=0, sorted=0; current<=last_idx && !sorted; current++)
  {
	for (int walker=last_idx, sorted=1; walker>current; walker--)
	{
	  if (list[walker] < list[walker-1])
	  {
		sorted         = 0;
		temp           = list[walker];
		list[walker]   = list[walker-1];
		list[walker-1] = temp;
	  }
	} // END-FOR walker
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

  BubbleSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
