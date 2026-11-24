/* Sistem Informasi Keuangan Warga (SIKAWAN) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WARGA 100
#define MAX_TRX 1000

/* ===== DATA WARGA ===== */
int idWarga[MAX_WARGA];
char namaWarga[MAX_WARGA][50];
int jumlahWarga = 0;
int idBerikutnya = 1;

/* ===== IURAN PER BULAN ===== */
int iuran = 20000;

/* ===== DATA TRANSAKSI ===== */
/* jenis: 'M' = pemasukan (iuran), 'K' = pengeluaran */
char jenis[MAX_TRX];
int trxId[MAX_TRX];
int trxBulan[MAX_TRX];
int trxTahun[MAX_TRX];
int trxNominal[MAX_TRX];
char trxKet[MAX_TRX][50];
int jumlahTrx = 0;


/* === FUNGSI BANTU === */

/* menghapus tanda enter di akhir tulisan */
void hapusEnter(char teks[]) {
    int i;
    for (i = 0; teks[i] != '\0'; i++) {
        if (teks[i] == '\n') {
            teks[i] = '\0';
        }
    }
}

/* minta angka, diulang terus sampai angkanya ada di antara min dan max */
int bacaAngka(char pesan[], int min, int max) {
    char teks[30];
    int angka;

    while (1) {
        printf("%s", pesan);
        if (fgets(teks, 30, stdin) == NULL) {
            exit(0);
        }
        angka = atoi(teks);
        if (angka >= min && angka <= max) {
            return angka;
        }
        printf("Input salah! Masukkan angka %d sampai %d.\n", min, max);
    }
}

/* minta tulisan (boleh pakai spasi) */
void bacaTeks(char pesan[], char hasil[]) {
    printf("%s", pesan);
    fgets(hasil, 50, stdin);
    hapusEnter(hasil);
}

/* cari posisi warga di array lewat ID. Kalau tidak ada hasilnya -1 */
int cariWarga(int id) {
    int i;
    for (i = 0; i < jumlahWarga; i++) {
        if (idWarga[i] == id) {
            return i;
        }
    }
    return -1;
}

/* tampilkan daftar semua warga */
void tampilDaftarWarga() {
    int i;
    printf("\nDAFTAR WARGA\n");
    for (i = 0; i < jumlahWarga; i++) {
        printf("ID %d : %s\n", idWarga[i], namaWarga[i]);
    }
}

/* total iuran yang sudah dibayar satu warga di satu bulan */
int totalBayar(int id, int bulan, int tahun) {
    int total = 0;
    int i;
    for (i = 0; i < jumlahTrx; i++) {
        if (jenis[i] == 'M' && trxId[i] == id && trxBulan[i] == bulan && trxTahun[i] == tahun) {
            total = total + trxNominal[i];
        }
    }
    return total;
}

/* hitungTotal('M') = total pemasukan, hitungTotal('K') = total pengeluaran */
int hitungTotal(char j) {
    int total = 0;
    int i;
    for (i = 0; i < jumlahTrx; i++) {
        if (jenis[i] == j) {
            total = total + trxNominal[i];
        }
    }
    return total;
}

/* tampilkan siapa yang sudah lunas dan yang menunggak di satu bulan */
void cekStatus(int bulan, int tahun) {
    int i, bayar, kurang;
    int jumlahBelum = 0;
    int totalTunggakan = 0;

    printf("\nSTATUS IURAN BULAN %d/%d (iuran Rp %d)\n", bulan, tahun, iuran);
    for (i = 0; i < jumlahWarga; i++) {
        bayar = totalBayar(idWarga[i], bulan, tahun);
        if (bayar >= iuran) {
            printf("%s : LUNAS\n", namaWarga[i]);
        } else {
            kurang = iuran - bayar;
            printf("%s : BELUM LUNAS, kurang Rp %d\n", namaWarga[i], kurang);
            totalTunggakan = totalTunggakan + kurang;
            jumlahBelum++;
        }
    }
    printf("Warga yang menunggak : %d orang\n", jumlahBelum);
    printf("Total tunggakan      : Rp %d\n", totalTunggakan);
}

