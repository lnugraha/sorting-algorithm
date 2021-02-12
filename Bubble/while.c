// gcc main.cpp -o main

#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void BubbleSort(int *list)
{
  int temp, sort;
  while (1){
    sort = 0;
    for (int i=0; i<SIZE-1; ++i){
      if (list[i] > list[i+1]) {
        temp = list[i];
        list[i] = list[i+1];
        list[i+1] = temp;
      sort = 1;
      }
    } // end for

    if (sort == 0)
      break;
  } //end-while

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

  BubbleSort(array);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
