#ifndef UTILS_H
#define UTILS_H
#include "bagOfWord.h"

int load_vocab(char *vocab_file, WordEntry *words, int max_word);
DatasetHeader load_docword(char *docword_file, WordEntry *words, int max_word);
WordEntry *copy_entries(WordEntry *words, int W);
void print_top_k(WordEntry *sorted, int total, int k);
void saveToFile (const char *filename, WordEntry *arr, int n, double time_taken);

#endif