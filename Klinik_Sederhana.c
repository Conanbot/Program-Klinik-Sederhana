#include <stdio.h>
#include <stdlib.h>
#include <direct.h>  

struct Pasien {
    int  id;
    char nama[50];
    int  umur;
    char alamat[100];
};

struct Dokter {
    int   id;
    char  nama[50];
    char  spesialis[50];
    float tarif;
};

struct Diagnosa {
    int   id_pasien;
    int   id_dokter;
    char  penyakit[100];
    float biaya_obat;
    float biaya_rawat;
};

void  inputPasien(struct Pasien *data_pasien);
void  inputDokter(struct Dokter *data_dokter);
void  inputDiagnosa(struct Diagnosa *diagnosa);
float hitungBiaya(struct Dokter data_dokter, struct Diagnosa diagnosa);
void  tampilkanData(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa);
void  cetakStruk(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa);
void  simpanData(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa);

static void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    struct Pasien   data_pasien = {0};
    struct Dokter   data_dokter = {0};
    struct Diagnosa diagnosa    = {0};
    int pilihan;

    do {
        bersihkanLayar();
        printf("=============================================\n");
        printf("     SISTEM MANAJEMEN DATA RUMAH SAKIT\n");
        printf("=============================================\n");
        printf("1. Input Data Pasien\n");
        printf("2. Input Data Dokter\n");
        printf("3. Input Data Diagnosa\n");
        printf("4. Tampilkan Semua Data\n");
        printf("5. Cetak Struk Pembayaran\n");
        printf("6. Simpan ke File\n");
        printf("7. Keluar\n");
        printf("=============================================\n");
        printf("Pilih menu (1-7): ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                inputPasien(&data_pasien);
                break;
            case 2:
                inputDokter(&data_dokter);
                break;
            case 3:
                inputDiagnosa(&diagnosa);
                break;
            case 4:
                tampilkanData(data_pasien, data_dokter, diagnosa);
                break;
            case 5:
                cetakStruk(data_pasien, data_dokter, diagnosa);
                break;
            case 6:
                simpanData(data_pasien, data_dokter, diagnosa);
                break;
            case 7:
                printf("\nTerima kasih! Program selesai.\n");
                return 0;
            default:
                printf("[PERINGATAN] Pilihan tidak valid!\n");
        }

        printf("\nTekan ENTER untuk kembali ke menu...");
        getchar();

    } while (1);

    return 0;
}

void inputPasien(struct Pasien *data_pasien) {
    printf("ID Pasien        : ");
    scanf("%d", &data_pasien->id);
    getchar();

    printf("Nama Pasien      : ");
    scanf("%[^\n]", data_pasien->nama);
    getchar();

    printf("Umur Pasien      : ");
    scanf("%d", &data_pasien->umur);
    getchar();

    printf("Alamat Pasien    : ");
    scanf("%[^\n]", data_pasien->alamat);
    getchar();

    printf("\n[INFO] Data pasien berhasil disimpan sementara!\n");
}

void inputDokter(struct Dokter *data_dokter) {
    printf("ID Dokter        : ");
    scanf("%d", &data_dokter->id);
    getchar();

    printf("Nama Dokter      : ");
    scanf("%[^\n]", data_dokter->nama);
    getchar();

    printf("Spesialis        : ");
    scanf("%[^\n]", data_dokter->spesialis);
    getchar();

    printf("Tarif Jasa Dokter: Rp ");
    scanf("%f", &data_dokter->tarif);
    getchar();

    printf("\n[INFO] Data dokter berhasil disimpan sementara!\n");
}

void inputDiagnosa(struct Diagnosa *diagnosa) {
    printf("ID Pasien (sesuai data): ");
    scanf("%d", &diagnosa->id_pasien);
    getchar();

    printf("ID Dokter (sesuai data): ");
    scanf("%d", &diagnosa->id_dokter);
    getchar();

    printf("Nama Penyakit           : ");
    scanf("%[^\n]", diagnosa->penyakit);
    getchar();

    printf("Biaya Obat (Rp)         : ");
    scanf("%f", &diagnosa->biaya_obat);
    getchar();

    printf("Biaya Rawat (Rp)        : ");
    scanf("%f", &diagnosa->biaya_rawat);
    getchar();

    printf("\n[INFO] Data diagnosa berhasil disimpan sementara!\n");
}

