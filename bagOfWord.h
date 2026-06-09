#ifndef BAG_OF_WORD
#define BAG_OF_WORD

#define MAX_WORD_LEN 64
#define MAX_WORD 145000

typedef struct
{
    int wordID;
    char word[64];
    long freq;
} WordEntry;

typedef struct {
    int D;
    int W; 
    long N;
} DatasetHeader;


#endif