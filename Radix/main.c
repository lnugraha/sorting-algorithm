#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

// WARNING: Radix Sort can only sort array with non-negative elements

int get_max(int array[], int n)
{
  int max = array[0];
  for (int i=1; i<n; ++i){
    if (array[i] > max) max = array[i];
  }
  return max;
}

void countSort(int array[], int n, int exp)
{
  int output[n], i, count[10] = {0};

  for (i=0; i<n; ++i) count[ (array[i]/exp)%10 ]++;
  for (i=1; i<10; ++i) count[i] += count[i-1];

  for (i=n-1; i>=0; i--){
    output[count[ (array[i]/exp)%10 ] - 1] = array[i]; 
    count[ (array[i]/exp)%10 ]--;
  }

  for (i=0; i<n; ++i) array[i] = output[i];
}

void RadixSort(int *array, int n)
{
  int max = get_max(array, n);
  for (int exp=1; max/exp>0 ; exp*=10) countSort(array, n, exp);
}
  
void printArray(int *array)
{ 
  for (int i=0; i<SIZE; ++i) printf("%d ", array[i]); 
}

int main(int argc, char *argv[]){

  int array[SIZE] = {8, 12, 0, 2, 1, 6, 7, 5};
  printf("PRE-Sorting:\n");
  printArray(array); 
  printf("\n");

  RadixSort(array, SIZE);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}