float hitungBiaya(struct Dokter data_dokter, struct Diagnosa diagnosa) {
    return data_dokter.tarif + diagnosa.biaya_obat + diagnosa.biaya_rawat;
}

void tampilkanData(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa) {
    float total = hitungBiaya(data_dokter, diagnosa);
    printf("\n----------- DATA PASIEN -----------\n");
    printf("ID Pasien : %d\n", data_pasien.id);
    printf("Nama      : %s\n", data_pasien.nama);
    printf("Umur      : %d\n", data_pasien.umur);
    printf("Alamat    : %s\n", data_pasien.alamat);

    printf("\n----------- DATA DOKTER -----------\n");
    printf("ID Dokter : %d\n", data_dokter.id);
    printf("Nama      : %s\n", data_dokter.nama);
    printf("Spesialis : %s\n", data_dokter.spesialis);
    printf("Tarif     : Rp %.2f\n", data_dokter.tarif);

    printf("\n----------- DATA DIAGNOSA -----------\n");
    printf("Penyakit    : %s\n", diagnosa.penyakit);
    printf("Biaya Obat  : Rp %.2f\n", diagnosa.biaya_obat);
    printf("Biaya Rawat : Rp %.2f\n", diagnosa.biaya_rawat);

    printf("\n=============================================\n");
    printf(">> TOTAL BIAYA PENGOBATAN : Rp %.2f\n", total);
    printf("=============================================\n");
}

void cetakStruk(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa) {
    float total = hitungBiaya(data_dokter, diagnosa);
    printf("\n=============================================\n");
    printf("         STRUK PEMBAYARAN RUMAH SAKIT\n");
    printf("=============================================\n");
    printf("ID Pasien : %d\n", data_pasien.id);
    printf("Nama      : %s\n", data_pasien.nama);
    printf("Umur      : %d tahun\n", data_pasien.umur);
    printf("Alamat    : %s\n", data_pasien.alamat);
    printf("---------------------------------------------\n");
    printf("Dokter    : %s (%s)\n", data_dokter.nama, data_dokter.spesialis);
    printf("Penyakit  : %s\n", diagnosa.penyakit);
    printf("---------------------------------------------\n");
    printf("Tarif Dokter  : Rp %10.2f\n", data_dokter.tarif);
    printf("Biaya Obat    : Rp %10.2f\n", diagnosa.biaya_obat);
    printf("Biaya Rawat   : Rp %10.2f\n", diagnosa.biaya_rawat);
    printf("---------------------------------------------\n");
    printf("TOTAL BIAYA   : Rp %10.2f\n", total);
    printf("=============================================\n");
    printf("     TERIMA KASIH ATAS KEPERCAYAAN ANDA\n");
    printf("=============================================\n");
}

void simpanData(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa) {
    _mkdir("C:\\TTS_DDP");

    FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp.txt", "a");

    if (file == NULL) {
        printf("[ERROR] Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    float total = hitungBiaya(data_dokter, diagnosa);
    fprintf(file, "=============================================\n");
    fprintf(file, "DATA PASIEN ID: %d\n", data_pasien.id);
    fprintf(file, "Nama: %s | Umur: %d | Alamat: %s\n", data_pasien.nama, data_pasien.umur, data_pasien.alamat);
    fprintf(file, "Dokter: %s (%s)\n", data_dokter.nama, data_dokter.spesialis);
    fprintf(file, "Penyakit: %s\n", diagnosa.penyakit);
    fprintf(file, "Tarif Dokter: Rp %.2f | Biaya Obat: Rp %.2f | Biaya Rawat: Rp %.2f\n",
            data_dokter.tarif, diagnosa.biaya_obat, diagnosa.biaya_rawat);
    fprintf(file, "TOTAL: Rp %.2f\n", total);
    fprintf(file, "=============================================\n\n");
    fclose(file);

    printf("\n[INFO] Data berhasil disimpan ke folder C:\\TTS_DDP\\data_rumahsakit_ddp.txt\n");
}

