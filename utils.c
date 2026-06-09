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
    // printf("[DEBUG] Total Vocab = %d\n", count);
    return count;
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

    // printf("[DEBUG] Header dataset => D=%d  W=%d  N=%ld\n", header.D, header.W, header.N);
    
    // baca per baris data
    char line[64];
    while (fgets(line, sizeof(line), fpDocword))
    {
        char *ptr = line;
        
        // Parse docID
        while (*ptr == ' ') {ptr++;}
        docID = 0;
        while(*ptr >= '0' && *ptr <= '9'){
            docID = docID * 10 + (*ptr++ - '0');
        }
        
        // Parse wordID
        while (*ptr == ' ') {ptr++;}
        wordID = 0;
        while(*ptr >= '0' && *ptr <= '9'){
            wordID = wordID * 10 + (*ptr++ - '0');
        }
        
        // Parse countWord
        while(*ptr == ' ') {ptr++;}
        countWord = 0;
        while(*ptr >= '0' && *ptr <= '9'){
            countWord = countWord * 10 + (*ptr++ - '0');
        }

        if (wordID >= 1 && wordID <= header.W)
            words[wordID].freq += countWord;
    }

    fclose(fpDocword);
    // printf("[DEBUG] selesai docword\n");
    return header;
}

WordEntry *copy_entries(WordEntry *words, int W)
{
    WordEntry *arr = malloc(W * sizeof(WordEntry));
    if (!arr) {
        fprintf(stderr, "[!] malloc gagal di copy_entries\n");
        return NULL;
    }

    for (int i = 0; i < W; i++) {
        arr[i] = words[i + 1];
    }
    // printf("[DEBUG] selesai copy");
    return arr;
}

