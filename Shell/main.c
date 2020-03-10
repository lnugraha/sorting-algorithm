#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void ShellSort(int *array, int last)
{
  int hold, incre, walker;
  incre = last/2;
  while(incre != 0)
  {
	for (int curr=incre; curr <= last; curr++)
	{
	  hold = array[curr];
	  walker = curr - incre;
	  while(walker >=0 && hold < array[walker])
	  {
		array[walker + incre] = array[walker];
		walker = (walker - incre);
	  }
	  array[walker + incre] = hold;
	} // END-FOR
	incre = incre/2;
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

  ShellSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}

