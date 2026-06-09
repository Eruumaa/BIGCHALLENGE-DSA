#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bagOfWord.h"

void insertionSort(WordEntry *arr, int n){
    for (int i = 1; i < n; i++) {
        WordEntry key = arr[i];
        int j = i - 1;
        /* Geser elemen yang lebih KECIL dari key ke kanan */
        while (j >= 0 && arr[j].freq < key.freq) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Heap
static void heapify(WordEntry *arr, int n, int i)
{
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < n && arr[left].freq  > arr[largest].freq) largest = left;
    if (right < n && arr[right].freq > arr[largest].freq) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(WordEntry *arr, int n)
{
    // max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // keluarkan
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

    // Balik array (descending)
    for (int i = 0, j = n - 1; i < j; i++, j--)
        swap(&arr[i], &arr[j]);
}
