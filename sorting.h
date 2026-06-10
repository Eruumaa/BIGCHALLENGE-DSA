#ifndef SORTING_H
#define SORTING_H
#include "bagOfWord.h"

void swap (WordEntry *a, WordEntry *b);
void insertionSort(WordEntry *arr, int n);
void heap_sort(WordEntry *arr, int n);
void quickSort (WordEntry arr[], int low, int high);

#endif