/* simpan semua data ke file */
void simpanData() {
    FILE *f;
    int i;

    f = fopen("data_sikawan.txt", "w");
    if (f == NULL) {
        printf("Gagal menyimpan data!\n");
        return;
    }
    fprintf(f, "%d %d %d %d\n", iuran, idBerikutnya, jumlahWarga, jumlahTrx);
    for (i = 0; i < jumlahWarga; i++) {
        fprintf(f, "%d\n", idWarga[i]);
        fprintf(f, "%s\n", namaWarga[i]);
    }
    for (i = 0; i < jumlahTrx; i++) {
        fprintf(f, "%c %d %d %d %d\n", jenis[i], trxId[i], trxBulan[i], trxTahun[i], trxNominal[i]);
        fprintf(f, "%s\n", trxKet[i]);
    }
    fclose(f);
}

/* baca data dari file (kalau file belum ada, tidak melakukan apa-apa) */
void bacaData() {
    FILE *f;
    char baris[100];
    int i;

    f = fopen("data_sikawan.txt", "r");
    if (f == NULL) {
        return;
    }

    fgets(baris, 100, f);
    sscanf(baris, "%d %d %d %d", &iuran, &idBerikutnya, &jumlahWarga, &jumlahTrx);

    for (i = 0; i < jumlahWarga; i++) {
        fgets(baris, 100, f);
        idWarga[i] = atoi(baris);
        fgets(namaWarga[i], 50, f);
        hapusEnter(namaWarga[i]);
    }

    for (i = 0; i < jumlahTrx; i++) {
        fgets(baris, 100, f);
        sscanf(baris, "%c %d %d %d %d", &jenis[i], &trxId[i], &trxBulan[i], &trxTahun[i], &trxNominal[i]);
        fgets(trxKet[i], 50, f);
        hapusEnter(trxKet[i]);
    }
    fclose(f);
}


/* ===================== MENU 1 : KELOLA DATA WARGA ===================== */

void tambahWarga() {
    char nama[50];

    if (jumlahWarga >= MAX_WARGA) {
        printf("Data warga sudah penuh!\n");
        return;
    }
    bacaTeks("Nama warga: ", nama);
    if (strlen(nama) == 0) {
        printf("Nama tidak boleh kosong!\n");
        return;
    }
    idWarga[jumlahWarga] = idBerikutnya;
    strcpy(namaWarga[jumlahWarga], nama);
    printf("Berhasil! %s punya ID %d\n", nama, idBerikutnya);
    jumlahWarga++;
    idBerikutnya++;
    simpanData();
}

void cariNama() {
    char kata[50];
    int i;
    int ketemu = 0;

    bacaTeks("Masukkan nama yang dicari: ", kata);
    for (i = 0; i < jumlahWarga; i++) {
        if (strstr(namaWarga[i], kata) != NULL) {
            printf("ID %d : %s\n", idWarga[i], namaWarga[i]);
            ketemu++;
        }
    }
    if (ketemu == 0) {
        printf("Warga tidak ditemukan.\n");
    }
}

