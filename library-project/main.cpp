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

struct ISBN // Prefix – Kode Negara – Kode Penerbit – Nomor Buku – Check Digit
{
    string previx;// 978
    string kodenegara;// milik indonesia 608
    string kodepenerbit;
    string nomorbuku;
    string checkdigit;// rumus check digit = (10 - (sum(products) % 10)) % 10
    // contoh nyata
    /*
        Digit : 9 7 8 6 0 2 0 3 1 2 3 4
        Posisi: 1 2 3 4 5 6 7 8 9 10 11 12
        Bobot : 1 3 1 3 1 3 1 3 1 3  1  3
        kalikan bergantian 1 dan 3:
        (9×1) + (7×3) + (8×1) + (6×3) + (0×1) + (2×3) + (0×1) + (3×3) + (1×1) + (2×3) + (3×1) + (4×3)
        Hasilnya = 93(ini adalah sum(products))
        
    */
};

struct buku
{
    // string id_buku;
    // ISBN isbn;
    // string judul;
    // string pengarang;
    // string penerbit;
    // string tahun_terbit;
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

void checkdigit(int arrdariisbn[],int hasil[]){
    int hasilawal = 0;
    int temp;
    // memindahkan nilai arr
    for (int i = 0; i < 13; i++)
    {
        hasil[i] = arrdariisbn[i]; 
    }
    // pencarian digit
    for (int i = 0; i < 12; i++)
    {
        if (i % 2 == 0)
        {
            temp = arrdariisbn[i] * 1;
            arrdariisbn[i];
        }
        else{
            temp = arrdariisbn[i] * 3;
            arrdariisbn[i];
        }
        
    }
    // sum/jumlah
    for (int i = 0; i < 12; i++)
    {
        hasilawal += arrdariisbn[i];
    }
    hasilawal = (10 - (hasilawal % 10)) % 10;
    hasil[12] = hasilawal;
    cout << endl;
    cout << "digit : " << hasilawal<<endl;
    for (int i = 0; i < 13; i++)
    {
        cout << hasil[i]<< " ";
    }
    

}

void isbn(int hasilisbn[],string nomorbukustr){
    // Prefix – Kode Negara – Kode Penerbit – Nomor Buku – Check Digit
    string prefixstr = "978";
    string kodenegarastr = "602";
    string kodepenerbitstr = "999";
    string sementara = prefixstr + kodenegarastr + kodepenerbitstr + nomorbukustr;
    int digit[12];
    cout << sementara<<endl;
    cout << sementara[1]<<endl;
    for (int i = 0; i < 12; i++)
    {
        digit[i] = sementara[i] - '0'; // angka 0 karena kode asci 0 adalah 48
    }
    cout << "isbn seentara tanpa validasi digit : ";
    for (int i = 0; i < 12; i++)
    {
        cout << digit[i];
    }
    checkdigit(digit,hasilisbn);

    
}


void tambahbuku(){
    string judulbuku,penerbit,pengarang,tahunterbit;
    
    int stock;
    int urutanbuku = 1,id = 1; //  urutan buku dan id itu beda,urutan buku untuk isbn

    // input
    #pragma region input
    cout << "masukkan judul buku : ";
    getline(cin,judulbuku);
    cout << "penerbit : ";
    getline(cin,penerbit);
    cout << "pengarang : ";
    getline(cin,pengarang);
    cout << "tahun terbit : ";
    getline(cin,tahunterbit);
    #pragma endregion

    //urutan buku
    #pragma region urutan buku isbn

    {
        string baris;
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            while (getline(bacafile,baris))
            {
                size_t posisi = baris.find("judul buku :");
                if (posisi != string::npos)
                {
                    if (baris.find(judulbuku) != string::npos)
                    {
                        urutanbuku = 1;
                        break;
                    }
                    else{;
                        urutanbuku++;
                    }
                }
                
            }
            cout << urutanbuku<<endl<<"diluar while"<<endl;
            
        }
        else{
            cout << "gagal membuka file!"<<endl;
        }
    }

    string urutanbukustr = to_string(urutanbuku);
    if (urutanbuku < 10)
    {
        urutanbukustr = "00" + urutanbukustr;
    }
    else if (urutanbuku < 100)
    {
        urutanbukustr = "0" + urutanbukustr;
    }
    
    #pragma endregion

    //id
    #pragma region id buku

    {
        ifstream bacafile("buku.txt");
        string baris;
        if (bacafile.is_open())
        {
            while (getline(bacafile,baris))
            {
                size_t posisi = baris.find("judul buku : ");
                if (posisi != string::npos)
                {
                    id++;
                }
            }
        }
    }
    string idstr = to_string(id);
    if (id < 10)
    {
        idstr = "00000" + idstr;
    }
    else if (id < 100)
    {
        idstr = "0000" + idstr;
    }
    else if (id < 1000)
    {
        idstr = "000" + idstr;
    }
    else if (id < 10000)
    {
        idstr = "00" + idstr;
    }
    else if (id < 100000)
    {
        idstr = "0" + idstr;
    }
    
