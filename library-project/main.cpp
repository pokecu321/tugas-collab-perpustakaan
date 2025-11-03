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

    //input data
    cout << "daftar akun!" <<endl;
    cout << "nama : ";
    getline(cin,anggota.nama);
    cout << "tempat tangal lahir(contoh format tulungagung,10 12 2009/jika tidak mirip ada kemungkinan bug pada sistem!)"<<endl;
    cout << "tempat : ";
    getline(cin,anggota.ttl.tempat);
    
    // input ttl
    while (true) // input tanggal
    {
        cout << "tanggal : ";
        cin >> anggota.ttl.tgl;
        if (cin &&  anggota.ttl.tgl<= 31) //jika input int dan kurang dari atau sama dengan 31 maka looping berhenti
        {
            break;//mengakhiri looping
        }
        else{//atau jika input selain int dan lebih dari 31 maka looping di jalan kan
            cout << "format salah,mohon input ulang!" << endl;
            cin.clear();//mengahapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');// menghapus buffer
        }
    }

    while (true)// input bulan
    {
        cout << "bulan : ";
        cin >> anggota.ttl.bulan;
        if (cin &&  anggota.ttl.bulan <= 12)//jika input int dan kurang dari atau sama dengan 12 maka looping berhenti
        {
            break; // mengakhiri looping
        }
        else{//atau jika input selain int dan lebih dari 12 maka looping di jalan kan
            cout << "format salah,mohon input ulang!"<<endl;
            cin.clear();//menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
    }
    
    while (true)//input tahun
    {
        cout << "tahun : ";
        cin >> anggota.ttl.tahun;
        if (cin)// jika input adalah int maka looping berhenti
        {
            break;
        }
        else{// jika tidak maka looping dijalankan
            cout << "input salah,mohon input ulang!"<<endl;
            cin.clear();//menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer(berhenti jika bertemu dengan newline atau endl)
        }
    }
    
    
    cout << "alamat : ";
    cin.ignore();//menghapus buffer
    getline(cin,anggota.alamat);

    cout << "email : ";
    getline(cin,anggota.email);
    
    //password
    while (true)// looping terus sampai ada break;
    {
        cout << "password : ";
        getline(cin,anggota.password);//input password
        cout << "konfirmasi password : ";
        getline(cin,konfirmasi);//input konfirmasi password
        //pengecekan kondisi"apakah password dan konfirmasi sama?"
        if (anggota.password == konfirmasi)//jika sama maka looping di hentikan
        {
            break;//memberi tanda ke looping bahwa looping berhenti
        }
        else{//jika tidak sama maka looping masih berlanjut
            cout << "password tidak sama!(tekan enter atau apa saja untuk lanjut XD"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
        
    }
    // konversi dari int menjadi string menggunakan stl string atau #include <string>
    tgl = to_string(anggota.ttl.tgl);
    bulan = to_string(anggota.ttl.bulan);
    tahun = to_string(anggota.ttl.tahun);
    //kode akun(untuk mempermudah saat sesi login)
    kodeakun = anggota.email +"-"+ anggota.password;
    
    //pembuatan kode angka pada akun
    {
        ifstream bacafile("anggota.txt");//inisialisasi variabel
        if (bacafile.is_open())
        {
            while (getline(bacafile,baris))// mengambil file dari anggota.txt lalu di masukkan ke baris
            {
                if (baris.find("kode : " + tahun + bulan + tgl ) != string::npos) //kondisi berisi pencarian kata kunci "kode : angka" 
                {//jika dalam baris di temukan tgl,bulan,tahun yang sama maka kode akun bagian 3 digit terakhir akan ter increment
                    urutan++;//increment
                }
            }
        }
        else{
            cout << "gagal membuka file YAHHAHAHHAH!" <<endl;
        }
        
    
    }
    //konversi int menjadi string
    string urutanstr = to_string(urutan);
    if (urutan < 10) //jika urutan kurang dari 10
    {
        urutanstr = "00" + urutanstr; //contoh 003
    }
    else if (urutan < 100) // urutan kurang dari 100 
    {
        urutanstr = "0" + urutanstr;//contoh 011
    }
    //menulis file ke anggota.txt
    ofstream file("anggota.txt",ios::app);
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
    


void login(data_anggota anggota,data_admin admin){
    ifstream bacafileanggota("anggota.txt");
    ifstream bacafileadmin("admin.txt");
    string password,email,kodeakun2;
    string nama,kode,ttl,alamat,pass,kodeakun,emaillagi;
    string baris;
    int jumlah = 0;

    cout << "login" <<endl;
    cout << "email : ";
    getline(cin,email);
    cout << "password : ";
    getline(cin,password);
    kodeakun2 = email + "-" + password;
    cout << kodeakun2; 
    
    while (getline(bacafileanggota,baris))
    {
        jumlah++;
    }
    

    
    
    
    
    
    
}


int main(){
    data_anggota anggota;
    data_admin admin;
    daftar(anggota);
    // login(anggota,admin);
}