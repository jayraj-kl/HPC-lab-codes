#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left;      // Start index of the left subarray
    int j = mid + 1;   // Start index of the right subarray
    int k = left;      // Start index to insert into the temporary array

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

#define THRESHOLD 499  // Stop parallelizing below this size

void recursiveMergeSortHelper(int arr[], int left, int right, int temp[], int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Only parallelize if above threshold and not too deep
        if ((right - left) > THRESHOLD && depth < 4) {
            #pragma omp task shared(arr, temp)
            recursiveMergeSortHelper(arr, left, mid, temp, depth + 1);
            
            #pragma omp task shared(arr, temp)
            recursiveMergeSortHelper(arr, mid + 1, right, temp, depth + 1);
            
            #pragma omp taskwait
        } else {
            // Sequential execution for small subarrays
            recursiveMergeSortHelper(arr, left, mid, temp, depth + 1);
            recursiveMergeSortHelper(arr, mid + 1, right, temp, depth + 1);
        }
        merge(arr, left, mid, right, temp);
    }
}

void recursiveMergeSort(int arr[], int left, int right, int temp[]) {
    #pragma omp parallel
    {
        #pragma omp single
        recursiveMergeSortHelper(arr, left, right, temp, 0);
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

    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) {
        printf("Memory allocation for temp array failed\n");
        free(arr);
        return 1;
    }

    // ---- TIMER START ----
    double start = omp_get_wtime();
    recursiveMergeSort(arr, 0, n - 1, temp);
    double end = omp_get_wtime();
    // ---- TIMER END ----
    
    printf("Time taken for sorting: %f seconds\n", end - start);

    free(arr);
    free(temp);
    return 0;
}