    #pragma endregion
    
    int hasilisbn[13];
    isbn(hasilisbn,urutanbukustr);

    {
        ofstream tulisfile("buku.txt",ios::app);
        if (tulisfile.is_open())
        {
            tulisfile << "judul buku : " << judulbuku << endl;
            tulisfile << "isbn : ";
            for (int i = 0; i < 13; i++)
            {
                tulisfile << hasilisbn[i];
            }
            tulisfile<< endl;
            tulisfile << "id : "<< idstr<<endl;
            tulisfile << "pengarang : " << pengarang << endl;
            tulisfile << "penerbit : " << penerbit << endl;
            tulisfile << "tahun terbit : "<<tahunterbit<<endl;
            tulisfile << endl;


        }

    }

}

// sudah selesai(jika tidak ada revisi)
void profileanggota(data_anggota anggota,string kodeakun,string email,string password,string baris1){
    cout <<endl<< "profile"<<endl;
    ifstream bacafile("anggota.txt");
    for (int i = 1; i <= 8 && getline(bacafile,baris1); i++)
    {
        cout << baris1<<endl;
    }
    cout << endl;
    
}

// belum selesai
void dasboranggota(data_anggota anggota,string kodeakun,string email,string password,string baris1){
    string menu;// variabel menu
    while (true)
    {
        cout << "dasbor anggota"<<endl;
        cout << "hai "<< email <<endl;
        cout << "1.cari"<<endl
            <<"2.pengembalian"<<endl
            <<"3.profile"<<endl
            <<"4.keluar"<<endl
            <<"input: ";
        cin >> menu;
        
        // pengecekan,menu apa yang di input oleh user
        if (menu == "1")
        {
            cout <<endl<< "pencarian"<<endl;
        }
        else if (menu == "2")
        {
            cout << endl<<"pengembalian"<<endl;
        }
        else if (menu == "3")
        {
	        profileanggota(anggota,kodeakun,email,password,baris1);
        }
        else if (menu == "4")
        {
            cout << "user memilih keluar!";
            break;
        }
        else{ // jika input tidak sesuai dengan yang ditampilkan maka looping
            cout << "input invalid!"<<endl;
            cout <<endl;
            continue;
        }
    }
    
}

// belum selesai
/*
void tampildataanggota(){
    ifstream bacafile("anggota.txt");
    string baris;
    int totalbaris = 0;
    if (bacafile.is_open())
    {
        while (getline(bacafile,baris))
        {
            totalbaris++;
        }
        cout << totalbaris<<endl; 
        string nama[totalbaris],id[totalbaris],kode[totalbaris],ttl[totalbaris],alamat[totalbaris],email[totalbaris],password[totalbaris],statusakun[totalbaris],kodeakun[totalbaris];
        

        while (getline(bacafile,kodeakun))
        {
            getline(bacafile,nama);
            getline(bacafile,id);
            getline(bacafile,kode);
            getline(bacafile,ttl);
            getline(bacafile,alamat);
            getline(bacafile,email);
            getline(bacafile,password);
            getline(bacafile,statusakun);
        }
        
        
    }
    
}
*/
//belum selesai
void dasboradmin(){
    cout << "1.tampil data anggota"<<endl;
    tambahbuku();
    // tampildataanggota();
}

// sepertinya sudah selesai
void daftar(data_anggota anggota){
    
    string tgl,bulan,tahun;
    string baris;
    string konfirmasi;// konfirmasi password
    string kodeakun; // berisi gabungan email dan password
    int urutan = 1;
    int id = 1;

    //input data
    cout << "daftar akun!" <<endl;
    cout << "nama : ";
    cin.ignore();
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
    
    // pembuatan id angka pada akun
    {
        ifstream bacafile("anggota.txt");
        if (bacafile.is_open())
        {
            while (getline(bacafile,baris))// mengambil file dari baca file lalu di input ke baris
            {
                if (baris.find("nama : ") != string::npos)// pencarian kata kunci di baris
                {
                    id++;
                }
                
            }
            
        }
        else
        {
            cout << "gagal membuka file!"<<endl;
        }
        
    }
    string idstr = to_string(id);
    if (id < 10) //jika urutan kurang dari 10
    {
        idstr = "00000" + idstr; //contoh 000003
    }
    else if (id < 100) // urutan kurang dari 100 
    {
        idstr = "0000" + idstr;//contoh 000011
    }
    else if (id < 1000)
    {
        idstr = "000" + idstr;
    }
    else if (id < 10000)
    {
        idstr = "00" + idstr;
    }

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
        file << "kode akun : " << kodeakun<<endl;
        file << "nama : " << anggota.nama << endl;
        file << "id : " << idstr<<endl;
        file << "kode : " << tahun + bulan + tgl + urutanstr <<endl;
        file << "ttl : " << anggota.ttl.tempat 
             << ", "<<tgl << ", "<< bulan
             << ", "<< tahun<<endl;
        file << "alamat : "<< anggota.alamat << endl;
        file << "email : "<< anggota.email<<endl;
        file << "password : "<< anggota.password<<endl;
        file << "status akun : "<<anggota.status<<endl;
    } 
}

