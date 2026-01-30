#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

void parallel_bubble_sort(int arr[], int n) {
    int i, j;
    bool swapped;
    
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        
        // Odd phase
        #pragma omp parallel for shared(arr, swapped)
        for (j = 1; j < n - i - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // Even phase
        #pragma omp parallel for shared(arr, swapped)
        for (j = 0; j < n - i - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // Early termination if no swaps occurred
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the array: "); 
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;  
    }
    // ---- TIMER START ----
    double start = omp_get_wtime();
    // clock_t start = clock();
    parallel_bubble_sort(arr, n);
    // clock_t end = clock();
    double end = omp_get_wtime();
    // ---- TIMER END ----
    
    // double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken: %f seconds\n", time_taken);
    printf("Time taken for sorting: %f seconds\n", end - start);
    free(arr);
    
    return 0;
}