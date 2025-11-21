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
void  inputData(struct Pasien *p, struct Dokter *d, struct Diagnosa *dg);
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
        if (scanf("%d", &x) == 1) { getchar(); return x; }
        printf("[PERINGATAN] Input tidak valid! Masukkan angka yang benar.\n");
        while (getchar() != '\n');
    }
}

/* =======================================================
   FUNGSI UTAMA INPUT DATA (GABUNGAN PASIEN+DOKTER+DIAGNOSA)
   ======================================================= */
void inputData(struct Pasien *p, struct Dokter *d, struct Diagnosa *dg) {
    printf("\n=== INPUT DATA PASIEN, DOKTER, DAN DIAGNOSA ===\n");

    inputPasien(p);
    inputDokter(d);
    inputDiagnosa(dg);

    dg->id_pasien = p->id;
    dg->id_dokter = d->id;

    simpanData(*p, *d, *dg);

    printf("\n[INFO] Semua data berhasil diinput dan otomatis disimpan ke file!\n");
}

/* ============================
           MAIN PROGRAM
   ============================ */
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
        printf("1. Input Data (Pasien + Dokter + Diagnosa)\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Cetak Struk Pembayaran\n");
        printf("4. Simpan ke File PDF\n");
        printf("5. Edit Data Berdasarkan ID\n");
        printf("6. Hapus Data Berdasarkan ID\n");
        printf("7. Keluar\n");
        printf("=============================================\n");

        pilihan = inputInt("Pilih menu (1-7): ");

        switch (pilihan) {
            case 1:
                inputData(&data_pasien, &data_dokter, &diagnosa);
                break;
            case 2:
                tampilkanDariFile();
                break;
            case 3:
                cetakStruk();
                break;
            case 4:
                simpanPDF(data_pasien, data_dokter, diagnosa);
                break;
            case 5:
                editData();
                break;
            case 6:
                hapusData();
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
}

/* ============================
        FUNGSI INPUT DETAIL
   ============================ */
void inputPasien(struct Pasien *data_pasien) {
    data_pasien->id = inputInt("ID Pasien        : ");
    printf("Nama Pasien      : ");
    fgets(data_pasien->nama, sizeof(data_pasien->nama), stdin);
    data_pasien->nama[strcspn(data_pasien->nama, "\n")] = 0;
    data_pasien->umur = inputInt("Umur Pasien      : ");
    printf("Alamat Pasien    : ");
    fgets(data_pasien->alamat, sizeof(data_pasien->alamat), stdin);
    data_pasien->alamat[strcspn(data_pasien->alamat, "\n")] = 0;
}

void inputDokter(struct Dokter *data_dokter) {
    data_dokter->id = inputInt("ID Dokter        : ");
    printf("Nama Dokter      : ");
    fgets(data_dokter->nama, sizeof(data_dokter->nama), stdin);
    data_dokter->nama[strcspn(data_dokter->nama, "\n")] = 0;
    printf("Spesialis        : ");
    fgets(data_dokter->spesialis, sizeof(data_dokter->spesialis), stdin);
    data_dokter->spesialis[strcspn(data_dokter->spesialis, "\n")] = 0;
    printf("Tarif Jasa Dokter: Rp. ");
    scanf("%f", &data_dokter->tarif);
    getchar();
}

void inputDiagnosa(struct Diagnosa *diagnosa) {
    printf("Nama Penyakit           : ");
    fgets(diagnosa->penyakit, sizeof(diagnosa->penyakit), stdin);
    diagnosa->penyakit[strcspn(diagnosa->penyakit, "\n")] = 0;
    printf("Biaya Obat              : Rp. "); scanf("%f", &diagnosa->biaya_obat); getchar();
    printf("Biaya Rawat             : Rp. "); scanf("%f", &diagnosa->biaya_rawat); getchar();
}

/* ============================
     SIMPAN DATA KE FILE TXT
   ============================ */
float hitungBiaya(struct Dokter d, struct Diagnosa g) {
    return d.tarif + g.biaya_obat + g.biaya_rawat;
}

