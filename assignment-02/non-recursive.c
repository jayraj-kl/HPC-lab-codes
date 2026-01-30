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

void iterativeMergeSort(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) {
        printf("Memory allocation for temp array failed\n");
        return;
    }

    for (int currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = leftStart + currSize - 1;
            int rightEnd = (leftStart + 2 * currSize - 1 < n - 1) ? leftStart + 2 * currSize - 1 : n - 1;

            if (mid < n - 1) {
                merge(arr, leftStart, mid, rightEnd, temp);
            }
        }
    }
    free(temp);
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
    iterativeMergeSort(arr, n);
    double end = omp_get_wtime();
    // ---- TIMER END ----

    printf("Time taken for sorting: %f seconds\n", end - start);
    free(arr);

    return 0;
}
