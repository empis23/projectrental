#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Struktur data untuk menyimpan informasi mobil
struct Mobil {
    string model;
    string platNomor;
    int hargaPerHari;
    bool tersedia;
    string penyewa;
    int lamaSewa;
};

const int MAX_MOBIL = 100;
Mobil daftarMobil[MAX_MOBIL] = {
    {"Toyota Avanza", "B1234CD", 300000, true},
    {"Honda Jazz", "B2345DE", 350000, true},
    {"Suzuki Ertiga", "B3456EF", 320000, true},
    {"Daihatsu Xenia", "B4567FG", 310000, true},
    {"Nissan Livina", "B5678GH", 340000, true},
    {"Mitsubishi Xpander", "B6789IJ", 400000, true},
    {"Kia Carens", "B78y90JK", 360000, true},
    {"Mazda CX-5", "B8901KL", 450000, true},
    {"Honda CR-V", "B9012LM", 500000, true},
    {"Toyota Fortuner", "B0123MN", 600000, true}
};
int jumlahMobil = 10;

// Array 2D simulasi ketersediaan mingguan mobil (1 = tersedia, 0 = tidak tersedia)
int ketersediaan[5][7] = {
    {1,1,0,1,1,1,0},
    {1,1,1,1,1,1,1},
    {0,0,0,0,0,1,1},
    {1,1,1,1,1,0,0},
    {1,0,1,0,1,0,1}
};

// Fungsi untuk mencari indeks mobil berdasarkan plat nomor dengan pencarian sequential
int cariMobil(string plat) {
    for (int i=0; i<jumlahMobil; i++) {
        if (daftarMobil[i].platNomor == plat) return i;
    }
    return -1;
}

// Fungsi binary search (asumsi daftarMobil sudah diurutkan berdasarkan platNomor)
int binarySearch(string target) {
    int low=0, high=jumlahMobil-1;
    while (low<=high) {
        int mid = (low+high)/2;
        if (daftarMobil[mid].platNomor == target) return mid;
        else if (daftarMobil[mid].platNomor < target) low = mid+1;
        else high = mid-1;
    }
    return -1;
}

// Fungsi mengurutkan daftarMobil berdasarkan plat nomor secara ascending (A-Z)
void urutkanPlatNomor() {
    for (int i=0; i < jumlahMobil-1; i++) {
        for (int j=i+1; j < jumlahMobil; j++) {
            if (daftarMobil[i].platNomor > daftarMobil[j].platNomor) {
                swap(daftarMobil[i], daftarMobil[j]);
            }
        }
    }
    cout << "[INFO] Data telah diurutkan berdasarkan plat nomor (A-Z).\n";
}