void simpanData(struct Pasien p, struct Dokter d, struct Diagnosa diag) {

    _mkdir("C:\\TTS_DDP");
    FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "a");

    fprintf(file, "==============================================================\n");
    fprintf(file, "=========================DATA PASIEN===========================\n");
    fprintf(file, "ID Pasien       : %d\n", p.id);
    fprintf(file, "Nama Pasien     : %s\n", p.nama);
    fprintf(file, "Umur Pasien     : %d\n", p.umur);
    fprintf(file, "Alamat Pasien   : %s\n\n", p.alamat);

    fprintf(file, "=========================DATA DOKTER===========================\n");
    fprintf(file, "ID Dokter       : %d\n", d.id);
    fprintf(file, "Nama Dokter     : %s\n", d.nama);
    fprintf(file, "Spesialis       : %s\n", d.spesialis);
    fprintf(file, "Tarif Dokter    : Rp %.2f\n", d.tarif);

    fprintf(file, "========================DATA DIAGNOSA==========================\n");
    fprintf(file, "Penyakit        : %s\n", diag.penyakit);
    fprintf(file, "Biaya Obat      : Rp %.2f\n", diag.biaya_obat);
    fprintf(file, "Biaya Rawat     : Rp %.2f\n", diag.biaya_rawat);
    fprintf(file, "--------------------------------------------------------------\n");

    fprintf(file, "TOTAL BIAYA     : Rp %.2f\n", hitungBiaya(d, diag));

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(file, "Tanggal Input   : %02d/%02d/%d\n\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    fclose(file);
}

/* ============================
        TAMPILKAN DATA
   ============================ */
