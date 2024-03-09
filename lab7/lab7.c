#include <stdio.h>

void bubbleSort(int arr[], int n, int swaps[]) {
    int i, j, temp, totalSwaps = 0;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                swaps[arr[j+1]]++;
                swaps[arr[j]]++;
                totalSwaps++;
            }
        }
    }

    for (int k = 0; k < 100; k++) {
        if (swaps[k] > 0) {
            printf("%d: # of times %d is swapped: %d\n", k, k, swaps[k]);
        }
    }

    printf("Total Swaps: %d\n", totalSwaps);
}

void selectionSort(int arr[], int n, int swaps[]) {
    int i, j, minIndex, temp, totalSwaps = 0;

    for ( i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = 0; j < n; j++) {
            if (arr[minIndex] > arr[j]) {
                temp = arr[minIndex];
                arr[minIndex] = arr[j];
                arr[j] = temp;
            }
        }
        if (minIndex != i) {
            totalSwaps++;
            swaps[arr[i]]++;
        }
    }


    for (int k = 0; k < 100; k++) {
        if (swaps[k] > 0) {
            printf("%d: # of times %d is swapped: %d\n", k, k, swaps[k]);
        }
    }
    printf("Total Swaps: %d\n", totalSwaps);
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);

    int swaps1[100] = {0}; // assuming the values are less than 100
    int swaps2[100] = {0};

    printf("\narray1 bubble sort:\n");
    bubbleSort(array1, n1, swaps1);

    printf("\narray2 bubble sort:\n");
    bubbleSort(array2, n2, swaps2);

    printf("\narray1 selection:\n");
    selectionSort(array1, n1, swaps1);

    printf("\narray2 selection:\n");
    selectionSort(array2, n2, swaps2);

    return 0;
}

