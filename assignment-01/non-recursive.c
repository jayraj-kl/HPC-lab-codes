#include <stdio.h>

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
    int currSize; 
    int leftStart; // For picking starting point of left subarrays

    int temp[n];

    for (currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
        for (leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = leftStart + currSize - 1;
            int rightEnd = (leftStart + 2 * currSize - 1 < n - 1) ? leftStart + 2 * currSize - 1 : n - 1;

            if (mid < n - 1) {
                merge(arr, leftStart, mid, rightEnd, temp);
            }
        }
    }
}


int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    iterativeMergeSort(arr, n);

    printf("Sorted array is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