void tampilkanDariFile() {
    FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
    if (!file) {
        printf("[ERROR] File data tidak ditemukan!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

/* ============================
         CETAK STRUK
   ============================ */
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

    // Tanggal Cetak
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
        else if (strstr(line, "Penyakit")) sscanf(line, "Penyakit       : %[^\n]", penyakit);
        else if (strstr(line, "Biaya Obat")) sscanf(line, "Biaya Obat      : Rp %f", &biaya_obat);
        else if (strstr(line, "Biaya Rawat")) sscanf(line, "Biaya Rawat     : Rp %f", &biaya_rawat);
        else if (strstr(line, "Tarif Dokter")) sscanf(line, "Tarif Dokter    : Rp %f", &tarif);
        else if (strstr(line, "TOTAL BIAYA")) {
            sscanf(line, "TOTAL BIAYA     : Rp %f", &total);

            // Setelah total ditemukan → tampilkan 1 struk pasien
            found = 1;
            printf("=========================DATA PASIEN===========================\n");
            printf("ID Pasien       : %d\n", id_pasien);
            printf("Nama Pasien     : %s\n", nama_pasien);
            printf("Umur            : %d\n", umur);
            printf("Alamat          : %s\n\n", alamat);

            printf("=========================DATA DOKTER===========================\n");
            printf("ID Dokter       : %d\n", id_dokter);
            printf("Nama Dokter     : %s\n", nama_dokter);
            printf("Spesialis       : %s\n", spesialis);
            printf("Tarif Dokter    : Rp %.2f\n\n", tarif);

            printf("========================DATA DIAGNOSA==========================\n");
            printf("Penyakit        : %s\n", penyakit);
            printf("Biaya Obat      : Rp %.2f\n", biaya_obat);
            printf("Biaya Rawat     : Rp %.2f\n", biaya_rawat);
            printf("--------------------------------------------------------------\n");
            printf("TOTAL BIAYA     : Rp %.2f\n", total);
            printf("==============================================================\n");
            printf("                          TERIMA KASIH\n");
            printf("                TELAH DATANG SEMOGA LEKAS SEMBUH\n");
            printf("==============================================================\n\n");
        }
    }

    if (!found)
        printf("[INFO] Tidak ada data untuk dicetak!\n");

    fclose(file);
}

/* ============================
         SIMPAN PDF
   ============================ */
 void simpanPDF(struct Pasien data_pasien, struct Dokter data_dokter, struct Diagnosa diagnosa) {
        FILE *cek = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
        if (!cek) {
            printf("[ERROR] File TXT belum ada! Harap input data dulu.\n");
            return;
        }
        fclose(cek);

        // Buat file formatted untuk PDF
        FILE *file = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
        FILE *formatted = fopen("C:\\TTS_DDP\\formatted_receipt.txt", "w");

        char line[256];
        int id_pasien = 0, umur = 0, id_dokter = 0;
        char nama_pasien[50] = "", alamat[100] = "";
        char nama_dokter[50] = "", spesialis[50] = "", penyakit[100] = "";
        float tarif = 0, biaya_obat = 0, biaya_rawat = 0, total = 0;
        int found = 0;

        // Tanggal Cetak
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(formatted, "==============================================================\n");
        fprintf(formatted, "                 STRUK PEMBAYARAN RUMAH SAKIT\n");
        fprintf(formatted, "==============================================================\n");
        fprintf(formatted, "Tanggal Cetak   : %02d/%02d/%d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
        fprintf(formatted, "==============================================================\n\n");

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "ID Pasien")) sscanf(line, "ID Pasien       : %d", &id_pasien);
            else if (strstr(line, "Nama Pasien")) sscanf(line, "Nama Pasien     : %[^\n]", nama_pasien);
            else if (strstr(line, "Umur Pasien")) sscanf(line, "Umur Pasien     : %d", &umur);
            else if (strstr(line, "Alamat Pasien")) sscanf(line, "Alamat Pasien   : %[^\n]", alamat);
            else if (strstr(line, "ID Dokter")) sscanf(line, "ID Dokter       : %d", &id_dokter);
            else if (strstr(line, "Nama Dokter")) sscanf(line, "Nama Dokter     : %[^\n]", nama_dokter);
            else if (strstr(line, "Spesialis")) sscanf(line, "Spesialis       : %[^\n]", spesialis);
            else if (strstr(line, "Penyakit")) sscanf(line, "Penyakit       : %[^\n]", penyakit);
            else if (strstr(line, "Biaya Obat")) sscanf(line, "Biaya Obat      : Rp %f", &biaya_obat);
            else if (strstr(line, "Biaya Rawat")) sscanf(line, "Biaya Rawat     : Rp %f", &biaya_rawat);
            else if (strstr(line, "Tarif Dokter")) sscanf(line, "Tarif Dokter    : Rp %f", &tarif);
            else if (strstr(line, "TOTAL BIAYA")) {
                sscanf(line, "TOTAL BIAYA     : Rp %f", &total);

                // Setelah total ditemukan → tampilkan 1 struk pasien
                found = 1;
                fprintf(formatted, "=========================DATA PASIEN===========================\n");
                fprintf(formatted, "ID Pasien       : %d\n", id_pasien);
                fprintf(formatted, "Nama Pasien     : %s\n", nama_pasien);
                fprintf(formatted, "Umur            : %d\n", umur);
                fprintf(formatted, "Alamat          : %s\n\n", alamat);

                fprintf(formatted, "=========================DATA DOKTER===========================\n");
                fprintf(formatted, "ID Dokter       : %d\n", id_dokter);
                fprintf(formatted, "Nama Dokter     : %s\n", nama_dokter);
                fprintf(formatted, "Spesialis       : %s\n", spesialis);
                fprintf(formatted, "Tarif Dokter    : Rp %.2f\n\n", tarif);

                fprintf(formatted, "========================DATA DIAGNOSA==========================\n");
                fprintf(formatted, "Penyakit        : %s\n", penyakit);
                fprintf(formatted, "Biaya Obat      : Rp %.2f\n", biaya_obat);
                fprintf(formatted, "Biaya Rawat     : Rp %.2f\n", biaya_rawat);
                fprintf(formatted, "--------------------------------------------------------------\n");
                fprintf(formatted, "TOTAL BIAYA     : Rp %.2f\n", total);
                fprintf(formatted, "==============================================================\n");
                fprintf(formatted, "                          TERIMA KASIH\n");
                fprintf(formatted, "                TELAH DATANG SEMOGA LEKAS SEMBUH\n");
                fprintf(formatted, "==============================================================\n\n");
            }
        }

        fclose(file);
        fclose(formatted);

        if (!found) {
            printf("[INFO] Tidak ada data untuk disimpan ke PDF!\n");
            remove("C:\\TTS_DDP\\formatted_receipt.txt");
            return;
        }

        system("powershell -Command \""
            "$imageUrl = 'https://i.ibb.co.com/8DCZ4pSW/Dise-o-de-logo-para.jpg'; "
            "$imagePath = 'C:\\\\TTS_DDP\\\\logo.png'; "
            "try { Invoke-WebRequest -Uri $imageUrl -OutFile $imagePath } catch { Write-Host 'Failed to download logo'; exit 1 }; "
            "$word = New-Object -ComObject Word.Application; "
            "$word.Visible = $false; "
            "$doc = $word.Documents.Open('C:\\\\TTS_DDP\\\\formatted_receipt.txt'); "
            "$doc.PageSetup.TopMargin = 0; "
            "$doc.PageSetup.BottomMargin = 0; "
            "$doc.PageSetup.LeftMargin = 0; "
            "$doc.PageSetup.RightMargin = 0; "
            "$doc.PageSetup.VerticalAlignment = 1; "
            "$doc.Content.ParagraphFormat.Alignment = 0; "
            "$doc.Content.Font.Size = 15; "
            "$pageWidth = $doc.PageSetup.PageWidth; "
            "$pageHeight = $doc.PageSetup.PageHeight; "
            "$shape = $doc.Shapes.AddPicture($imagePath, $false, $true, 0, 0, $pageWidth, $pageHeight); "
            "$shape.WrapFormat.Type = 3; "
            "$shape.ZOrder(5); "
            "$pdfPath = 'C:\\\\TTS_DDP\\\\data_rumahsakit_ddp.pdf'; "
            "$doc.SaveAs([ref]$pdfPath, [ref]17); "
            "$doc.Close(); "
            "$word.Quit();\"");

        // Hapus file formatted setelah PDF dibuat
        remove("C:\\TTS_DDP\\formatted_receipt.txt");

        printf("\n[INFO] File PDF berhasil dibuat!\n");
    }

