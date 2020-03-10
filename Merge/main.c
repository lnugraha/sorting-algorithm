#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void merge(int *array, int l, int m, int r) 
{ 
  int i, j, k; 
  int n1 = m - l + 1; 
  int n2 =  r - m; 
  /* create temp arrays */
  int L[n1], R[n2]; 

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++) 
	L[i] = array[l + i]; 
  for (j = 0; j < n2; j++) 
	R[j] = array[m + 1+ j]; 

  /* Merge the temp arrays back into array[l..r]*/
  i = 0; // Initial index of first subarray 
  j = 0; // Initial index of second subarray 
  k = l; // Initial index of merged subarray 
  while (i < n1 && j < n2) 
  { 
	if (L[i] <= R[j]) 
	{ 
	  array[k] = L[i]; 
	  i++; 
	} else { 
	  array[k] = R[j]; 
	  j++; 
	} 
	k++; 
  } 

  /* Copy the remaining elements of L[], if any */
  while (i < n1) 
  { 
	array[k] = L[i]; 
	i++; 
	k++; 
  } 

  /* Copy the remaining elements of R[], if any */
  while (j < n2) 
  {
	array[k] = R[j]; 
	j++; 
	k++; 
  } 
} 

void MergeSort(int *array, int l, int r) 
{ 
  if (l < r) 
  { 
	int m = l+(r-l)/2; 
	MergeSort(array, l, m); 
	MergeSort(array, m+1, r); 
	merge(array, l, m, r); 
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

  MergeSort(array, 0, SIZE-1);
  printf("POST-Sorting:\n");
  printArray(array);
  printf("\n");

  return 0;
}