// Menu untuk mencari mobil dengan pilihan metode pencarian
void menuCariMobil() {
    int metode;
    cout << "\n====== Menu Pencarian Mobil ======\n";
    cout << "1. Sequential Search\n";
    cout << "2. Binary Search (plat harus diurutkan)\n";
    cout << "Pilihan: ";
    cin >> metode;
    cin.ignore();

    string plat;
    cout << "Masukkan plat nomor (Tanpa spasi): ";
    getline(cin, plat);

    int idx = -1;
    if (metode == 1) {
        idx = cariMobil(plat);
    } else if (metode == 2) {
        urutkanPlatNomor();
        idx = binarySearch(plat);
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    if (idx != -1)
        cout << "Mobil ditemukan: " << daftarMobil[idx].model << " (" << daftarMobil[idx].platNomor << ")\n";
    else
        cout << "Mobil tidak ditemukan.\n";
}

// Fungsi rekursif menghitung total biaya sewa
int hitungBiaya(int harga, int lama) {
    if (lama == 0) return 0;
    return harga + hitungBiaya(harga, lama-1);
}

// Fungsi tambah mobil ke daftar
void tambahMobil() {
    if (jumlahMobil >= MAX_MOBIL) {
        cout << "Kapasitas maksimum tercapai.\n";
        return;
    }
    cin.ignore();
    cout << "Masukkan model mobil: "; getline(cin, daftarMobil[jumlahMobil].model);
    cout << "Masukkan plat nomor: "; getline(cin, daftarMobil[jumlahMobil].platNomor);
    cout << "Masukkan harga sewa per hari (ribuan): ";
    int harga; cin >> harga;
    daftarMobil[jumlahMobil].hargaPerHari = harga*1000;
    daftarMobil[jumlahMobil].tersedia = true;
    daftarMobil[jumlahMobil].penyewa = "";
    daftarMobil[jumlahMobil].lamaSewa = 0;
    jumlahMobil++;
    cout << "Mobil berhasil ditambahkan!\n";
}

// Fungsi hapus mobil dari daftar berdasarkan plat nomor dan catat alasan pada file log
void hapusMobil() {
    cin.ignore();
    string plat, alasan;
    cout << "Masukkan plat nomor mobil yang ingin dihapus: "; getline(cin, plat);
    int idx = cariMobil(plat);
    if (idx == -1) {
        cout << "Mobil tidak ditemukan.\n";
        return;
    }
    cout << "Masukkan alasan penghapusan(bebas): "; getline(cin, alasan);
    for (int i=idx; i < jumlahMobil-1; i++) {
        daftarMobil[i] = daftarMobil[i+1];
    }
    jumlahMobil--;
    ofstream log("log_penghapusan.txt", ios::app);
    log << "Mobil " << plat << " dihapus. Alasan: " << alasan << "\n";
    log.close();
    cout << "Mobil berhasil dihapus.\n";
}

// Menu edit daftar mobil
void menuEditMobil() {
    int pilihan;
    cout << "\n==== Menu Edit Mobil ====";
    cout << "\n1. Tambah Mobil";
    cout << "\n2. Hapus Mobil";
    cout << "\nPilihan: ";
    cin >> pilihan;
    if (pilihan == 1) tambahMobil();
    else if (pilihan == 2) hapusMobil();
    else cout << "Pilihan tidak valid.\n";
}

// Tampilkan daftar semua mobil dengan status lengkap
void tampilkanMobil() {
    cout << "\n================================================================================\n";
    cout << "| No |           Model Mobil           | Plat Nomor | Harga/Hari |   Status   |\n";
    cout << "================================================================================\n";
    for (int i=0; i<jumlahMobil; i++) {
        cout << "| " << setw(2) << i+1 << " | " << left << setw(30) << daftarMobil[i].model;
        cout << " | " << setw(10) << daftarMobil[i].platNomor;
        cout << " | Rp" << right << setw(9) << daftarMobil[i].hargaPerHari;
        cout << " | " << left << setw(10) << (daftarMobil[i].tersedia ? "Tersedia" : "Disewa") << " |\n";
    }
    cout << "================================================================================\n";
}

// Tampilkan hanya mobil yang tersedia
void tampilkanMobilTersedia() {
    cout << "\n============================ Mobil Tersedia ============================\n";
    cout << "| No |           Model Mobil           | Plat Nomor | Harga/Hari |\n";
    cout << "=========================================================================\n";
    int no=1;
    for (int i=0; i<jumlahMobil; i++) {
        if (daftarMobil[i].tersedia) {
            cout << "| " << setw(2) << no++ << " | " << left << setw(30) << daftarMobil[i].model;
            cout << " | " << setw(10) << daftarMobil[i].platNomor;
            cout << " | Rp" << right << setw(9) << daftarMobil[i].hargaPerHari << " |\n";
        }
    }
    if (no == 1) cout << "| Tidak ada mobil yang tersedia.                                      |\n";
    cout << "=========================================================================\n";
}

// Tampilkan hanya mobil yang sedang disewa beserta detail penyewa dan lama sewa
void tampilkanMobilDisewa() {
    cout << "\n================================ Mobil Disewa =============================\n";
    cout << "| No |           Model Mobil           | Plat Nomor | Penyewa     | Lama Sewa |\n";
    cout << "==========================================================================\n";
    int no=1;
    for (int i=0; i<jumlahMobil; i++) {
        if (!daftarMobil[i].tersedia) {
            cout << "| " << setw(2) << no++ << " | " << left << setw(30) << daftarMobil[i].model;
            cout << " | " << setw(10) << daftarMobil[i].platNomor;
            cout << " | " << setw(10) << daftarMobil[i].penyewa;
            cout << " | " << setw(9) << daftarMobil[i].lamaSewa << " |\n";
        }
    }
    if (no == 1) cout << "| Tidak ada mobil yang disewa.                                          |\n";
    cout << "==========================================================================\n";
}

// Fungsi untuk menyewa mobil
void sewaMobil() {
    cin.ignore();
    string plat, nama;
    int lama;
    cout << "Masukkan plat mobil: ";
    getline(cin, plat);
    int idx = cariMobil(plat);
    if (idx == -1) {
        cout << "Mobil tidak ditemukan.\n";
        return;
    }
    if (!daftarMobil[idx].tersedia) {
        cout << "Mobil sedang disewa.\n";
        return;
    }
    cout << "Masukkan nama penyewa: ";
    getline(cin, nama);
    cout << "Lama sewa (hari): ";
    cin >> lama;
    daftarMobil[idx].tersedia = false;
    daftarMobil[idx].penyewa = nama;
    daftarMobil[idx].lamaSewa = lama;
    int biaya = hitungBiaya(daftarMobil[idx].hargaPerHari, lama);

    // Simpan transaksi ke file log
    ofstream log("log_transaksi.txt", ios::app);
    log << nama << ", " << plat << ", " << lama << " hari, Rp" << biaya << "\n";
    log.close();

    cout << "Sewa berhasil! Total biaya: Rp" << biaya << endl;
}

// Fungsi untuk mengembalikan mobil
void kembalikanMobil() {
    cin.ignore();
    string plat;
    cout << "Masukkan plat mobil yang dikembalikan: ";
    getline(cin, plat);
    int idx = cariMobil(plat);
    if (idx == -1) {
        cout << "Mobil tidak ditemukan.\n";
        return;
    }
    if (daftarMobil[idx].tersedia) {
        cout << "Mobil belum disewa.\n";
        return;
    }
    int biaya = hitungBiaya(daftarMobil[idx].hargaPerHari, daftarMobil[idx].lamaSewa);
    cout << "Mobil dikembalikan oleh: " << daftarMobil[idx].penyewa << endl;
    cout << "Total biaya sewa: Rp" << biaya << endl;
    daftarMobil[idx].tersedia = true;
    daftarMobil[idx].penyewa = "";
    daftarMobil[idx].lamaSewa = 0;
}

// Menu sewa mobil lengkap dengan opsi sewa, kembalikan, dan tampilkan mobil disewa
void menuSewa() {
    int pilihan;
    cout << "\n====Menu Sewa ====";
    cout << "\n1. Sewa mobil";
    cout << "\n2. Kembalikan mobil";
    cout << "\n3. Tampilkan mobil yang disewa";
    cout << "\nPilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: 
            sewaMobil(); 
            break;
        case 2: 
            kembalikanMobil(); 
            break;
        case 3: 
            tampilkanMobilDisewa(); 
            break;
        default: 
        cout << "Pilihan tidak valid.\n";
    }
}

