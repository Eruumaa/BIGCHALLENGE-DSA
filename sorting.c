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