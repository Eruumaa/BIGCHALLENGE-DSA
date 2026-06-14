# 🚀 Big Challenge: Struktur Data & Algoritma - Bag of Words

Selamat datang di repositori proyek **Big Challenge** untuk mata kuliah Struktur Data dan Algoritma. Proyek ini dikembangkan menggunakan bahasa C untuk memproses, mengakumulasi, dan mengurutkan dataset teks berskala masif (*Bag of Words*) dari UCI Machine Learning Repository.

---

## 👥 Tim Pengembang

* **Muhammad Aqil Mubarak** (250810701100003)
* **Virzi Mayhand Syahputra** (250810701100077)

**Institusi:** Universitas Syiah Kuala (USK), Fakultas MIPA, Jurusan Informatika.

📄 **Dokumen Laporan Akhir:** [Baca Laporan (PDF)](https://github.com/Eruumaa/BIGCHALLENGE-DSA)
🎥 **Video Demonstrasi & Penjelasan:** [Tonton di YouTube](https://youtu.be/xXKTgXLwh-s)

---

## 🎯 Deskripsi Proyek

Dataset *Bag of Words* berisi daftar kosakata unik (`vocab.*.txt`) dan frekuensi kemunculannya di berbagai dokumen (`docword.*.txt`). Proyek ini menuntut penyelesaian masalah pemrosesan data berjumlah ratusan ribu baris ke dalam memori komputer secara efisien.

Program ini secara dinamis akan:

1. Membaca dan mem-*parsing* file dataset.
2. Mengakumulasikan frekuensi kata dari seluruh dokumen.
3. Mengurutkan kata dari frekuensi terbesar ke terkecil (*descending*) menggunakan tiga algoritma *sorting* berbeda.
4. Mencetak daftar *Top-K* kata beserta frekuensinya ke layar monitor.
5. Menyimpan keseluruhan hasil pengurutan beserta kalkulasi **waktu eksekusi (ms)** ke dalam sebuah file teks eksternal.

---

## ✨ Fitur Utama

* **Auto-Detection Path:** Pengguna dapat memasukkan letak file `docword` dari direktori mana saja (misal: `../Data/docword.kos.txt`), dan sistem akan otomatis melacak pasangan file `vocab`-nya.
* **Robust I/O Parsing:** Menggunakan fungsi *parsing* string tingkat rendah dan `fscanf` untuk menghindari *buffer overflow* dan kelebihan konsumsi memori saat memproses dataset berukuran besar (seperti PubMed yang mencapai 1.7GB).
* **Multiple Sorting Algorithms:** Dilengkapi dengan 3 pilihan algoritma pengurutan untuk analisis komparasi performa:
  * 🐢 *Insertion Sort* (Algoritma Sederhana)
  * ⚡ *Quick Sort* (Divide & Conquer)
  * 🌲 *Heap Sort* (Complete Binary Tree / Max-Heap)

---

## 📊 Alur Program (Flowchart)

Berikut adalah alur logika pemrosesan data dari tahap inisialisasi, komputasi *sorting*, hingga pencetakan *output*.

![Flowchart Program](https://github.com/Eruumaa/BIGCHALLENGE-DSA/blob/main/DSA%20Flowchart.drawio.png)

---

## ⏱️ Analisis Kompleksitas Algoritma

Berdasarkan pengujian pada dataset, berikut adalah rangkuman performa waktu algoritma yang digunakan dalam program ini (mengacu pada pengurutan secara *descending*):

| Algoritma | Best Case | Worst Case | Average Case | Space Complexity | 
| :--- | :--- | :--- | :--- | :--- | 
| **Insertion Sort** | O(N) | O(N²) | O(N²) | O(1) | 
| **Quick Sort** | O(N log N) | O(N²) | O(N log N) | O(log N) | 
| **Heap Sort** | O(N log N) | O(N log N) | O(N log N) | O(1) | 

*Catatan: Quick Sort dan Heap Sort terbukti sangat stabil dan mampu menyelesaikan komputasi dataset berskala masif hanya dalam hitungan milidetik.*

---

## ⚙️ Cara Kompilasi dan Eksekusi

Proyek ini dilengkapi dengan `makefile` agar mudah dikompilasi pada environment GNU/GCC.

### Prasyarat

* C Compiler (GCC/MinGW)
* Make utility

### Langkah-langkah

1. *Clone* repositori ini:

```bash
   git clone [https://github.com/Eruumaa/BIGCHALLENGE-DSA.git](https://github.com/Eruumaa/BIGCHALLENGE-DSA.git)
   cd BIGCHALLENGE-DSA
```

2. Lakukan kompilasi menggunakan make:

```Bash
   make
```

3. Jalankan program hasil kompilasi:

```Bash
   ./bigchallange
```

4. Saat program berjalan, masukkan path dari file dataset docword (pastikan Anda sudah mengunduh dataset-nya). Contoh:

```
   Tentukan file docword: Data/docword.kos.txt
```

📚 Referensi
- Draf Tugas Spesifikasi Big Challenge SDA 2025/2026 - Prof. Dr. Taufik Fuadi Abidin, M.Tech.
- Laporan Resmi Kelompok 1: Kelompok1_BIGCHALLENGE_SDA_2026a.pdf
- UCI Machine Learning Repository (Bag of Words Dataset): [Link Dataset](https://archive.ics.uci.edu/dataset/164/bag+of+words)
