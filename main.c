/* Bryson Goad
 * Parallel Programming lab 3 - Count Sort
 * Implementation of a parallel count sort using OpenMP
 * randomly generates an array of ints for ease of testing with various sizes
 * Program Arguments: <array_size> <thread_count>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

void Count_sort(int a[], int length);

int thread_count;   // number of threads to use
double time_start,  // Start time of the parallel section
        time_end;   // Finish time of the parallel section

int main(int argc, char* argv[]) {
    int array_size; // Size of the array to be sorted
    int* a;         // The array to be sorted

    // initialize variables with program arguments
    array_size = atoi(argv[1]);
    thread_count = atoi(argv[2]);

    // Allocate the array
    a = malloc(array_size*sizeof(int));

    // Fill the array with random numbers
    srand(time(NULL));
    for (int i = 0; i < array_size; i++){
        a[i] = rand()%100000;
    }

    // Display the initial unsorted array
    for (int i = 0; i < array_size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // sort array
    Count_sort(a, array_size);

    // Display the sorted array
    for (int i = 0; i < array_size; i++) {
        printf("%d ", a[i]);
    }
    // Display the elapsed time of the parallel section
    printf("\nelapsed time: %f\n", time_end-time_start);
    return 0;
}

// Sorts an array using a count sort
// Parameters:
//      a : the array to be sorted
//      length : the length of the array
void Count_sort(int a[], int length) {
    int i,      // index for outer loop
        j,      // index for inner loop, private for each thread
        count;  // Number of elements less than the current one, private for each thread

    // Allocate temporary array for sorting
    int* temp = malloc(length*sizeof(int));

    time_start = omp_get_wtime();   // start timer

    // Do a count sort in parallel
#   pragma omp parallel for num_threads(thread_count) private (count,j)
    // for each element in the array
    for (i = 0; i < length; i++) {
        count = 0;
        // count every other element that is less than the current one
        for (j = 0; j < length; j++){
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        }
        // insert current element at index [count] in the temporary array
        temp[count] = a[i];
    }

    time_end = omp_get_wtime();     // end timer

    // copy sorted array into original array
    memcpy(a, temp, length*sizeof(int));
    free(temp);
}