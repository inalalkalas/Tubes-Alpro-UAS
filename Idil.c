#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Pengiriman {
    char nama_pengirim[50];
    char tujuan_pengiriman[50];
    float berat_barang;
    char nama_penerima[50];
    char kode_resi[10];
    float harga;
    time_t timestamp;
    char status[20];
};

float hitungHarga(float berat) {
    const float harga_per_kg = 10.0;
    return berat * harga_per_kg;
}

// newline buffer 
void newLine(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void tampilkanKodeResi(struct Pengiriman data) {
    printf("Kode Resi        : %s\n", data.kode_resi);
}

void tampilkanData(struct Pengiriman data) {
    printf("Nama Pengirim   : %s\n", data.nama_pengirim);
    printf("Tujuan Pengiriman: %s\n", data.tujuan_pengiriman);
    printf("Berat Barang     : %.2f kg\n", data.berat_barang);
    printf("Nama Penerima    : %s\n", data.nama_penerima);
    printf("Kode Resi        : %s\n", data.kode_resi);
    printf("Harga            : Rp.%.2f\n", data.harga);

    char timestamp_str[20];
    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", localtime(&data.timestamp));
    printf("Timestamp        : %s\n", timestamp_str);

    printf("Status           : %s\n", data.status);

    printf("-----------------------------\n");
}

void cariData(struct Pengiriman data[], int jumlah_data, char kode_resi_cari[10]) {
    int ditemukan = 0;
    for (int i = 0; i < jumlah_data; i++) {
        if (strcmp(data[i].kode_resi, kode_resi_cari) == 0) {
            tampilkanData(data[i]);
            ditemukan = 1;
            break;
        }
    }

    if (!ditemukan) {
        printf("Data tidak ditemukan.\n");
    }
}

void tampilkanSemuaData(struct Pengiriman data[], int jumlah_data) {
    if (jumlah_data > 0) {
        printf("\nSemua Data Pengiriman:\n");
        for (int i = 0; i < jumlah_data; i++) {
            printf("Data ke-%d:\n", i + 1);
            tampilkanData(data[i]);
        }
    } else {
        printf("Tidak ada data yang diinput.\n");
    }
}

int compareTimestampAsc(const void *a, const void *b) {
    return ((struct Pengiriman *)a)->timestamp - ((struct Pengiriman *)b)->timestamp;
}

int compareTimestampDesc(const void *a, const void *b) {
    return ((struct Pengiriman *)b)->timestamp - ((struct Pengiriman *)a)->timestamp;
}

void urutkanData(struct Pengiriman data[], int jumlah_data, int urutan) {
    if (urutan == 1) {
        qsort(data, jumlah_data, sizeof(struct Pengiriman), compareTimestampAsc);
        printf("\nData Pengiriman diurutkan berdasarkan tanggal secara ascending:\n");
    } else if (urutan == 2) {
        qsort(data, jumlah_data, sizeof(struct Pengiriman), compareTimestampDesc);
        printf("\nData Pengiriman diurutkan berdasarkan tanggal secara descending:\n");
    } else {
        printf("Pilihan tidak valid.\n");
        return;
    }

    tampilkanSemuaData(data, jumlah_data);
}

void simpanDataKeFileCSV(struct Pengiriman data[], int jumlah_data) {
    FILE *file = fopen("data_pengiriman.csv", "w");
    if (file != NULL) {
        // Print header
        fprintf(file, "Nama Pengirim;Tujuan Pengiriman;Berat Barang;Nama Penerima;Kode Resi;Harga;Timestamp;Status\n");

        for (int i = 0; i < jumlah_data; i++) {
            // Use fprintf to write data to file
            fprintf(file, "%s;%s;%.2f;%s;%s;%.2f;%ld;%s\n", data[i].nama_pengirim, data[i].tujuan_pengiriman,
                    data[i].berat_barang, data[i].nama_penerima, data[i].kode_resi, data[i].harga,
                    data[i].timestamp, data[i].status);
        }

        fclose(file);
        printf("Data berhasil disimpan ke data_pengiriman.csv.\n");
    } else {
        printf("Gagal membuka file untuk penulisan data.\n");
    }
}

void bacaDataDariFile(struct Pengiriman data[], int *jumlah_data) {
    FILE *file = fopen("data_pengiriman.csv", "r");
    if (file != NULL) {
        // Change the fscanf format to read the data correctly
        while (fscanf(file, "%49[^;];%49[^;];%f;%49[^;];%9[^;];%f;%ld;%19[^\n]\n",
                      data[*jumlah_data].nama_pengirim, data[*jumlah_data].tujuan_pengiriman,
                      &data[*jumlah_data].berat_barang, data[*jumlah_data].nama_penerima,
                      data[*jumlah_data].kode_resi, &data[*jumlah_data].harga,
                      &data[*jumlah_data].timestamp, data[*jumlah_data].status) == 8) {
            (*jumlah_data)++;
        }

        fclose(file);
    } else {
        printf("File tidak ditemukan atau gagal membuka file untuk membaca data.\n");
    }
}

int main() {
    const int maks_data = 100;
    struct Pengiriman data[maks_data];
    int jumlah_data = 0;

    bacaDataDariFile(data, &jumlah_data);

    int pilihan, urutan;
    char kode_resi_cari[10];

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Data Pengiriman\n");
        printf("2. Cari Data Pengiriman\n");
        printf("3. Tampilkan Semua Data Pengiriman\n");
        printf("4. Urutkan Data Berdasarkan Tanggal\n");
        printf("5. Edit Status Pengiriman\n");
        printf("6. Keluar\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &pilihan);


        switch (pilihan) {
            case 1:
                newLine();

                printf("\nMasukkan data pengiriman\n");
                printf("Nama Pengirim   : ");
                fgets(data[jumlah_data].nama_pengirim, sizeof(data[jumlah_data].nama_pengirim), stdin);
                strtok(data[jumlah_data].nama_pengirim, "\n"); // Remove the newline from the input

                printf("Tujuan Pengiriman: ");
                fgets(data[jumlah_data].tujuan_pengiriman, sizeof(data[jumlah_data].tujuan_pengiriman), stdin);
                strtok(data[jumlah_data].tujuan_pengiriman, "\n"); // Remove the newline from the input

                printf("Berat Barang (kg): ");
                scanf("%f", &data[jumlah_data].berat_barang);
                newLine();

                printf("Nama Penerima    : ");
                fgets(data[jumlah_data].nama_penerima, sizeof(data[jumlah_data].nama_penerima), stdin);
                strtok(data[jumlah_data].nama_penerima, "\n"); // Remove the newline from the input

                sprintf(data[jumlah_data].kode_resi, "R%03d", jumlah_data + 1);

                data[jumlah_data].harga = hitungHarga(data[jumlah_data].berat_barang);

                data[jumlah_data].timestamp = time(NULL);

                printf("\nKode Resi yang telah diinput:\n");
                tampilkanKodeResi(data[jumlah_data]);

                // Adding status input
                printf("\nPilih status pengiriman (1. Ongoing, 2. Delivered): ");
                int status_choice;
                scanf("%d", &status_choice);
                getchar();

                switch (status_choice) {
                    case 1:
                        strcpy(data[jumlah_data].status, "Ongoing");
                        break;
                    case 2:
                        strcpy(data[jumlah_data].status, "Delivered");
                        break;
                    default:
                        printf("Pilihan status tidak valid. Status di set default sebagai Ongoing.\n");
                        strcpy(data[jumlah_data].status, "Ongoing");
                }

                jumlah_data++;
                simpanDataKeFileCSV(data, jumlah_data);
                break;

            case 2:
                newLine();

                printf("\nMasukkan kode resi untuk mencari data: ");
                fgets(kode_resi_cari, sizeof(kode_resi_cari), stdin);
                strtok(kode_resi_cari, "\n");
                cariData(data, jumlah_data, kode_resi_cari);
                break;

            case 3:
                tampilkanSemuaData(data, jumlah_data);
                break;

            case 4:
                newLine();

                printf("\nPilih urutan pengurutan:\n");
                printf("1. Ascending\n");
                printf("2. Descending\n");
                printf("Pilih urutan (1-2): ");
                scanf("%d", &urutan);

                urutkanData(data, jumlah_data, urutan);
                break;

            case 5:
                newLine();

                // Edit Status
                printf("\nMasukkan kode resi untuk mengedit status: ");
                fgets(kode_resi_cari, sizeof(kode_resi_cari), stdin);
                strtok(kode_resi_cari, "\n");
                cariData(data, jumlah_data, kode_resi_cari);

                // Find the index of the shipment with the given Resi Code
                int index;
                for (index = 0; index < jumlah_data; index++) {
                    if (strcmp(data[index].kode_resi, kode_resi_cari) == 0) {
                        break;
                    }
                }

                if (index < jumlah_data) {
                    printf("Pilih status baru (1. Ongoing, 2. Delivered): ");
                    int status_choice;
                    scanf("%d", &status_choice);
                    getchar();

                    switch (status_choice) {
                        case 1:
                            strcpy(data[index].status, "Ongoing");
                            break;
                        case 2:
                            strcpy(data[index].status, "Delivered");
                            break;
                        default:
                            printf("Pilihan status tidak valid. Status tidak diubah.\n");
                    }
                } else {
                    printf("Data tidak ditemukan.\n");
                }
                break;

            case 6:
                printf("Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }
    } while (pilihan != 6);

    return 0;
}