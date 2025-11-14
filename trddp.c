#include <stdio.h>
    #include <stdlib.h>
    #include <direct.h>
    #include <time.h>
    #include <string.h>

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
    void  tampilkanDariFile();
    void  cetakStruk();
    void  simpanData(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa);
    void  simpanPDF(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa);
    void  editData();
    void  hapusData();

    static void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    int inputInt(const char *pesan) {
        int x;
        while (1) {
            printf("%s", pesan);
            if (scanf("%d", &x) == 1) {
                getchar();
                return x;
            } else {
                printf("[PERINGATAN] Input tidak valid! Masukkan angka yang benar.\n");
                while (getchar() != '\n');
            }
        }
    }

    int main() {
        struct Pasien   data_pasien = {0};
        struct Dokter   data_dokter = {0};
        struct Diagnosa diagnosa    = {0};

        int pilihan;
        int adaPasien = 0, adaDokter = 0;

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
            printf("6. Simpan ke File PDF\n");
            printf("7. Edit Data Berdasarkan ID\n");
            printf("8. Hapus Data Berdasarkan ID\n");
            printf("9. Keluar\n");
            printf("=============================================\n");

            pilihan = inputInt("Pilih menu (1-9): ");

            switch (pilihan) {
                case 1:
                    inputPasien(&data_pasien);
                    adaPasien = 1;
                    break;
                case 2:
                    inputDokter(&data_dokter);
                    adaDokter = 1;
                    break;
                case 3:
                    if (!adaPasien || !adaDokter) {
                        printf("[PERINGATAN] Harap input data pasien dan dokter terlebih dahulu!\n");
                        break;
                    }
                    inputDiagnosa(&diagnosa);
                    simpanData(data_pasien, data_dokter, diagnosa);
                    break;
                case 4:
                    tampilkanDariFile();
                    break;
                case 5:
                    cetakStruk();
                    break;
                case 6:
                    simpanPDF(data_pasien, data_dokter, diagnosa);
                    break;
                case 7:
                    editData();
                    break;
                case 8:
                    hapusData();
                    break;
                case 9:
                    printf("\nTerima kasih! Program selesai.\n");
                    return 0;
                default:
                    printf("[PERINGATAN] Pilihan tidak valid! Masukkan angka 1-9.\n");
            }

            printf("\nTekan ENTER untuk kembali ke menu...");
            getchar();

        } while (1);
    }

    void inputPasien(struct Pasien *data_pasien) {
        data_pasien->id = inputInt("ID Pasien        : ");
        printf("Nama Pasien      : ");
        scanf("%[^\n]", data_pasien->nama); getchar();
        data_pasien->umur = inputInt("Umur Pasien      : ");
        printf("Alamat Pasien    : ");
        scanf("%[^\n]", data_pasien->alamat); getchar();
        printf("\n[INFO] Data pasien berhasil diinput!\n");
    }

    void inputDokter(struct Dokter *data_dokter) {
        data_dokter->id = inputInt("ID Dokter        : ");
        printf("Nama Dokter      : ");
        scanf("%[^\n]", data_dokter->nama); getchar();
        printf("Spesialis        : ");
        scanf("%[^\n]", data_dokter->spesialis); getchar();
        printf("Tarif Jasa Dokter: Rp ");
        scanf("%f", &data_dokter->tarif); getchar();
        printf("\n[INFO] Data dokter berhasil diinput!\n");
    }

    void inputDiagnosa(struct Diagnosa *diagnosa) {
        diagnosa->id_pasien = inputInt("ID Pasien (sesuai data): ");
        diagnosa->id_dokter = inputInt("ID Dokter (sesuai data): ");
        printf("Nama Penyakit           : ");
        scanf("%[^\n]", diagnosa->penyakit); getchar();
        printf("Biaya Obat (Rp)         : ");
        scanf("%f", &diagnosa->biaya_obat); getchar();
        printf("Biaya Rawat (Rp)        : ");
        scanf("%f", &diagnosa->biaya_rawat); getchar();
        printf("\n[INFO] Data diagnosa berhasil diinput!\n");
    }

    float hitungBiaya(struct Dokter data_dokter, struct Diagnosa diagnosa) {
        return data_dokter.tarif + diagnosa.biaya_obat + diagnosa.biaya_rawat;
    }

    void simpanData(struct Pasien p, struct Dokter d, struct Diagnosa diag) {
        if (p.id == 0 || d.id == 0) {
            printf("[ERROR] Data pasien atau dokter belum lengkap!\n");
            return;
        }

        _mkdir("C:\\TTS_DDP");
        FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "a");
        if (!file) {
            printf("[ERROR] Gagal membuka file!\n");
            return;
        }
        fprintf(file, "==============================================================\n");
        fprintf(file, "DATA PASIEN\n");
        fprintf(file, "ID Pasien       : %d\n", p.id);
        fprintf(file, "Nama Pasien     : %s\n", p.nama);
        fprintf(file, "Umur Pasien     : %d\n", p.umur);
        fprintf(file, "Alamat Pasien   : %s\n\n", p.alamat);
        fprintf(file, "==============================================================\n");
        fprintf(file, "DATA DOKTER\n");
        fprintf(file, "ID Dokter       : %d\n", d.id);
        fprintf(file, "Nama Dokter     : %s\n", d.nama);
        fprintf(file, "Spesialis       : %s\n", d.spesialis);
        fprintf(file, "Tarif Dokter    : Rp %.2f\n", d.tarif);
        fprintf(file, "Biaya Obat      : Rp %.2f\n", diag.biaya_obat);
        fprintf(file, "Biaya Rawat     : Rp %.2f\n", diag.biaya_rawat);
        fprintf(file, "--------------------------------------------------------------\n");
        fprintf(file, "TOTAL BIAYA     : Rp %.2f\n", hitungBiaya(d, diag));

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(file, "Tanggal Input   : %02d/%02d/%d\n",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
        fprintf(file, "==============================================================\n\n");

        fclose(file);
        printf("[INFO] Data otomatis tersimpan ke file TXT!\n");
    }

    void tampilkanDariFile() {
        FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
        if (!file) {
            printf("[ERROR] File data tidak ditemukan!\n");
            return;
        }

        printf("=====================================================================================================================\n");
        printf("                                             DAFTAR DATA RUMAH SAKIT                                                \n");
        printf("=====================================================================================================================\n");
        printf("| %-5s | %-20s | %-3s | %-20s | %-20s | %-12s | %-12s | %-12s |\n",
            "ID", "Nama Pasien", "Umr", "Dokter", "Spesialis", "Obat (Rp)", "Rawat (Rp)", "Total (Rp)");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        int id_pasien, umur, id_dokter;
        char nama_pasien[50], alamat[100];
        char nama_dokter[50], spesialis[50];
        float tarif, biaya_obat, biaya_rawat, total;

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "ID Pasien")) {
                sscanf(line, "ID Pasien       : %d", &id_pasien);
            } else if (strstr(line, "Nama Pasien")) {
                sscanf(line, "Nama Pasien     : %[^\n]", nama_pasien);
            } else if (strstr(line, "Umur Pasien")) {
                sscanf(line, "Umur Pasien     : %d", &umur);
            } else if (strstr(line, "ID Dokter")) {
                sscanf(line, "ID Dokter       : %d", &id_dokter);
            } else if (strstr(line, "Nama Dokter")) {
                sscanf(line, "Nama Dokter     : %[^\n]", nama_dokter);
            } else if (strstr(line, "Spesialis")) {
                sscanf(line, "Spesialis       : %[^\n]", spesialis);
            } else if (strstr(line, "Tarif Dokter")) {
                sscanf(line, "Tarif Dokter    : Rp %f", &tarif);
            } else if (strstr(line, "Biaya Obat")) {
                sscanf(line, "Biaya Obat      : Rp %f", &biaya_obat);
            } else if (strstr(line, "Biaya Rawat")) {
                sscanf(line, "Biaya Rawat     : Rp %f", &biaya_rawat);
            } else if (strstr(line, "TOTAL BIAYA")) {
                sscanf(line, "TOTAL BIAYA     : Rp %f", &total);

            
                printf("| %-5d | %-20s | %-3d | %-20s | %-20s | %-12.2f | %-12.2f | %-12.2f |\n",
                    id_pasien, nama_pasien, umur, nama_dokter, spesialis,
                    biaya_obat, biaya_rawat, total);
            }
        }

        printf("=====================================================================================================================\n");

        fclose(file);
    }


    void simpanPDF(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa) {
        FILE *cek = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
        if (!cek) {
            printf("[ERROR] File TXT belum ada! Harap input data dulu.\n");
            return;
        }
        fclose(cek);

        system("powershell -Command \""
            "$word = New-Object -ComObject Word.Application; "
            "$doc = $word.Documents.Open('C:\\\\TTS_DDP\\\\data_rumahsakit_ddp_temp.txt'); "
            "$pdfPath = 'C:\\\\TTS_DDP\\\\data_rumahsakit_ddp.pdf'; "
            "$doc.SaveAs([ref]$pdfPath, [ref]17); "
            "$doc.Close(); "
            "$word.Quit();\"");

        printf("\n[INFO] File PDF berhasil dibuat!\n");
    }

    void editData() {
        struct Pasien p;
        struct Dokter d;
        struct Diagnosa dg;

        FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
        if (!file) {
            printf("[ERROR] File data tidak ditemukan!\n");
            return;
        }

        int idEdit = inputInt("\nMasukkan ID pasien yang ingin diedit: ");
        char cariID[40];
        sprintf(cariID, "ID Pasien       : %d", idEdit);

        FILE *temp = fopen("C:\\TTS_DDP\\temp_edit.txt", "w");
        if (!temp) {
            printf("[ERROR] Gagal membuat file sementara!\n");
            fclose(file);
            return;
        }

        char line[512];
        int found = 0;
        int skip = 0;

        while (fgets(line, sizeof(line), file)) {
            if (!found && strstr(line, cariID)) {
                found = 1;
                skip = 1;

                printf("\nDitemukan data pasien dengan ID %d. Silakan input data baru!\n", idEdit);
                inputPasien(&p);
                inputDokter(&d);
                inputDiagnosa(&dg);

                float total = hitungBiaya(d, dg);
                time_t now = time(NULL);
                char waktuSimpan[40];
                strftime(waktuSimpan, sizeof(waktuSimpan), "%d/%m/%Y", localtime(&now));

                fprintf(temp,
                    "==============================================================\n\n"
                    "STRUK PEMBAYARAN RUMAH SAKIT\n"
                    "==============================================================\n\n"
                    "DATA PASIEN\n"
                "ID Pasien       : %d\n"
                    "Nama Pasien     : %s\n"
                    "Umur Pasien     : %d\n"
                    "Alamat Pasien   : %s\n\n"
                    "DATA DOKTER\n"
                    "ID Dokter       : %d\n"
                    "Nama Dokter     : %s\n"
                    "Spesialis       : %s\n"
                    "Tarif Dokter    : Rp %.2f\n"
                    "Biaya Obat      : Rp %.2f\n"
                    "Biaya Rawat     : Rp %.2f\n"
                    "--------------------------------------------------------------\n"
                    "TOTAL BIAYA     : Rp %.2f\n"
                    "Tanggal Cetak   : %s\n"
                    "==============================================================\n\n",
                    p.id, p.nama, p.umur, p.alamat,
                    d.id, d.nama, d.spesialis,
                    d.tarif, dg.biaya_obat, dg.biaya_rawat,
                    total, waktuSimpan
                );

                continue;
            }

            if (skip) {
                if (strstr(line, "==============================================================")) {
                    skip = 0;
                }
                continue;
            }

            fputs(line, temp);
        }

        fclose(file);
        fclose(temp);

        if (!found) {
            remove("C:\\TTS_DDP\\temp_edit.txt");
            printf("\n[INFO] Tidak ditemukan data dengan ID tersebut!!\n");
            return;
        }

        remove("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt");
        rename("C:\\TTS_DDP\\temp_edit.txt", "C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt");

        printf("\n[INFO] Data pasien dengan ID %d berhasil diperbaharui!\n", idEdit);
    }