// hampir selesai atau malah sudah selesai
void login(data_anggota anggota,data_admin admin){
    //deklarasi variabel
    ifstream bacafileanggota("anggota.txt");
    ifstream bacafileadmin("admin.txt");
    string passwordlog,emaillog,kodeakunlog;// input log
    string nama1,kode1,ttl1,alamat1,pass1,kodeakun1,email1;// anggota
    string nama2,kode2,ttl2,alamat2,pass2,kodeakun2,email2;//admin
    string baris1,baris2;
    int jumlah = 0;

    cout << "login" <<endl;
    cout << "email : ";
    cin.ignore();// menghilangkan beffer
    getline(cin,emaillog);
    cout << "password : ";
    getline(cin,passwordlog);
    kodeakunlog = emaillog + "-" + passwordlog;// pembuatan kode akun khusus login 

    if (bacafileanggota.is_open())
    {
        bool ditemukan = false;// ditemukan bernilai false
        while (getline(bacafileanggota,baris1))
        {
    
            size_t posisi1 = baris1.find(kodeakunlog);// pencarian kode akun
            if (posisi1 != string::npos)
            {
                ditemukan = true;
                kodeakun1 = baris1.substr(posisi1);// pengambilan kalimat
                email1 = kodeakun1.substr(0,kodeakun1.find('-'));// memotong kalimat dari posisi 0 sampai bertemu dengan '-'
                pass1 = kodeakun1.substr(kodeakun1.find('-') + 1,kodeakun1.find('\n')); // memotong kalimat dari posisi '-'+1 (+ 1 supaya '-' tidak ikut) sampai bertemu dengan '\n' atau newline atau endl

		        // buat tes atau buat debug doang
                /*cout << kodeakun1 << endl;
                cout << email1<<endl;
                cout << pass1<<endl;
                cout <<baris1<<endl;*/
                /*for(int i = 1;i <= 8 && getline(bacafileanggota,baris1);i++){
			        cout << baris1 <<endl;
			
		        }*/
                
                
            
            }
        
        }
    }
    // kurang lebih sama seperti yang anggota,cumman ini admmmin
    if (bacafileadmin.is_open())
    {
        bool ditemukan = false;
        while (getline(bacafileadmin,baris2))
        {
            size_t posisi2 = baris2.find(kodeakunlog);
            if (posisi2 != string::npos)
            {
                ditemukan = true;
                kodeakun2 = baris2.substr(posisi2);
                cout << posisi2 <<endl;
                email2 = kodeakun2.substr(0,kodeakun2.find('-'));
                pass2 = kodeakun2.substr(kodeakun2.find("-") + 1,kodeakun2.find('\n'));
                cout << kodeakun2.length()<<endl;
                cout << email2 <<endl;
                cout << pass2<<endl;
                
            }
            
        }
        
    }
    // pengecekan apakah input login ada di data anggota atau admin atau malah akun tidak ada
    if (kodeakun1 == kodeakunlog) // jika anggota
    {
        dasboranggota(anggota,kodeakun1,email1,pass1,baris1);
    }
    else if (kodeakun2 == kodeakunlog) // jika admin
    {
        dasboradmin();
    }
    else{ // jika tidak ditemukan 
        cout << "akun tidak ditemukan!";
    }
    
}

int main(){
    string menu;
    data_anggota anggota;
    data_admin admin;
    while (true)
    {
        cout <<"1.login!"<<endl
        << "2.daftar!"<<endl
        << "3.keluar"<<endl
        << "input : ";
        cin >> menu;
        if (menu == "1")
        {
            login(anggota,admin);
            break;
        }
        else if (menu == "2")
        {
            daftar(anggota);    
            
            login(anggota,admin);
            break;
        }
        else if (menu == "3")
        {
            cout << "user memilih keluar"<<endl;
            break;
        }
        
        else{
            cout << "input invalid!"<<endl;
            cout <<endl;
            continue;
        }
        
    }
    tambahbuku();
}
