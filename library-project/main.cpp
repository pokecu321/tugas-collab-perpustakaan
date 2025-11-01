#include <iostream>
#include <fstream>// file handling
#include <string>// manipulasi string
#include <limits>// membuang buffer
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
    
    string tgl,bulan,tahun;
    string baris;
    string konfirmasi;// konfirmasi password
    string kodeakun; // berisi gabungan email dan password
    int urutan = 1;

    cout << "daftar akun!" <<endl;
    cout << "nama : ";
    getline(cin,anggota.nama);
    cout << "tempat tangal lahir(contoh format tulungagung,10 12 2009/jika tidak mirip ada kemungkinan bug pada sistem!)"<<endl;
    cout << "tempat : ";
    getline(cin,anggota.ttl.tempat);
    
    while (true)
    {
        cout << "tanggal : ";
        cin >> anggota.ttl.tgl;
        if (cin &&  anggota.ttl.tgl<= 31)
        {
            break;
        }
        else{
            cout << "format salah,mohon input ulang!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }

    while (true)
    {
        cout << "bulan : ";
        cin >> anggota.ttl.bulan;
        if (cin &&  anggota.ttl.bulan <= 12)
        {
            break;
        }
        else{
            cout << "format salah,mohon input ulang!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    
    while (true)
    {
        cout << "tahun : ";
        cin >> anggota.ttl.tahun;
        if (cin)
        {
            break;
        }
        else{
            cout << "input salah,mohon input ulang!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    

    cout << "alamat : ";
    cin.ignore();
    getline(cin,anggota.alamat);

    cout << "email : ";
    getline(cin,anggota.email);
    
    while (true)
    {
        cout << "password : ";
        getline(cin,anggota.password);
        cout << "konfirmasi password : ";
        getline(cin,konfirmasi);
        if (anggota.password == konfirmasi)
        {
            break;
        }
        else{
            cout << "password tidak sama!(tekan enter atau apa saja untuk lanjut XD)"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        
    }
    
    tgl = to_string(anggota.ttl.tgl);
    bulan = to_string(anggota.ttl.bulan);
    tahun = to_string(anggota.ttl.tahun);
    kodeakun = anggota.email +"-"+ anggota.password;
    
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
        file << "alamat : "<< anggota.alamat << endl;
        file << "email : "<< anggota.email<<endl;
        file << "password : "<< anggota.password<<endl;
        file << "kode akun : " << kodeakun<<endl;
    }   

}
    


void login(){

}


int main(){
    data_anggota anggota;
    daftar(anggota);
}