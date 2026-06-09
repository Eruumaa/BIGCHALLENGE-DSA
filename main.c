#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bagOfWord.h"
#include "utils.h"

int main(){
    WordEntry words[13000];
    DatasetHeader header;

    // Load Vocab
    load_vocab("vocab.nips.txt", words, MAX_WORD);

    // Load Docword
    load_docword("docword.nips.txt", words, MAX_WORD);

    // copy word
    copy_entries(words, header.W);
    
    // printf("\n5 kata pertama dalam arr:\n");
    // for (int i = 0; i < 5; i++) {
    //     printf("arr[%d] = wordID:%d  word:%s  freq:%ld\n",
    //         i, arr[i].wordID, arr[i].word, arr[i].freq);
    // }

    // free(words);
    return 0;
}