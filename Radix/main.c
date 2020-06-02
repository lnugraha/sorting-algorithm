#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void RadixSort(int *array, int last)
{

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

  RadixSort(array, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");


  return 0;
}
