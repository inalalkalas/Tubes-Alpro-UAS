#include <stdio.h>
#include <string.h>


struct Pengiriman {
    char nama_pengirim[50];
    char tujuan_pengiriman[50];
    float berat_barang;
    char nama_penerima[50];
    char kode_resi[10];
    float harga;
};


float hitungHarga(float berat) {
    const float harga_per_kg = 10.0;
    return berat * harga_per_kg;
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
    printf("Harga            : $%.2f\n", data.harga);
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

int main() {
    const int maks_data = 100;
    struct Pengiriman data[maks_data];
    int jumlah_data = 0;


    printf("Masukkan data pengiriman:\n");
    printf("Nama Pengirim   : ");
    fgets(data[jumlah_data].nama_pengirim, sizeof(data[jumlah_data].nama_pengirim), stdin);
    printf("Tujuan Pengiriman: ");
    fgets(data[jumlah_data].tujuan_pengiriman, sizeof(data[jumlah_data].tujuan_pengiriman), stdin);
    printf("Berat Barang (kg): ");
    scanf("%f", &data[jumlah_data].berat_barang);
    getchar(); 
    printf("Nama Penerima    : ");
    fgets(data[jumlah_data].nama_penerima, sizeof(data[jumlah_data].nama_penerima), stdin);

   
    sprintf(data[jumlah_data].kode_resi, "R%03d", jumlah_data + 1);


    data[jumlah_data].harga = hitungHarga(data[jumlah_data].berat_barang);


    printf("\nKode Resi yang telah diinput:\n");
    tampilkanKodeResi(data[jumlah_data]);


    jumlah_data++;


    char kode_resi_cari[10];
    printf("\nMasukkan kode resi untuk mencari data: ");
    fgets(kode_resi_cari, sizeof(kode_resi_cari), stdin);
    strtok(kode_resi_cari, "\n");
    cariData(data, jumlah_data, kode_resi_cari);

    return 0;
}
