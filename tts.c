#include <stdio.h>
#include <stdlib.h>

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
    char ulang;

    do {
        bersihkanLayar();

        printf("=============================================\n");
        printf("     SISTEM MANAJEMEN DATA RUMAH SAKIT\n");
        printf("=============================================\n");
        printf("1. Input Data Pasien\n");
        printf("2. Input Data Dokter\n");
        printf("3. Input Data Diagnosa\n");
        printf("4. Tampilkan Semua Data\n");
        printf("5. Keluar\n");
        printf("=============================================\n");
        printf("Pilih menu (1-5): ");
        scanf("%d", &pilihan);
        getchar();

        printf("\n");

        switch (pilihan) {
            case 1:
                printf(">> INPUT DATA PASIEN\n");
                inputPasien(&data_pasien);
                break;
            case 2:
                printf(">> INPUT DATA DOKTER\n");
                inputDokter(&data_dokter);
                break;
            case 3:
                printf(">> INPUT DATA DIAGNOSA\n");
                inputDiagnosa(&diagnosa);
                break;
            case 4:
                printf(">> TAMPILKAN DATA LENGKAP\n");
                tampilkanData(data_pasien, data_dokter, diagnosa);
                break;
            case 5:
                do {
                    printf("Apakah kamu ingin menginput data lagi? (y/t): ");
                    scanf(" %c", &ulang);
                    getchar();
                    if (ulang != 'y' && ulang != 't') {
                        printf("Masukkan input yang benar! (y/t)\n");
                    }
                } while (ulang != 'y' && ulang != 't');
                if (ulang == 't') {
                    printf("\nTerima kasih! Program selesai.\n");
                    return 0;
                }
                break;
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

    printf("\n[INFO] Data pasien berhasil disimpan!\n");
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

    printf("\n[INFO] Data dokter berhasil disimpan!\n");
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

    printf("\n[INFO] Data diagnosa berhasil disimpan!\n");
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