/* ============================
           EDIT DATA
   ============================ */
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
                    // "==============================================================\n"
                    // "=========================DATA PASIEN===========================\n"
                    "ID Pasien       : %d\n"
                    "Nama Pasien     : %s\n"
                    "Umur Pasien     : %d\n"
                    "Alamat Pasien   : %s\n\n"
                    "=========================DATA DOKTER===========================\n"
                    "ID Dokter       : %d\n"
                    "Nama Dokter     : %s\n"
                    "Spesialis       : %s\n"
                    "Tarif Dokter    : Rp %.2f\n"
                    "========================DATA DIAGNOSA==========================\n"
                    "Penyakit        : %s\n"
                    "Biaya Obat      : Rp %.2f\n"
                    "Biaya Rawat     : Rp %.2f\n"
                    "--------------------------------------------------------------\n"
                    "TOTAL BIAYA     : Rp %.2f\n"
                    "Tanggal Input   : %s\n\n",
                    p.id, p.nama, p.umur, p.alamat,
                    d.id, d.nama, d.spesialis,
                    d.tarif, dg.penyakit, dg.biaya_obat, dg.biaya_rawat,
                    total, waktuSimpan
                );

                continue;
            }

           // Jika sedang skip blok lama
if (skip) {
    // Blok berakhir ketika kita menemukan garis pemisah YANG DIIKUTI baris kosong
    if (strstr(line, "==============================================================")) {

        long pos = ftell(file);
        char next[512];

        if (fgets(next, sizeof(next), file)) {
            // Jika setelah garis ada baris kosong → akhir blok
            if (strcmp(next, "\n") == 0 || strcmp(next, "\r\n") == 0) {
                skip = 0;
                continue; // jangan tulis garis terakhir
            } else {
                // bukan akhir blok → kembalikan pointer
                fseek(file, pos, SEEK_SET);
            }
        }
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

/* ============================
         HAPUS DATA
   ============================ */
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

        // Deteksi awal data pasien yang ingin dihapus
        if (!skipBlock && strstr(line, "ID Pasien")) {
            int id;
            sscanf(line, "ID Pasien       : %d", &id);

            if (id == idHapus) {
                // Mulai skip seluruh blok (pasien + dokter + diagnosa)
                found = 1;
                skipBlock = 1;
                continue;
            }
        }

        // Jika sedang skip blok
        if (skipBlock) {

            // Deteksi AKHIR blok: garis batas + baris kosong setelahnya
            if (strstr(line, "==============================================================")) {

                // Cek baris berikutnya (peek)
                long pos = ftell(file);
                char next[512];

                if (fgets(next, sizeof(next), file)) {
                    if (strcmp(next, "\n") == 0 || strcmp(next, "\r\n") == 0) {
                        // blok berakhir → matikan skip
                        skipBlock = 0;
                        continue; // jangan tulis garis ini
                    } else {
                        // bukan akhir blok → kembalikan posisi
                        fseek(file, pos, SEEK_SET);
                    }
                }
            }
            continue;
        }

        // Tulis baris jika tidak di-skip
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
        printf("\n[INFO] Semua data terkait ID %d (pasien + dokter + diagnosa) telah dihapus!\n", idHapus);
        // CEK apakah file benar-benar kosong dari data pasien
FILE *cek = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "r");
int adaData = 0;
char celine[200];

while (fgets(celine, sizeof(celine), cek)) {
    if (strstr(celine, "ID Pasien")) {
        adaData = 1;
        break;
    }
}
fclose(cek);

// Jika tidak ada data pasien lagi → kosongkan file total
if (!adaData) {
    FILE *clear = fopen("C:\\TTS_DDP\\data_rumahsakit_ddp_temp.txt", "w");
    fclose(clear);
    
}
    }
}