// Fungsi memberikan diskon pada harga mobil
void diskon(Mobil* m, int persen) {
    m->hargaPerHari = m->hargaPerHari * (100 - persen) / 100;
}

// Menu diskon untuk memberikan diskon berdasarkan input model atau plat
void diskonMobil() {
    cin.ignore();
    string input;
    int persen;
    cout << "Masukkan model mobil atau plat (bagian nama/plat): ";
    getline(cin, input);
    cout << "Masukkan besar diskon (%): ";
    cin >> persen;
    bool found = false;
    for (int i=0; i < jumlahMobil; i++) {
        if (daftarMobil[i].model.find(input) != string::npos || daftarMobil[i].platNomor.find(input) != string::npos) {
            diskon(&daftarMobil[i], persen);
            found = true;
        }
    }
    if (found) cout << "Diskon berhasil diberikan.\n";
    else cout << "Tidak ada mobil cocok ditemukan.\n";
}

// Simpan data daftarMobil ke file
void simpanKeFile() {
    ofstream file("data_mobil.txt");
    for (int i=0; i < jumlahMobil; i++) {
        file << daftarMobil[i].model << ";" << daftarMobil[i].platNomor << ";" << daftarMobil[i].hargaPerHari << ";"
             << daftarMobil[i].tersedia << ";" << daftarMobil[i].penyewa << ";" << daftarMobil[i].lamaSewa << "\n";
    }
    file.close();
    cout << "Data berhasil disimpan.\n";
}

