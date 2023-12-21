#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

int temp = 0;

 
int partitioning(int numbers[], int begin, int end)
{
    
    int pivot = numbers[begin];
    int pivot_index = begin;

    for (int i = begin + 1; i <= end; i++) {
        if (numbers[i] <= pivot)
            pivot_index++;
    }

    temp = numbers[pivot_index];
    numbers[pivot_index] = numbers[begin];
    numbers[begin] = temp;

    int i = begin, j = end;

    while (i < pivot_index && j > pivot_index) {
        while (numbers[i] <= pivot) {
            i++;
        }
        while (numbers[j] > pivot) {
            j--;
        }
        if (i < pivot_index && j > pivot_index) {
            temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
            i++;
            j--;
        }
    }
 
    return pivot_index;
}
 
void quick_sort(int numbers[], int begin, int end)
{
    if (begin >= end)
        return;
 
    int pivot_index = partitioning(numbers, begin, end);
    
    #pragma omp task shared(numbers)
    quick_sort(numbers, begin, pivot_index - 1);

    #pragma omp task shared(numbers)
    quick_sort(numbers, pivot_index + 1, end);
}
 
int main()
{

    std::vector<int> numbers;
    int n = 10000;
    for (int i = 0; i < n; i++) {
        numbers.push_back(rand());
    }

    // check before quicksort
    // for (int i = 0; i < n; i++) {
    //     std::cout << numbers[i] << " ";
    // }

    double time = omp_get_wtime();
    quick_sort(numbers.data(), 0, n - 1);
    time = omp_get_wtime() - time;
    std::cout << "Time for quick sort: " << time << std::endl;
 
    for (int i = 0; i < n-1; i++) {
        if (numbers[i] > numbers[i+1]) {
        std::cout << "Incorrect" << " ";
        }
    }

    // check after quicksort
    // for (int i = 0; i < n; i++) {
    //     std::cout << numbers[i] << " ";
    // }

    return 0;
}