void ubahWarga() {
    int id, idx;
    char nama[50];

    tampilDaftarWarga();
    id = bacaAngka("ID warga yang diubah: ", 1, 99999);
    idx = cariWarga(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    bacaTeks("Nama baru: ", nama);
    if (strlen(nama) == 0) {
        printf("Nama tidak boleh kosong!\n");
        return;
    }
    strcpy(namaWarga[idx], nama);
    printf("Nama berhasil diubah.\n");
    simpanData();
}

void hapusWarga() {
    int id, idx, i;

    tampilDaftarWarga();
    id = bacaAngka("ID warga yang dihapus: ", 1, 99999);
    idx = cariWarga(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    /* geser data di belakangnya satu langkah ke kiri */
    for (i = idx; i < jumlahWarga - 1; i++) {
        idWarga[i] = idWarga[i + 1];
        strcpy(namaWarga[i], namaWarga[i + 1]);
    }
    jumlahWarga--;
    printf("Warga berhasil dihapus.\n");
    simpanData();
}

void kelolaWarga() {
    int sub;

    do {
        printf("\n--- KELOLA DATA WARGA ---\n");
        printf("1. Tambah warga\n");
        printf("2. Tampilkan semua warga\n");
        printf("3. Cari warga\n");
        printf("4. Ubah nama warga\n");
        printf("5. Hapus warga\n");
        printf("0. Kembali\n");
        sub = bacaAngka("Pilih: ", 0, 5);

        if (sub == 1) {
            tambahWarga();
        } else if (sub == 2) {
            tampilDaftarWarga();
        } else if (sub == 3) {
            cariNama();
        } else if (sub == 4) {
            ubahWarga();
        } else if (sub == 5) {
            hapusWarga();
        }
    } while (sub != 0);
}


/* ===================== MENU 2 : ATUR IURAN ===================== */

void aturIuran() {
    printf("\nIuran sekarang: Rp %d per bulan\n", iuran);
    iuran = bacaAngka("Iuran baru (Rp): ", 1, 10000000);
    printf("Iuran diubah menjadi Rp %d\n", iuran);
    simpanData();
}


/* ===================== MENU 3 : CATAT PEMBAYARAN ===================== */

void catatPembayaran() {
    int id, idx, bulan, tahun, sudah, kurang, nominal;

    printf("\n--- CATAT PEMBAYARAN IURAN ---\n");
    if (jumlahWarga == 0) {
        printf("Belum ada warga. Tambah warga dulu di menu 1.\n");
        return;
    }
    if (jumlahTrx >= MAX_TRX) {
        printf("Data transaksi sudah penuh!\n");
        return;
    }

    tampilDaftarWarga();
    id = bacaAngka("ID warga yang membayar: ", 1, 99999);
    idx = cariWarga(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }

    tahun = bacaAngka("Tahun iuran (contoh 2026): ", 2000, 2100);
    bulan = bacaAngka("Bulan iuran (1-12): ", 1, 12);

    sudah = totalBayar(id, bulan, tahun);
    if (sudah >= iuran) {
        printf("%s sudah LUNAS untuk bulan %d/%d.\n", namaWarga[idx], bulan, tahun);
        return;
    }

    kurang = iuran - sudah;
    printf("%s masih kurang Rp %d\n", namaWarga[idx], kurang);
    nominal = bacaAngka("Jumlah bayar (Rp): ", 1, kurang);

    jenis[jumlahTrx] = 'M';
    trxId[jumlahTrx] = id;
    trxBulan[jumlahTrx] = bulan;
    trxTahun[jumlahTrx] = tahun;
    trxNominal[jumlahTrx] = nominal;
    strcpy(trxKet[jumlahTrx], "-");
    jumlahTrx++;
    simpanData();

    printf("Pembayaran berhasil dicatat.\n");
    if (nominal == kurang) {
        printf("Status: LUNAS\n");
    } else {
        printf("Status: masih kurang Rp %d\n", kurang - nominal);
    }
}


/* ===================== MENU 4 : CEK STATUS ===================== */

void menuStatus() {
    int bulan, tahun;

    printf("\n--- CEK STATUS PEMBAYARAN ---\n");
    tahun = bacaAngka("Tahun (contoh 2026): ", 2000, 2100);
    bulan = bacaAngka("Bulan (1-12): ", 1, 12);
    cekStatus(bulan, tahun);
}


/* ===================== MENU 5 : CATAT PENGELUARAN ===================== */

void catatPengeluaran() {
    int bulan, tahun, saldo, nominal;
    char ket[50];

    printf("\n--- CATAT PENGELUARAN KAS ---\n");
    if (jumlahTrx >= MAX_TRX) {
        printf("Data transaksi sudah penuh!\n");
        return;
    }

    saldo = hitungTotal('M') - hitungTotal('K');
    printf("Saldo kas sekarang: Rp %d\n", saldo);
    if (saldo <= 0) {
        printf("Saldo kas kosong, pengeluaran tidak bisa dicatat.\n");
        return;
    }

    bacaTeks("Keterangan (contoh: Kebersihan): ", ket);
    if (strlen(ket) == 0) {
        printf("Keterangan tidak boleh kosong!\n");
        return;
    }
    nominal = bacaAngka("Nominal pengeluaran (Rp): ", 1, saldo);
    tahun = bacaAngka("Tahun (contoh 2026): ", 2000, 2100);
    bulan = bacaAngka("Bulan (1-12): ", 1, 12);

    jenis[jumlahTrx] = 'K';
    trxId[jumlahTrx] = 0;
    trxBulan[jumlahTrx] = bulan;
    trxTahun[jumlahTrx] = tahun;
    trxNominal[jumlahTrx] = nominal;
    strcpy(trxKet[jumlahTrx], ket);
    jumlahTrx++;
    simpanData();

    printf("Pengeluaran berhasil dicatat.\n");
}


/* ===================== MENU 6 : LIHAT SALDO ===================== */

void lihatSaldo() {
    int masuk = hitungTotal('M');
    int keluar = hitungTotal('K');

    printf("\nTotal pemasukan   : Rp %d\n", masuk);
    printf("Total pengeluaran : Rp %d\n", keluar);
    printf("SALDO KAS         : Rp %d\n", masuk - keluar);
}


/* ===================== MENU 7 : RIWAYAT TRANSAKSI ===================== */

void riwayat() {
    int i, idx;

    printf("\n--- RIWAYAT TRANSAKSI ---\n");
    if (jumlahTrx == 0) {
        printf("Belum ada transaksi.\n");
        return;
    }

    for (i = 0; i < jumlahTrx; i++) {
        printf("%d. ", i + 1);
        if (jenis[i] == 'M') {
            idx = cariWarga(trxId[i]);
            printf("MASUK, bulan %d/%d, Rp %d, iuran ", trxBulan[i], trxTahun[i], trxNominal[i]);
            if (idx == -1) {
                printf("(warga sudah dihapus)\n");
            } else {
                printf("%s\n", namaWarga[idx]);
            }
        } else {
            printf("KELUAR, bulan %d/%d, Rp %d, %s\n", trxBulan[i], trxTahun[i], trxNominal[i], trxKet[i]);
        }
    }
}


/* ===================== MENU 8 : LAPORAN KEUANGAN ===================== */

void laporan() {
    int bulan, tahun, i;
    int masuk = 0;
    int keluar = 0;

    printf("\n--- LAPORAN KEUANGAN BULANAN ---\n");
    tahun = bacaAngka("Tahun (contoh 2026): ", 2000, 2100);
    bulan = bacaAngka("Bulan (1-12): ", 1, 12);

    for (i = 0; i < jumlahTrx; i++) {
        if (trxBulan[i] == bulan && trxTahun[i] == tahun) {
            if (jenis[i] == 'M') {
                masuk = masuk + trxNominal[i];
            } else {
                keluar = keluar + trxNominal[i];
            }
        }
    }

    printf("\n===== LAPORAN BULAN %d/%d =====\n", bulan, tahun);
    printf("Pemasukan bulan ini   : Rp %d\n", masuk);
    printf("Pengeluaran bulan ini : Rp %d\n", keluar);
    printf("Selisih bulan ini     : Rp %d\n", masuk - keluar);
    printf("Saldo kas keseluruhan : Rp %d\n", hitungTotal('M') - hitungTotal('K'));
    cekStatus(bulan, tahun);
}


/* ===================== PROGRAM UTAMA ===================== */

int main() {
    int pilih;

    bacaData();

    do {
        printf("\n=========================================\n");
        printf("  SIKAWAN - Sistem Informasi Keuangan Warga\n");
        printf("=========================================\n");
        printf("1. Kelola data warga\n");
        printf("2. Atur nominal iuran\n");
        printf("3. Catat pembayaran iuran\n");
        printf("4. Cek status pembayaran & tunggakan\n");
        printf("5. Catat pengeluaran kas\n");
        printf("6. Lihat saldo kas\n");
        printf("7. Riwayat transaksi\n");
        printf("8. Laporan keuangan\n");
        printf("9. Keluar\n");
        pilih = bacaAngka("Pilih menu (1-9): ", 1, 9);

        switch (pilih) {
            case 1: kelolaWarga(); break;
            case 2: aturIuran(); break;
            case 3: catatPembayaran(); break;
            case 4: menuStatus(); break;
            case 5: catatPengeluaran(); break;
            case 6: lihatSaldo(); break;
            case 7: riwayat(); break;
            case 8: laporan(); break;
            case 9:
                simpanData();
                printf("\nData tersimpan. Terima kasih!\n");
                break;
        }
    } while (pilih != 9);

    return 0;
}
