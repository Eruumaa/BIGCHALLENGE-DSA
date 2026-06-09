#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bagOfWord.h"

int load_vocab(char *vocab_file, WordEntry *words, int max_word){
    FILE *fpVocab = fopen(vocab_file, "r");
    if(!fpVocab){
        printf("[!] Gagal memuat file"); return -1;
    }

    int count = 0;
    char line[MAX_WORD_LEN];

    while (fgets(line, sizeof(line), fpVocab) && count < MAX_WORD){
        line[strcspn(line, "\n")] = '\0';

        int id = count + 1;
        words[id].wordID = id;
        strncpy(words[id].word, line, MAX_WORD_LEN-1);
        words[id].word[MAX_WORD_LEN-1] = '\0';
        words[id].freq = 0;

        count++;
    }
    fclose(fpVocab);
    // printf("Total Vocab = %d\n", count);
}

DatasetHeader load_docword(char *docword_file, WordEntry *words, int max_word){
    DatasetHeader header = {0, 0, 0};
    int docID, wordID;
    long countWord = 0;

    FILE *fpDocword = fopen(docword_file, "r");
    if (!fpDocword) {
        printf("[!] Gagal memuat file"); return header;
    }

    if (fscanf(fpDocword, "%d", &header.D) != 1 ||
        fscanf(fpDocword, "%d", &header.W) != 1 ||
        fscanf(fpDocword, "%ld", &header.N) != 1) {
        fprintf(stderr, "ERROR: Format header file docword tidak valid.\n");
        fclose(fpDocword);
        return header;
    }

    // printf("Header dataset => D=%d  W=%d  N=%ld\n", header.D, header.W, header.N);
    
    while(fscanf(fpDocword, "%d %d %d", &docID, &wordID, &countWord) == 3){
        if(wordID >= 1 && wordID <= header.W){
            words[wordID].freq += countWord;
        }
    }
    fclose(fpDocword);
    // printf("selesai docword\n");
}

WordEntry *copy_entries(WordEntry *words, int W)
{
    WordEntry *arr = malloc(W * sizeof(WordEntry));
    if (!arr) {
        fprintf(stderr, "ERROR: malloc gagal di copy_entries\n");
        return NULL;
    }

    for (int i = 0; i < W; i++) {
        arr[i] = words[i + 1];
    }
    return arr;
}

