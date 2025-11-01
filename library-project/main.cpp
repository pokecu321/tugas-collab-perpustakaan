#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct TTL
{
    string tempat;
    int tgl;
    int bulan;
    int tahun;
};

struct data_anggota
{
    string id;//6 digit
    string kode;
    // kode berisi 9 digit :
    // 1. 4 digit tahun lahir
    // 2. 2 digit bulan lahir
    // 3. 2 digit tanggal lahir
    // 4. 3 digit urutan
    string nama;
    string alamat;
    TTL ttl;
    string email;
    string password;
    bool status;// status berisi 1/0
    // 1 = belum mengembalikan
    // 0 = sudah menembalikan
};

struct data_admin
{
    string id;
    string username;
    string passwd;
    string nama;
};

struct buku
{
    string id_buku;
    string isbn;
    string judul;
    string pengarang;
    string penerbit;
    string tahun_terbit;
    int stock;
};
struct peminjaman
{
    string id_pemminjaman;
    string id_anggota;
    string id_buku;
    string tanggal_pinjam;
    string tanggal_kembali;
    string status;
    string denda;
};

void daftar(data_anggota anggota){
    
    cout << "daftar akun!" <<endl;
    cout << "nama : ";
    getline(cin,anggota.nama);
    
    cout << "tempat tangal lahir(contoh format tulungagung,10 12 2009/jika tidak mirip ada kemungkinan bug pada sistem!)"<<endl;
    cout << "tempat : ";
    getline(cin,anggota.ttl.tempat);
    cout << "tanggal,bulan,tahun : ";
    cin >> anggota.ttl.tgl;
    cin >> anggota.ttl.bulan;
    cin >> anggota.ttl.tahun;

    cout << "email : ";
    cin.ignore();
    getline(cin,anggota.email);
    cout << "password : ";
    getline(cin,anggota.password);
    cout << "konfirmmasi password : ";
    getline(cin,anggota.password);

    string tgl,bulan,tahun;
    string baris;
    int urutan = 1;
    tgl = to_string(anggota.ttl.tgl);
    bulan = to_string(anggota.ttl.bulan);
    tahun = to_string(anggota.ttl.tahun);
    {
        ifstream bacafile("data.txt");
        while (getline(bacafile,baris))
        {
            if (baris.find("nama") != string::npos) //kondisi berisi pencarian kata kunci "nama"
            {
                urutan++;
            }
        }
    
    }
    if (urutan == 0)
    {
        urutan = urutan + 1;
    }
    
    string urutanstr = to_string(urutan);
    if (urutan < 10) 
    {
        urutanstr = "00" + urutanstr;
    }
    else if (urutan < 100) 
    {
        urutanstr = "0" + urutanstr;
    }

    ofstream file("data.txt",ios::app);
    if(file.is_open()){
        file << endl;
        file << "nama : " << anggota.nama << endl;
        file << "kode : " << tahun + bulan + tgl + urutanstr <<endl;
        file << "ttl : " << anggota.ttl.tempat 
             << ", "<<tgl << ", "<< bulan
             << ", "<< tahun<<endl;
        file << "email : "<< anggota.email<<endl;
        file << "password : "<< anggota.password<<endl;
    }
}

void login(){

}



int main(){
    data_anggota anggota;
    daftar(anggota);
}