# SIKAWAN — Sistem Informasi Keuangan Warga

![Bahasa](https://img.shields.io/badge/bahasa-C-00599C?logo=c&logoColor=white)
![Antarmuka](https://img.shields.io/badge/antarmuka-CLI-4D4D4D)
![Lisensi](https://img.shields.io/badge/lisensi-MIT-green)

**SIKAWAN** adalah aplikasi berbasis terminal (CLI) yang ditulis dalam bahasa C untuk mencatat keuangan kas warga, misalnya kas RT/RW. Aplikasi ini membantu pengurus mengelola data warga, mencatat iuran bulanan, memantau tunggakan, mencatat pengeluaran, dan membuat laporan keuangan bulanan. Semua data tersimpan otomatis ke file teks, sehingga tidak perlu database atau pustaka tambahan.

Proyek ini dibuat sebagai proyek mata kuliah Dasar Pemrograman (DASPRO).

## Daftar Isi

- [Fitur](#fitur)
- [Struktur Proyek](#struktur-proyek)
- [Persyaratan](#persyaratan)
- [Kompilasi dan Menjalankan](#kompilasi-dan-menjalankan)
- [Panduan Penggunaan](#panduan-penggunaan)
- [Contoh Keluaran](#contoh-keluaran)
- [Aturan dan Perilaku Program](#aturan-dan-perilaku-program)
- [Format File Data](#format-file-data)
- [Cara Kerja Kode](#cara-kerja-kode)
- [Batasan](#batasan)
- [Ide Pengembangan](#ide-pengembangan)
- [Kontribusi](#kontribusi)
- [Lisensi](#lisensi)
- [Penulis](#penulis)

## Fitur

- **Kelola data warga**: tambah, tampilkan, cari, ubah nama, dan hapus warga. Setiap warga mendapat ID unik yang tidak dipakai ulang.
- **Atur nominal iuran**: nominal iuran per bulan bisa diubah kapan saja (bawaan Rp 20.000).
- **Catat pembayaran iuran**: mendukung pembayaran penuh maupun dicicil dalam beberapa kali bayar.
- **Cek status dan tunggakan**: menampilkan siapa yang LUNAS dan siapa yang belum, lengkap dengan jumlah kekurangan, jumlah penunggak, dan total tunggakan.
- **Catat pengeluaran kas**: setiap pengeluaran disertai keterangan dan tidak bisa melebihi saldo kas.
- **Lihat saldo kas**: total pemasukan, total pengeluaran, dan saldo.
- **Riwayat transaksi**: daftar seluruh pemasukan dan pengeluaran secara berurutan.
- **Laporan keuangan bulanan**: ringkasan pemasukan, pengeluaran, selisih, saldo keseluruhan, dan status iuran bulan tersebut.
- **Penyimpanan otomatis**: data disimpan ke `data_sikawan.txt` setiap ada perubahan dan dibaca kembali saat program dibuka.
- **Validasi input**: input angka yang salah atau di luar rentang akan diminta ulang, bukan membuat program berhenti.

## Struktur Proyek

```
project-daspro/
├── sikawan_v4.c        # Kode sumber program (satu file)
├── data_sikawan.txt    # Data contoh: 12 warga dan 33 transaksi (Okt–Nov 2026)
├── README.md           # Dokumentasi proyek
└── LICENSE             # Lisensi MIT
```

## Persyaratan

- Kompiler C apa pun yang mendukung standar C umum, misalnya **GCC** atau **Clang**.
- Terminal atau command prompt.
- Tidak ada dependensi eksternal. Program hanya memakai `stdio.h`, `stdlib.h`, dan `string.h`.

Cara memasang GCC:

| Sistem operasi | Perintah / cara |
| --- | --- |
| Debian / Ubuntu | `sudo apt install build-essential` |
| Fedora | `sudo dnf install gcc` |
| macOS | `xcode-select --install` |
| Windows | Pasang [MinGW-w64](https://www.mingw-w64.org/) atau [MSYS2](https://www.msys2.org/) |

## Kompilasi dan Menjalankan

1. Clone repositori ini:

   ```bash
   git clone https://github.com/kurniawanhafiz/project-daspro.git
   cd project-daspro
   ```

2. Kompilasi:

   ```bash
   gcc sikawan_v4.c -o sikawan
   ```

   Untuk melihat peringatan kompiler (opsional):

   ```bash
   gcc -Wall -Wextra sikawan_v4.c -o sikawan
   ```

3. Jalankan:

   ```bash
   ./sikawan          # Linux / macOS
   sikawan.exe        # Windows
   ```

> **Penting:** jalankan program dari folder yang berisi `data_sikawan.txt`. File data dicari di folder kerja saat ini. Jika file belum ada, program mulai dengan data kosong dan akan membuat file baru saat ada data yang disimpan.

Untuk memulai dari data kosong, hapus atau ganti nama `data_sikawan.txt` sebelum menjalankan program.

## Panduan Penggunaan

Menu utama:

```
=========================================
  SIKAWAN - Sistem Informasi Keuangan Warga
=========================================
1. Kelola data warga
2. Atur nominal iuran
3. Catat pembayaran iuran
4. Cek status pembayaran & tunggakan
5. Catat pengeluaran kas
6. Lihat saldo kas
7. Riwayat transaksi
8. Laporan keuangan
9. Keluar
```

| Menu | Fungsi | Yang diminta program |
| --- | --- | --- |
| **1. Kelola data warga** | Membuka submenu: tambah, tampilkan, cari, ubah, hapus warga | Nama warga, atau ID warga untuk ubah/hapus |
| **2. Atur nominal iuran** | Mengubah iuran per bulan | Nominal baru (Rp 1 – 10.000.000) |
| **3. Catat pembayaran iuran** | Mencatat warga yang membayar iuran | ID warga, tahun, bulan, jumlah bayar |
| **4. Cek status pembayaran** | Melihat status LUNAS/BELUM LUNAS semua warga | Tahun dan bulan |
| **5. Catat pengeluaran kas** | Mencatat uang kas yang keluar | Keterangan, nominal, tahun, bulan |
| **6. Lihat saldo kas** | Menampilkan pemasukan, pengeluaran, dan saldo | — |
| **7. Riwayat transaksi** | Menampilkan semua transaksi | — |
| **8. Laporan keuangan** | Laporan satu bulan beserta status iuran | Tahun dan bulan |
| **9. Keluar** | Menyimpan data lalu menutup program | — |

Submenu **Kelola data warga**:

```
1. Tambah warga
2. Tampilkan semua warga
3. Cari warga
4. Ubah nama warga
5. Hapus warga
0. Kembali
```

### Alur kerja yang disarankan

1. Tambahkan seluruh warga lewat menu **1 → 1**.
2. Atur nominal iuran lewat menu **2** jika berbeda dari Rp 20.000.
3. Setiap ada warga yang membayar, catat lewat menu **3**.
4. Awal atau akhir bulan, cek tunggakan lewat menu **4**.
5. Catat pengeluaran kas lewat menu **5**.
6. Buat laporan bulanan lewat menu **8**.

## Contoh Keluaran

Berikut keluaran asli program saat dijalankan dengan `data_sikawan.txt` bawaan repositori.

**Menu 6 — Lihat saldo kas**

```
Total pemasukan   : Rp 410000
Total pengeluaran : Rp 250000
SALDO KAS         : Rp 160000
```

**Menu 4 — Cek status pembayaran (November 2026)**

```
STATUS IURAN BULAN 11/2026 (iuran Rp 20000)
Budi Santoso : LUNAS
Siti Aminah : LUNAS
Ahmad Fauzi : BELUM LUNAS, kurang Rp 10000
Dewi Lestari : LUNAS
Rudi Hartono : LUNAS
Rina Marlina : LUNAS
Eko Prasetyo : LUNAS
Fitri Handayani : LUNAS
Hendra Wijaya : BELUM LUNAS, kurang Rp 20000
Nurul Hidayah : LUNAS
Agus Salim : LUNAS
Yulia Sari : BELUM LUNAS, kurang Rp 10000
Warga yang menunggak : 3 orang
Total tunggakan      : Rp 40000
```

## Aturan dan Perilaku Program

**Warga**

- ID dibuat otomatis dan bertambah satu setiap ada warga baru. ID warga yang sudah dihapus tidak dipakai lagi.
- Nama tidak boleh kosong dan maksimal 49 karakter.
- Pencarian nama berupa pencocokan sebagian teks dan **membedakan huruf besar/kecil** (mencari `Budi` tidak menemukan `budi`).
- Jika warga dihapus, transaksi lamanya tetap ada. Di riwayat, transaksi tersebut ditandai `(warga sudah dihapus)`.

**Pembayaran iuran**

- Pembayaran boleh dicicil. Jumlah bayar harus antara Rp 1 dan sisa kekurangan bulan itu.
- Jika warga sudah lunas di bulan tersebut, pembayaran baru ditolak.
- Status LUNAS ditentukan dari total semua pembayaran warga di bulan dan tahun yang sama dibandingkan dengan nominal iuran.

**Pengeluaran**

- Keterangan wajib diisi.
- Nominal tidak boleh melebihi saldo kas saat ini. Jika saldo nol atau kurang, pengeluaran tidak bisa dicatat.

**Umum**

- Tahun yang diterima: 2000–2100. Bulan: 1–12.
- Setiap perubahan data langsung disimpan ke file.

## Format File Data

Data disimpan dalam file teks biasa `data_sikawan.txt` dengan susunan berikut:

```
<iuran> <idBerikutnya> <jumlahWarga> <jumlahTransaksi>
<id warga 1>
<nama warga 1>
...
<jenis> <id warga> <bulan> <tahun> <nominal>
<keterangan>
...
```

Keterangan:

- Baris pertama berisi empat angka: nominal iuran, ID berikutnya yang akan dipakai, jumlah warga, dan jumlah transaksi.
- Setiap warga memakai 2 baris: ID, lalu nama.
- Setiap transaksi memakai 2 baris: data transaksi, lalu keterangan.
- `jenis` bernilai `M` untuk pemasukan (iuran) atau `K` untuk pengeluaran.
- Untuk pengeluaran, `id warga` diisi `0`. Untuk pemasukan, kolom keterangan berisi `-`.

Contoh potongan file:

```
20000 13 12 33
1
Budi Santoso
2
Siti Aminah
...
M 1 10 2026 20000
-
K 0 10 2026 30000
Kebersihan lingkungan
```

> Hindari mengedit file ini secara manual kecuali perlu. Jumlah warga dan jumlah transaksi di baris pertama harus sesuai dengan isi file, atau data bisa terbaca salah.

## Cara Kerja Kode

Seluruh program ada di satu file, `sikawan_v4.c`, dan disusun dengan array global (tanpa struct dan tanpa alokasi memori dinamis), sehingga mudah dipelajari.

| Bagian | Isi |
| --- | --- |
| Data warga | `idWarga[]`, `namaWarga[][]`, `jumlahWarga`, `idBerikutnya` |
| Data transaksi | `jenis[]`, `trxId[]`, `trxBulan[]`, `trxTahun[]`, `trxNominal[]`, `trxKet[][]`, `jumlahTrx` |
| Fungsi bantu | `bacaAngka`, `bacaTeks`, `hapusEnter`, `cariWarga`, `tampilDaftarWarga`, `totalBayar`, `hitungTotal`, `cekStatus` |
| Penyimpanan | `simpanData`, `bacaData` |
| Menu | `kelolaWarga`, `aturIuran`, `catatPembayaran`, `menuStatus`, `catatPengeluaran`, `lihatSaldo`, `riwayat`, `laporan` |
| Program utama | `main` menampilkan menu dalam perulangan `do ... while` sampai pengguna memilih keluar |

Input dibaca dengan `fgets` lalu diubah dengan `atoi`, sehingga masukan yang bukan angka tidak membuat program macet.

## Batasan

- Kapasitas maksimal **100 warga** dan **1.000 transaksi** (`MAX_WARGA` dan `MAX_TRX` di awal kode).
- Nominal iuran hanya satu nilai yang berlaku untuk semua bulan. Jika iuran diubah, status bulan-bulan sebelumnya ikut dihitung ulang dengan nominal yang baru.
- Transaksi tidak bisa diubah atau dihapus lewat program, hanya ditambah.
- Tidak ada autentikasi pengguna. Siapa pun yang menjalankan program bisa mengubah data.
- Nilai uang disimpan sebagai bilangan bulat rupiah, tanpa pemisah ribuan pada tampilan.
- Pencarian nama membedakan huruf besar/kecil.

## Ide Pengembangan

- Riwayat nominal iuran per periode agar perubahan iuran tidak memengaruhi bulan lalu.
- Fitur koreksi atau pembatalan transaksi.
- Pencarian nama tanpa membedakan huruf besar/kecil.
- Format rupiah dengan pemisah ribuan.
- Ekspor laporan ke file `.txt` atau `.csv`.
- Pemakaian `struct` untuk merapikan data warga dan transaksi.
- Cadangan (backup) otomatis file data.

## Kontribusi

Kontribusi terbuka untuk siapa saja.

1. Fork repositori ini.
2. Buat cabang baru: `git checkout -b fitur-baru`
3. Lakukan perubahan dan commit: `git commit -m "Tambah fitur baru"`
4. Push ke cabang Anda: `git push origin fitur-baru`
5. Buka Pull Request.

Jika menemukan bug atau punya saran, silakan buat [Issue](https://github.com/kurniawanhafiz/project-daspro/issues).

## Lisensi

Proyek ini dirilis di bawah [Lisensi MIT](LICENSE). Anda bebas menggunakan, menyalin, memodifikasi, dan mendistribusikan proyek ini, selama pemberitahuan hak cipta dan lisensi disertakan.

## Penulis

**Kurniawan Hafiz** — [@kurniawanhafiz](https://github.com/kurniawanhafiz)
