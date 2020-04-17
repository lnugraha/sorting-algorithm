#include <cassert>

#include <iterator>
#include <algorithm>
#include <list>
#include <vector>

#include <iostream>

template<typename T>
T partition(T first, T last, T pivot)
{
  auto previousToLast = std::prev(last);
  auto pivotValue = *pivot;
  // Change pivot element to the end
  std::swap(*pivot, *previousToLast);
  auto storeIndex = first;
  // Determine index of the pivot element
  for (auto i=first; i<previousToLast; ++i){
    if(*i <= pivotValue)
    {
      std::swap(*i, *storeIndex);
      ++storeIndex;
    } // END-IF
  }
  // Restore pivot element at the determined index
  std::swap(*storeIndex, *previousToLast);
  return storeIndex;
}

template<typename T>
void quicksort(T first, T last)
{
  if (first >= last) return;

  // Select pivot index and begin partitioning
  auto pivot = first + std::distance(first, std::prev(last)) / 2;
  pivot = partition( first, last, pivot );

  // Sort each partition
  quicksort( first, std::prev(pivot) );
  quicksort( std::next(pivot), last);

}

namespace TEST{
template<typename T>
void sortImplementation(T first, T last, std::random_access_iterator_tag)
{
  assert(first <= last);
  quicksort(first, last);
}

template<typename T>
void sort(T first, T last)
{
  typedef typename std::iterator_traits<T>::iterator_category category;
  sortImplementation( first, last, category() );
}
} // END namespace TEST

int main(int argc, char *argv[]){
  std::vector<int> numbers1{3, 5, 1, 9, 0, 7, 6, 2, 4, 8};
  std::vector<int> numbers2 = numbers1;
  std::cout << "Unsorted Array:\t";
  std::for_each(numbers1.cbegin(), numbers1.cend(), [] (const int& i) {
    std::cout << i << " "; });
  
  std::cout << std::endl;

  std::cout << "std::sort() results:\t";
  std::sort(numbers1.begin(), numbers1.end());
  for (int number : numbers1) std::cout << number << " ";
  
  std::cout << std::endl;

  std::cout << "TEST::sort() results:\t";
  TEST::sort(numbers2.begin(), numbers2.end());
  for (int number : numbers2) std::cout << number << " ";

  std::cout << std::endl;
  
  return 0;
}
