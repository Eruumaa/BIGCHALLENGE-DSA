#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "bagOfWord.h"
#include "utils.h"
#include "sorting.h"

int main(){
    WordEntry *words = calloc(MAX_WORD + 1, sizeof(WordEntry));
    if (!words) { fprintf(stderr, "ERROR: Gagal mengalokasi memori untuk words\n"); return 1;}

    char docwordInput[256];
    char vocabInput[256];
    char directoryPath[256] = "";

    printf("Tentukan file docword: ");
    scanf("%255s", docwordInput);

    char *lastSlash = strrchr(docwordInput, '/');
    char *lastBackslash = strrchr(docwordInput, '\\');
    char *fileName = docwordInput; 

    if (lastSlash != NULL || lastBackslash != NULL) {
        char *lastSep = (lastSlash > lastBackslash) ? lastSlash : lastBackslash;
        fileName = lastSep + 1; 
        
        int dirLen = fileName - docwordInput;
        strncpy(directoryPath, docwordInput, dirLen);
        directoryPath[dirLen] = '\0';
    }

    if (strncmp(fileName, "docword.", 8) == 0) {
        sprintf(vocabInput, "%svocab.%s", directoryPath, fileName + 8);
    } else {
        printf("[!] Format file tidak sesuai. Harap masukkan nama file berformat docword.*.txt\n");
        free(words);
        return 1;
    }

    printf("\n[i] Sedang memuat %s dan %s...\n", vocabInput, docwordInput);

    int totalVocab = load_vocab(vocabInput, words, MAX_WORD);
    if(totalVocab <= 0) {
        free(words);
        return 1;
    }
    
    DatasetHeader header = load_docword(docwordInput, words, MAX_WORD);
    if(header.W <= 0 || header.D <= 0) {
        fprintf(stderr, "[!] Gagal memuat docword file atau data kosong\n");
        free(words);
        return 1;
    }

    int pilihan;
    do {
        pilihan = -1;   
        printf("\nPilihan:\n");
        printf("  1) Urutkan dengan Insertion Sort   (simpan ke file)\n");
        printf("  2) Urutkan dengan Quick Sort       (simpan ke file)\n");
        printf("  3) Urutkan dengan Heap Sort        (simpan ke file)\n");
        printf("  4) Tampilkan k kata terbesar ke layar\n");
        printf("  5) Selesai\n");
        printf("Pilihan anda: ");
        
        // Membersihkan buffer jika user menginputkan selain angka
        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
        }

        char output_file[128];
        clock_t start, end;
        double time_taken;

        WordEntry *arr = NULL; 
        int k;                  

        switch(pilihan) {
            case 1: 
                printf("\n[i] Memulai Insertion Sort...\n");
                arr = copy_entries(words, header.W);
                
                start = clock();
                insertionSort(arr, header.W);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                printf("\nSelesai mengurutkan, Waktu yang diperlukan: %.0f ms\n", time_taken);
                sprintf(output_file, "output_insertion_%s", fileName + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;

            case 2:
                printf("\n[i] Memulai Quicksort...\n");
                arr = copy_entries(words, header.W);
                
                start = clock();
                quickSort(arr, 0, header.W - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                printf("\nSelesai mengurutkan, Waktu yang diperlukan: %.0f ms\n", time_taken);
                sprintf(output_file, "output_quicksort_%s", fileName + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;

            case 3: 
                printf("\n[i] Memulai Heapsort...\n");
                arr = copy_entries(words, header.W);
                
                start = clock();
                heap_sort(arr, header.W);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                printf("\nSelesai mengurutkan, Waktu yang diperlukan: %.0f ms\n", time_taken);
                sprintf(output_file, "output_heapsort_%s", fileName + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;
        
            case 4:
                printf("\nMasukkan nilai k (10 < k < 150): ");
                if (scanf("%d", &k) != 1){
                    printf(" [! Harap ]Masukkan Bilangan Bulat");
                    break;
                }

                if(k > 10 && k < 150){
                    printf("\n[i] Mengurutkan data menggunakan Quicksort untuk mendapatkan Top %d...\n", k);
                    arr = copy_entries(words, header.W);
                    
                    start = clock();
                    quickSort(arr, 0, header.W - 1);
                    end = clock();
                    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
                    
                    print_top_k(arr, header.W, k);

                    printf("\nWaktu untuk mengurutkan: %.0f ms\n", time_taken);
                    
                    free(arr);
                } else {
                    printf("Harap masukkan nilai k (10 < k < 150)");
                    break;
                }
                
                break;

            case 5:
                printf("\n[i] Program Selesai.\n");
                break;
            
            default:
                printf("\n[!] Pilihan tidak valid!\n");
        }
    } while(pilihan != 5);

    free(words);
    return 0;
}