// Baca data dari file dengan format yang sama dengan simpanKeFile
void bacaDariFile() {
    ifstream file("data_mobil.txt");
    jumlahMobil = 0;
    while (getline(file, daftarMobil[jumlahMobil].model, ';') &&
           getline(file, daftarMobil[jumlahMobil].platNomor, ';') &&
           file >> daftarMobil[jumlahMobil].hargaPerHari && file.get() &&
           file >> daftarMobil[jumlahMobil].tersedia && file.get() &&
           getline(file, daftarMobil[jumlahMobil].penyewa, ';') &&
           file >> daftarMobil[jumlahMobil].lamaSewa) {
        file.get();
        jumlahMobil++;
        if(jumlahMobil >= MAX_MOBIL) break;
    }
    file.close();
    cout << "Data berhasil dibaca dari file.\n";
}

// Tampilkan isi log transaksi sewa
void tampilkanLogTransaksi() {
    ifstream log("log_transaksi.txt");
    if (!log) {
        cout << "Belum ada data transaksi.\n";
        return;
    }
    cout << "\n=========== Riwayat Transaksi ==========\n";
    string baris;
    while (getline(log, baris)) {
        cout << baris << "\n";
    }
    cout << "========================================\n";
    log.close();
}

// Hapus file yang ditentukan pengguna
void hapusFile() {
    cin.ignore();
    string namaFile;
    cout << "Masukkan nama file yang ingin dihapus: ";
    getline(cin, namaFile);
    if (remove(namaFile.c_str()) == 0) cout << "[INFO] File berhasil dihapus.\n";
    else cout << "[ERROR] Gagal menghapus file. Pastikan file ada.\n";
}

// Ganti nama file
void renameFile() {
    cin.ignore();
    string lama, baru;
    cout << "Masukkan nama file lama: ";
    getline(cin, lama);
    cout << "Masukkan nama file baru: ";
    getline(cin, baru);
    if (rename(lama.c_str(), baru.c_str()) == 0) cout << "[INFO] File berhasil diubah namanya.\n";
    else cout << "[ERROR] Gagal mengganti nama file. Pastikan file lama ada.\n";
}

// Menu manajemen data
void menuManajemenData() {
    int pilihan;
    cout << "\n====== Manajemen Data ======\n";
    cout << "1. Simpan data ke file\n";
    cout << "2. Muat data dari file\n";
    cout << "3. Tampilkan log transaksi\n";
    cout << "4. Hapus file\n";
    cout << "5.Ganti nama file\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: 
            simpanKeFile(); 
            break;
        case 2: 
            bacaDariFile(); 
            tampilkanMobil(); 
            break;
        case 3: 
            tampilkanLogTransaksi(); 
            break;
        case 4: 
            hapusFile(); 
            break;
        case 5: 
            renameFile(); 
            break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

// Tampilkan simulasi ketersediaan mobil (array 2D)
void tampilkanKetersediaan() {
    cout << "\n==== Simulasi Ketersediaan Mobil (Array 2D) ====\n";
    string hari[] = {"Sen", "Sel", "Rab", "Kam", "Jum", "Sab", "Min"};
    cout << setw(12) << "Mobil/Hari";
    for (int i=0; i<7; i++) cout << setw(6) << hari[i];
    cout << endl;
    for (int i=0; i<5; i++) {
        cout << setw(12) << ("Mobil "+to_string(i+1));
        for (int j=0; j<7; j++) {
            cout << setw(6) << (ketersediaan[i][j] ? "Y" : "N");
        }
        cout << endl;
    }
}

// Menu untuk simulasi jadwal servis (hanya 2D)
void menuJadwalServis() {
    int pilihan;
    cout << "\n==== Simulasi Jadwal ====\n";
    cout << "1. Ketersediaan Mingguan (Array 2D)\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    if (pilihan == 1) tampilkanKetersediaan();
    else cout << "Pilihan tidak valid.\n";
}

// Fungsi demonstrasi pointer ke array harga sewa mobil
void pointerKeArray() {
    int harga[] = {300000,350000,320000,310000,340000};
    int* ptr = harga;
    cout << "\n=== Pointer ke Array ===\n";
    for (int i=0; i<5; i++) {
        cout << "Harga ke-" << (i+1) << " = Rp" << *(ptr+i) << endl;
    }
}

// Fungsi demonstrasi pointer ke string (atribut model mobil)
void pointerKeString() {
    int index;
    cout << "\n=== Pointer ke String ===\n";
    cout << "Pilih nomor mobil (1 - " << jumlahMobil << "): ";
    cin >> index;
    if (index < 1 || index > jumlahMobil) {
        cout << "Nomor mobil tidak valid.\n";
        return;
    }
    string* ptr = &daftarMobil[index-1].model;
    cout << "Model Mobil [" << index << "] = " << *ptr << endl;
    cout << "(Data diambil dari daftarMobil [" << index-1 << "]. model)\n";
}

// Fungsi demonstrasi pointer ke pointer
void pointerKePointer() {
    int harga = 300000;
    int* ptr = &harga;
    int** ptrptr = &ptr;
    cout << "\n=== Pointer ke Pointer ===\n";
    cout << "Harga sewa mobil diakses berbagai cara:\n";
    cout << "Langsung: Rp" << harga << "\n";
    cout << "Melalui pointer: Rp" << *ptr << "\n";
    cout << "Melalui pointer ke pointer: Rp" << **ptrptr << "\n";
}

// Menu simulasi pointer
void menuSimulasiPointer() {
    int pilihan;
    char ulang;
    do {
        cout << "\n====== Simulasi Pointer ======\n";
        cout << "1. Pointer ke Array\n";
        cout << "2. Pointer ke String\n";
        cout << "3. Pointer ke Pointer\n";
        cout << "4. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        switch(pilihan) {
            case 1: 
                pointerKeArray(); 
                break;
            case 2: 
                pointerKeString(); 
                break;
            case 3: 
                pointerKePointer(); 
                break;
            case 4: 
            return;
            default: cout << "Pilihan tidak valid.\n"; continue;
        }
        cout << "Kembali ke menu pointer? (y/n): ";
        cin >> ulang;
    } while (ulang == 'y' || ulang == 'Y');
}