void cetakStruk() {
    FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
    if (!file) {
        printf("[ERROR] File data tidak ditemukan!\n");
        return;
    }

    char line[256];
    int id_pasien = 0, umur = 0, id_dokter = 0;
    char nama_pasien[50] = "", alamat[100] = "";
    char nama_dokter[50] = "", spesialis[50] = "", penyakit[100] = "";
    float tarif = 0, biaya_obat = 0, biaya_rawat = 0, total = 0;
    int found = 0;

    printf("\n==============================================================\n");
    printf("                 STRUK PEMBAYARAN RUMAH SAKIT\n");
    printf("==============================================================\n");

   
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("Tanggal Cetak   : %02d/%02d/%d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    printf("==============================================================\n\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "ID Pasien")) sscanf(line, "ID Pasien       : %d", &id_pasien);
        else if (strstr(line, "Nama Pasien")) sscanf(line, "Nama Pasien     : %[^\n]", nama_pasien);
        else if (strstr(line, "Umur Pasien")) sscanf(line, "Umur Pasien     : %d", &umur);
        else if (strstr(line, "Alamat Pasien")) sscanf(line, "Alamat Pasien   : %[^\n]", alamat);
        else if (strstr(line, "ID Dokter")) sscanf(line, "ID Dokter       : %d", &id_dokter);
        else if (strstr(line, "Nama Dokter")) sscanf(line, "Nama Dokter     : %[^\n]", nama_dokter);
        else if (strstr(line, "Spesialis")) sscanf(line, "Spesialis       : %[^\n]", spesialis);
        else if (strstr(line, "Biaya Obat")) sscanf(line, "Biaya Obat      : Rp %f", &biaya_obat);
        else if (strstr(line, "Biaya Rawat")) sscanf(line, "Biaya Rawat     : Rp %f", &biaya_rawat);
        else if (strstr(line, "Tarif Dokter")) sscanf(line, "Tarif Dokter    : Rp %f", &tarif);
        else if (strstr(line, "TOTAL BIAYA")) {
            sscanf(line, "TOTAL BIAYA     : Rp %f", &total);


            found = 1;
            printf("DATA PASIEN\n");
            printf("ID Pasien       : %d\n", id_pasien);
            printf("Nama Pasien     : %s\n", nama_pasien);
            printf("Umur            : %d\n", umur);
            printf("Alamat          : %s\n\n", alamat);

            printf("DATA DOKTER\n");
            printf("ID Dokter       : %d\n", id_dokter);
            printf("Nama Dokter     : %s\n", nama_dokter);
            printf("Spesialis       : %s\n", spesialis);
            printf("Tarif Dokter    : Rp %.2f\n\n", tarif);

            printf("DATA DIAGNOSA\n");
            printf("Biaya Obat      : Rp %.2f\n", biaya_obat);
            printf("Biaya Rawat     : Rp %.2f\n", biaya_rawat);
            printf("--------------------------------------------------------------\n");
            printf("TOTAL BIAYA     : Rp %.2f\n", total);
            printf("==============================================================\n\n");
        }
    }

    if (!found)
        printf("[INFO] Tidak ada data untuk dicetak!\n");

    fclose(file);
}


