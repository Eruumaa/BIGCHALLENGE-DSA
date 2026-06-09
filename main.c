#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bagOfWord.h"
#include "utils.h"

int main(){
    WordEntry *words = calloc(MAX_WORD + 1, sizeof(WordEntry));
    if (!words) { fprintf(stderr, "ERROR: Gagal mengalokasi memori untuk words\n"); return 1;}

    DatasetHeader header;

    // Load Vocab
    load_vocab("vocab.pubmed.txt", words, MAX_WORD);

    // Load Docword
    header = load_docword("docword.pubmed.txt", words, MAX_WORD);

    // copy word untuk sorting nanti
    // WordEntry *arr = copy_entries(words, header.W);

    // baca data
    print_top_k_beta(words);
    // print_top_k_beta(arr);
    

    free(words);
    return 0;
}