// Fungsi sorting - bubble, insertion, selection, shell, quick sort masing-masing dengan arah ascending atau descending
void bubbleSort(bool asc = true) {
    for (int i=0; i<jumlahMobil-1; i++) {
        for (int j=0; j<jumlahMobil-i-1; j++) {
            if ((asc && daftarMobil[j].hargaPerHari > daftarMobil[j+1].hargaPerHari) ||
                (!asc && daftarMobil[j].hargaPerHari < daftarMobil[j+1].hargaPerHari)) {
                swap(daftarMobil[j], daftarMobil[j+1]);
            }
        }
    }
}

void insertionSort(bool asc = true) {
    for (int i=1; i<jumlahMobil; i++) {
        Mobil key = daftarMobil[i];
        int j = i-1;
        while(j >= 0 && ((asc && daftarMobil[j].hargaPerHari > key.hargaPerHari)||(!asc && daftarMobil[j].hargaPerHari < key.hargaPerHari))) {
            daftarMobil[j+1] = daftarMobil[j];
            j--;
        }
        daftarMobil[j+1] = key;
    }
}

void selectionSort(bool asc = true) {
    for (int i=0; i<jumlahMobil-1; i++) {
        int idx = i;
        for (int j=i+1; j<jumlahMobil; j++) {
            if ((asc && daftarMobil[j].hargaPerHari < daftarMobil[idx].hargaPerHari) || (!asc && daftarMobil[j].hargaPerHari > daftarMobil[idx].hargaPerHari)) {
                idx = j;
            }
        }
        swap(daftarMobil[i], daftarMobil[idx]);
    }
}

void shellSort(bool asc = true) {
    for(int gap=jumlahMobil/2; gap>0; gap/=2){
        for(int i=gap; i<jumlahMobil; i++){
            Mobil temp = daftarMobil[i];
            int j;
            for(j=i; j>=gap && ((asc && daftarMobil[j-gap].hargaPerHari > temp.hargaPerHari) || (!asc && daftarMobil[j-gap].hargaPerHari < temp.hargaPerHari)); j-=gap){
                daftarMobil[j] = daftarMobil[j-gap];
            }
            daftarMobil[j] = temp;
        }
    }
}

