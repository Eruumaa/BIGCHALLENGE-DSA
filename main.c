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

    char vocabFile[128];
    char docwordFile[128];
    char docwordName[256];
    char vocabName[256];

    printf("Tentukan dataset : ");
    scanf("%127s", docwordFile);
    
    if (strncmp(docwordFile, "docword.", 8) == 0) {
        sprintf(vocabFile, "vocab.%s", docwordFile + 8);
    } else {
        printf("[!] Format file tidak sesuai. Harap masukkan nama file berformat docword.*.txt\n");
        free(words);
        return 1;
    }

    sprintf(docwordName, "%s", docwordFile);
    sprintf(vocabName, "%s", vocabFile);

    printf("\n[i] Sedang memuat %s dan %s...\n", vocabName, docwordName);

    int totalVocab = load_vocab(vocabName, words, MAX_WORD);
    if(totalVocab <= 0) {
        free(words);
        return 1;
    }
    
    DatasetHeader header = load_docword(docwordName, words, MAX_WORD);
    if(header.W <= 0 || header.D <= 0) {
        fprintf(stderr, "[!] Gagal memuat docword file atau data kosong\n");
        free(words);
        return 1;
    }

    int pilihan;
    do {
        printf("\nPilihan:\n");
        printf("1) Urutkan data menggunakan salah satu metode pengurutan sederhana.\n");
        printf("   Simpan keluaran dalam sebuah file teks secara descending order,\n");
        printf("   termasuk waktu yang dibutuhkan untuk mengurutkan data tersebut.\n");
        printf("2) Urutkan data menggunakan metode quicksort.\n");
        printf("   Simpan keluaran dalam sebuah file teks secara descending order\n");
        printf("   dan tampilkan waktu yang dibutuhkan untuk mengurutkan data tsb.\n");
        printf("3) Urutkan data menggunakan metode heapsort.\n");
        printf("   Simpan keluaran dalam sebuah file teks secara descending order\n");
        printf("   dan tampilkan waktu yang dibutuhkan untuk mengurutkan data tsb.\n");
        printf("4) Tampilkan ke layar monitor 100 kata dengan frekuensi terbesar\n");
        printf("   termasuk waktu yang dibutuhkan untuk mengurutkan data tsb.\n");
        printf("5) Selesai\n");
        printf("Pilihan anda: ");
        
        // Membersihkan buffer jika user menginputkan selain angka
        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            continue;
        }

        char output_file[128];
        clock_t start, end;
        double time_taken;

        switch(pilihan) {
            case 1: {
                printf("\n[i] Memulai Insertion Sort...\n");
                WordEntry *arr = copy_entries(words, header.W);
                
                start = clock();
                insertionSort(arr, header.W);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                sprintf(output_file, "output_insertion_%s", docwordFile + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;
            }

            case 2: {
                printf("\n[i] Memulai Quicksort...\n");
                WordEntry *arr = copy_entries(words, header.W);
                
                start = clock();
                quickSort(arr, 0, header.W - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                sprintf(output_file, "output_quicksort_%s", docwordFile + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;
            }

            case 3: {
                printf("\n[i] Memulai Heapsort...\n");
                WordEntry *arr = copy_entries(words, header.W);
                
                start = clock();
                heap_sort(arr, header.W);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                sprintf(output_file, "output_heapsort_%s", docwordFile + 8);
                saveToFile(output_file, arr, header.W, time_taken);
                
                free(arr);
                break;
            }

            case 4: {
                int k;
                // Meskipun di menu tertulis 100, tugas meminta penentuan nilai k ketika pilihan 4 dipilih
                printf("\nMasukkan nilai k (10 < k < 150): ");
                scanf("%d", &k);
                
                printf("\n[i] Mengurutkan data (menggunakan Quicksort) untuk mendapatkan Top %d...\n", k);
                WordEntry *arr = copy_entries(words, header.W);
                
                start = clock();
                quickSort(arr, 0, header.W - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
                
                print_top_k(arr, header.W, k);
                printf("\nWaktu untuk mengurutkan: %.0f ms\n", time_taken);
                
                free(arr);
                break;
            }

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