void hapusData() {
    FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
    if (!file) {
        printf("[ERROR] File data tidak ditemukan!\n");
        return;
    }

    int idHapus = inputInt("\nMasukkan ID Pasien yang ingin dihapus: ");
    FILE *temp = fopen("C:\\TTS_DDP\\temp_hapus.txt", "w");
    if (!temp) {
        printf("[ERROR] Gagal membuat file sementara!\n");
        fclose(file);
        return;
    }

    char line[512];
    int found = 0;
    int skipBlock = 0;

    while (fgets(line, sizeof(line), file)) {
       
        if (strstr(line, "ID Pasien")) {
            int id;
            sscanf(line, "ID Pasien       : %d", &id);
            if (id == idHapus) {
                found = 1;
                skipBlock = 1; 
                continue;
            }
        }

   
        if (skipBlock) {
            if (strstr(line, "==============================================================")) {
                skipBlock = 0; 
            }
            continue;
        }

      
        fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        remove("C:\\TTS_DDP\\temp_hapus.txt");
        printf("\n[INFO] Tidak ditemukan data dengan ID %d.\n", idHapus);
    } else {
        remove("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt");
        rename("C:\\TTS_DDP\\temp_hapus.txt", "C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt");
        printf("\n[INFO] Semua data pasien dengan ID %d berhasil dihapus!\n", idHapus);
    }
}