int partition(int low, int high, bool asc) {
    int pivot = daftarMobil[high].hargaPerHari;
    int i = low-1;
    for (int j=low; j<high; j++){
        if ((asc && daftarMobil[j].hargaPerHari < pivot) || (!asc && daftarMobil[j].hargaPerHari > pivot)) {
            i++;
            swap(daftarMobil[i], daftarMobil[j]);
        }
    }
    swap(daftarMobil[i+1], daftarMobil[high]);
    return i+1;
}

void quickSort(int low, int high, bool asc){
    if(low < high){
        int pi = partition(low, high, asc);
        quickSort(low, pi-1, asc);
        quickSort(pi+1, high, asc);
    }
}

void algoritmaSorting(){
    int metode;
    cout << "\n==== Pilih Algoritma Sorting ====\n";
    cout << "1. Bubble Sort Ascending\n";
    cout << "2. Bubble Sort Descending\n";
    cout << "3. Insertion Sort Ascending\n";
    cout << "4. Insertion Sort Descending\n";
    cout << "5. Selection Sort Ascending\n";
    cout << "6. Selection Sort Descending\n";
    cout << "7. Shell Sort Ascending\n";
    cout << "8. Shell Sort Descending\n";
    cout << "9. Quick Sort Ascending\n";
    cout << "10. Quick Sort Descending\n";
    cout << "silahkan Pilih Metode (1-10): ";
    cin >> metode;
    switch (metode){
        case 1: 
            bubbleSort(true); 
            break;
        case 2: 
            bubbleSort(false); 
            break;
        case 3: 
            insertionSort(true); 
            break;
        case 4: 
            insertionSort(false); 
            break;
        case 5: 
            selectionSort(true); 
            break;
        case 6: 
            selectionSort(false); 
            break;
        case 7: 
            shellSort(true); 
            break;
        case 8: 
            shellSort(false); 
            break;
        case 9: 
            quickSort(0, jumlahMobil-1, true); 
            break;
        case 10: 
            quickSort(0, jumlahMobil-1, false); 
            break;
        default: cout << "Pilihan tidak valid.\n"; 
        return;
    }
    cout << "Data berhasil diurutkan dengan algoritma pilihan.\n";
    tampilkanMobil();
}

// Menu tampilkan mobil dengan opsi tampil semua, tersedia, disewa, dan sorting harga
void menuTampilkanMobil() {
    int pilihan;
    cout << "\n==== Tampilkan Daftar Mobil ====\n";
    cout << "1. Semua mobil\n";
    cout << "2. Hanya yang tersedia\n";
    cout << "3. Hanya yang disewa\n";
    cout << "4. Urutkan berdasarkan harga\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: 
            tampilkanMobil(); 
            break;
        case 2: 
            tampilkanMobilTersedia(); 
            break;
        case 3: 
            tampilkanMobilDisewa(); 
            break;
        case 4: 
            algoritmaSorting(); 
            break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

// Fungsi konfirmasi untuk kembali ke menu utama
bool kembaliKeMenu() {
    char jawab;
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> jawab;
    return (jawab == 'y' || jawab == 'Y');
}

// Program utama
int main(){
    int pilihan;
    do {
        cout << "\n==== PROGRAM RENTAL MOBIL PT NIAP ====\n";
        cout << "1. Tampilkan Daftar Mobil\n";
        cout << "2. Edit Daftar Mobil\n";
        cout << "3. Cari Mobil\n";
        cout << "4. Sewa/Kembalikan Mobil\n";
        cout << "5. Diskon Mobil\n";
        cout << "6. Manajemen Data\n";
        cout << "7. Jadwal Servis\n";
        cout << "8. Simulasi Pointer\n";
        cout << "9. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        switch (pilihan){
            case 1: 
                menuTampilkanMobil(); 
                break;
            case 2: 
                menuEditMobil(); 
                break;
            case 3: 
                menuCariMobil(); 
                break;
            case 4:
                menuSewa(); 
                break;
            case 5: 
                diskonMobil(); 
                break;
            case 6: 
                menuManajemenData(); 
                break;
            case 7: 
                menuJadwalServis(); 
                break;
            case 8: 
                menuSimulasiPointer(); 
                break;
            case 9: cout << "Terima kasih telah menggunakan program kami.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
        if (pilihan != 9 && !kembaliKeMenu()) break;
    } while (pilihan != 9);
    
    return 0;
}
