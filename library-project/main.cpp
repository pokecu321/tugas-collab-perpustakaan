#include <iostream>
#include <fstream>// file handling
#include <string>// manipulasi string
#include <limits>// membuang buffer
#include<cstdlib>// untuk membuat fungsi clear!(gara gara dulu pernah dikasih tahu pak badrus)
#include<ctime>

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
    // kode berisi 11 digit :
    // 1. 4 digit tahun lahir
    // 2. 2 digit bulan lahir
    // 3. 2 digit tanggal lahir
    // 4. 3 digit urutan
    string nama;
    string alamat;
    TTL ttl;
    string email;
    string password;
    bool status = 1;// status berisi 1/0
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
    int previx;// 978
    int kodenegara;// milik indonesia 608
    int kodepenerbit;
    int nomorbuku;
    int checkdigit;// rumus check digit = (10 - (sum(products) % 10)) % 10
    
};

struct buku
{
    // string id_buku;
    // ISBN isbn;
    // string judul;
    // string pengarang;
    // string penerbit;
    // string tahun_terbit;
    // int stock;
};
struct peminjaman
{
    string id_peminjaman;
    string id_anggota;
    string id_buku;
    string tanggal_pinjam;
    string tanggal_kembali;
    string status;
    string denda;
};

struct waktutanggal{
    int tgl;
    int bulan;
    int tahun;
};

// menajalankan command line "clear" / "cls" untuk membersihkan terminal
void clearCMD_ln(){
    system("cls");
}

// waktu
waktutanggal waktunyata(){
    time_t now = time(0);// time_t = tipe data detik, now = variabel, time(0) = fungsi untuk ambil waktu sekarang dalam detik

    tm t = *localtime(&now);// 

    waktutanggal waktu;
    waktu.tgl = t.tm_mday;
    waktu.bulan = t.tm_mon + 1;// karena berisi 0 - 11
    waktu.tahun = t.tm_year + 1900; // karena pertama kali tahun terbaca oleh system adalah tahun 1900
    return waktu;
}


string fiksi(){
    int status;
    while (true)
    {
        
        cout << endl;
        cout << "fiksi"<<endl
            << "1.fiksi umum"<<endl
            << "2.fantasy"<<endl
            << "3.fiksi ilmiah"<<endl
            << "4.misteri / detektif"<<endl
            << "5.horor"<<endl
            << "6.petualangan"<<endl
            << "7.roman"<<endl
            << "8.fiksi sejarah"<<endl
            << "9.young adult"<<endl
            << "input : ";
        cin >> status;
        if (cin &&( 0 < status && status <= 9))
        {
            break;
        }
        else{
            cout << "input invalid!"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
        cout << endl;
    }    

    string statusstr = to_string(status);// konversi int ke string
    return "0" + statusstr;// mengembalikan nilai 

}

string nonfiksi(){
   
    int status;
    while (true)
    {
        
        cout << endl;
        cout << "pilih"<<endl
            << "1.sejarah"<<endl
            << "2.sains"<<endl
            << "3.biografi"<<endl
            << "4.sosial dan budaya"<<endl
            << "5.motivasi / pengembangan diri"<<endl
            << "6.teknologi"<<endl
            << "7.kesahatan"<<endl
            << "input : ";
        cin >> status;
        if (cin && ( 0 < status && status <= 7))
        {
            cout <<"berhasil"<<endl;
            break;
        }
        else{
            cout << "invalid!"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
        cout << endl;
    }
    string statusstr = to_string(status);// konversi int ke string
    return "1" + statusstr;// mengembalikan nilai 
}

string kodebuku(){
    string status;
    string kode;
    while (true)
    {
        cout << endl;
        cout << "status"<<endl
            << "0.fiksi"<<endl
            << "1.nonfiksi"<<endl
            << "input : ";
        cin >> status;
        if (status == "0")
        {
            cout << "fiksi"<<endl;
            kode = fiksi();
            
            break;
        }
        else if (status == "1")
        {
            cout << "nonfiksi"<<endl;
            kode = nonfiksi();
           
            break;
        }
        else{
            cout << "input invalid!"<<endl;
        }

    }
    cout << endl;
    //id
    #pragma region id buku
    
    int id = 1;
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
        idstr = kode + "000" + idstr;
    }
    else if (id < 100)
    {
        idstr = kode + "00" + idstr;
    }
    else if (id < 1000)
    {
        idstr = kode + "0" + idstr;
    }
    else if (id < 10000)
    {
        idstr =  kode + idstr;
    }
    else if (id < 100000)
    {
        idstr =  kode + idstr;
    }
    
    #pragma endregion
    
    return idstr;

}


void tambahbuku(){
    // inisialisasi variabel
    string judulbuku,penerbit,pengarang,tahunterbitstr;
    string isbnstr;
    ISBN isbn;
    int stock,tahunterbit;

    // input
    #pragma region input
    cin.ignore();// menghapus buffer
    cout << "masukkan judul buku : ";
    getline(cin,judulbuku);
    for (int i = 0; i < judulbuku.length(); i++)// konversi ke lower case
    {
        judulbuku[i] = tolower(judulbuku[i]);// konversi
    }
    
    cout << "penerbit : ";
    getline(cin,penerbit);
    cout << "pengarang : ";
    getline(cin,pengarang);
    while (true)// looping
    {
        
        cout << "tahun terbit : ";
        cin >> tahunterbit;
        tahunterbitstr = to_string(tahunterbit);// konversi ke string
        if (cin && tahunterbit && tahunterbitstr.length() == 4 )// pengecekan input dan panjang nilai
        {
            break;
        }
        else{
            cout << "gagal"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
        
        
    }
    while (true)
    {
        cout << "stock : ";
        cin >> stock;//input stock

        if (cin && stock > 0)// pengecekan nilai input
        {
            break;
        }
        else{
            cout << "gagal"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
    }
    
    #pragma region isbn coy
    while (true)
    {
        cout <<endl
            << "======"<<endl;
        cout << "isbn "<<endl
            << "prefiks(default tidak boleh di ganti): 978/979"<<endl
            << "kode negara(indonesia : 608)"<<endl
            << "kode penerbit(biasanya perpustakaan)"<<endl
            << "urutan judul buku / nomor buku"<<endl
            << "check digit"<<endl
            << "isbn berisi 13 digit!"<<endl;
        
        // prefiks
        while (true)
        {
            cout <<"input prefiks: ";
            cin >> isbn.previx;
            if (cin && isbn.previx && isbn.previx == 978 || isbn.previx == 979)
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();// menghapus sisa input yang salah
                cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
            }
        }

        // kode negara
        while (true)
        {
            cout <<"input kode negara: ";
            cin >> isbn.kodenegara;
            if (cin && isbn.kodenegara)
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();// menghapus sisa input yang salah
                cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
            }
        }

        // kode pernerbit
        while (true)
        {
            cout <<"input penerbit: ";
            cin >> isbn.kodepenerbit;
            if (cin && isbn.kodepenerbit)
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();// menghapus sisa input yang salah
                cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
            }
        }

        // nomor buku
        while (true)
        {
            cout <<"input nomor buku : ";
            cin >> isbn.nomorbuku;
            if (cin && isbn.nomorbuku)// pengecekan input
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();// menghapus sisa input yang salah
                cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
            }
        }

        // checkdigit
        while (true)
        {
            cout <<"input check digit atau digit terakhir : ";
            cin >> isbn.checkdigit;
            if (cin && isbn.checkdigit)// pengecekan input
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();// menghapus sisa input yang salah
                cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
            }
        }

        // menggabung semua var menjadi satu
        isbnstr = to_string(isbn.previx) + to_string(isbn.kodenegara) + to_string(isbn.kodepenerbit) + to_string(isbn.nomorbuku) + to_string(isbn.checkdigit);
        // bukti hasil isbn
        cout << "isbn : "<< isbnstr<<endl;
        if (isbnstr.length() == 13)// pengecekan panjang isbn yang harus 13 digit
        {
            cout << "berhasil"<<endl;
            break;
        }
        else{
            cout << "invalid!"<<endl
                << "digit adalah " << isbnstr.length()<< " bukan 13!"<<endl;
        }
        
    }
    cout << endl;
    #pragma endregion

    #pragma endregion

    // menulis ke dalam file 
    string kode = kodebuku();

    {
        ofstream tulisfile("buku.txt",ios::app);
        if (tulisfile.is_open())
        {
            tulisfile << "judul buku : " << judulbuku << endl;
            tulisfile << "isbn : "<<isbnstr;
            tulisfile<< endl;
            tulisfile << "id : "<< kode<<endl;
            tulisfile << "pengarang : " << pengarang << endl;
            tulisfile << "penerbit : " << penerbit << endl;
            tulisfile << "tahun terbit : "<<tahunterbit<<endl;
            tulisfile << "stock : "<< stock<<endl;
            tulisfile << endl;

        }

    }

}


// sudah selesai(jika tidak ada revisi)
void profileanggota(data_anggota anggota,string kodeakun,string email,string password){
    cout <<endl<< "profile"<<endl;
    // inisialisai variabel
    string baris;
    ifstream bacafile("anggota.txt");
    // pengecekan apakah file terbuka atau tidak
    if (bacafile.is_open())
    {
        
        while (getline(bacafile,baris)) // memasukkan isi file anggota ke baris
        {
            
            size_t posisi = baris.find(kodeakun);// pencarian profile yang sama dengan kode akun
            if (posisi != string::npos)
            {
                for(int i = 1;i <= 8 && getline(bacafile,baris);i++){
	                cout << baris <<endl;
                
                }

            
            }

        }

    }
    else{
        cout << "gagal membuka!"<<endl;
    }
    cout << endl;
}


void carianggota(){
    
}

// sudah selesai

void tampildataanggota(){
     
    int totalbaris = 0,index = 0;
    
    // mencari total baris
    {
    ifstream bacafile("anggota.txt");
        if (bacafile.is_open())
        {
            string baris1;
            while (getline(bacafile,baris1))
            {
                size_t posisi = baris1.find("nama : ");
                if (posisi != string::npos)
                {
                    totalbaris++;
                }

            }
        }
    }
    
    int menu;
    string tmp,idstr[totalbaris];
    string nama[totalbaris],ttl[totalbaris],alamat[totalbaris],email[totalbaris],password[totalbaris],statusakun[totalbaris],kodeakun[totalbaris];
    long long id[totalbaris],kode[totalbaris];
    /* penjelasan 
        kenapa long long?kenapa tidak int?
        karena batas int adalah 2147483647 atau 10 digit,sedangkan
        isi dari kode akun berisi 11 digit.
        jika bertanya "kenapa kok tidak long bang?",
        karena long tidak pasti nilai nya/bit nya,yang mana 
        pada saat saya baca baca di ai,long terkadang 32 bit dan 64 bit,
        sedangkan int 32 bit dan long long adalah 64 bit
        
        yapping dikit hehe
        -adin
    */
    
    // ambil data
    {
        
        ifstream bacafile("anggota.txt");
        if (bacafile.is_open())
        {
            
            
            string baris;

            while (getline(bacafile,baris))
            {
               
                if ((baris.find("nama : ")) != string::npos)
                {
                    nama[index] = baris.substr(baris.find(":")+1);//mengambil nilai setelah kata kunci ":"
                    while (nama[index][0] == ' '){//mengapus spasi di awal kalimat supaya rapi
                        nama[index].erase(0,1);
                
                    }
                    
                }

                if ((baris.find("kode akun : ")) != string::npos)
                {
                    kodeakun[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (kodeakun[index][0] == ' ')
                    {
                        kodeakun[index].erase(0,1);
                    }
                     
                }

                if ((baris.find("id : ")) != string::npos)
                {
                    string tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    idstr[index] = tmp;
                    while (idstr[index][0] == ' ')
                    {
                        idstr[index].erase(0,1);
                    }
                    
                    id[index] = atoi(tmp.c_str());
                
                }

                if ((baris.find("kode : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    kode[index] = stoll(tmp.c_str());
                   
                }

                if ((baris.find("ttl : ")) != string::npos)
                {
                    ttl[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (ttl[index][0] == ' ')
                    {
                        ttl[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("alamat : ") != string::npos))
                {
                    alamat[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (alamat[index][0] == ' ')
                    {
                        alamat[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("email : ")) != string::npos)
                {
                    email[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (email[index][0] == ' ')
                    {
                        email[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("password : ")) != string::npos)
                {
                    password[index]= baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (password[index][0] == ' ')
                    {
                        password[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("status akun : ")) != string::npos)
                {
                    statusakun[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (statusakun[index][0] == ' ')
                    {
                        statusakun[index].erase(0,1);
                    }
                    index++;
                }
                                                
            }
            
        
        
        }   
    }
    

    bool out = false;
    // tampilan
    while (true)
    {    

        cout << endl;
        cout << "1.id"<<endl
            << "2.kode"<<endl
            << "3.nama"<<endl
            << "4.cari anggota berdasarkan kode anggota"<<endl
            << "0.kembali!"<<endl
            << "input : ";
        cin >> menu;

        if (cin)
        {
            switch (menu)
            {
                case 1:
                {
                    cout << "id"<<endl
                        <<"id \t| kode\t      |status| ttl \t\t\t |nama \t\t | email \t\t | passwd "<<endl;
                    for (int i = 0; i < index; i++)
                    {
                        cout << idstr[i]<<"\t|"<<kode[i]<< "  |"<< statusakun[i]<<"    |"<<ttl[i]<<"\t |" <<nama[i] <<"\t | " <<email[i]<< "\t |"<< password[i] <<endl; 
                    }
                    break;
                }

                case 2:
                {

                    // sort
                    for (int i = 0; i < index - 1 ; i++)
                    {
                        for (int j = 0; j < index - i - 1; j++)
                        {
                            if (kode[j] > kode[j + 1])
                            {
                                swap(kode[j],kode[j + 1]);
                                swap(nama[j],nama[j + 1]);
                                swap(id[j],id[j + 1]);
                                swap(idstr[j],idstr[j + 1]);
                                swap(ttl[j],ttl[j + 1]);
                                swap(statusakun[j],statusakun[j + 1]);
                                swap(email[j],email[j + 1]);
                                swap(password[j],password[j + 1]);
                                swap(kodeakun[j],kodeakun[j + 1]);

                            }

                        }

                    }
                    // output
                    cout << "kode"<<endl
                        <<"kode\t   | id\t    |status| ttl \t\t\t |nama \t\t\t | email \t\t | passwd "<<endl;
                    for (int i = 0; i < index; i++)
                    {
                        cout << kode[i]<<"|"<<idstr[i]<< "  |"<< statusakun[i]<<"    |"<<ttl[i]<<"\t |" <<nama[i] <<"\t\t | " <<email[i]<< "\t |"<< password[i]<<endl; 
                    }

                    break;
                }

                case 3:
                {

                    // sort 
                    for (int i = 0; i < totalbaris - 1; i++)
                    {
                        for (int j = 0; j < totalbaris - i - 1; j++)
                        {
                            if (nama[j] > nama[j + 1])
                            {
                                swap(kode[j],kode[j + 1]);
                                swap(nama[j],nama[j + 1]);
                                swap(id[j],id[j + 1]);
                                swap(idstr[j],idstr[j + 1]);
                                swap(ttl[j],ttl[j + 1]);
                                swap(statusakun[j],statusakun[j + 1]);
                                swap(email[j],email[j + 1]);
                                swap(password[j],password[j + 1]);
                                swap(kodeakun[j],kodeakun[j + 1]);

                            }
                            
                        }
                        
                    }
                    
                    //output
                    cout << "nama"<<endl
                        <<"nama \t\t | id\t    |status| ttl \t\t\t | kode \t| email \t\t  | passwd "<<endl;
                    for (int i = 0; i < totalbaris; i++)
                    {
                        cout << nama[i] << "\t | " << idstr[i] <<"   | "<< statusakun[i]<< " | " << ttl[i]<<" \t |"<< kode[i]<< "\t| "<< email[i]<< "\t  | "<< password[i]<<endl;
                    }
                    
                    break;
                }

                case 4:
                {
                    string cari;
                    string kodestr[index];
                    bool ditemukan = false;
                    cout << "cari anggota"<<endl
                        << "input kode anggota : ";
                    cin >> cari;
                    for (int i = 0; i < index; i++)
                    {
                        kodestr[i] = to_string(kode[i]);
                        if (kodestr[i] == cari)
                        {
                            cout << "ditemukan!"<<endl
                                <<endl;
                            cout <<"kode\t   | id\t    |status| ttl \t\t\t |nama \t\t\t | email \t\t | passwd "<<endl;

                            cout << kode[i]<<"|"<<idstr[i]<< "  |"<< statusakun[i]<<"    |"<<ttl[i]<<"\t |" <<nama[i] <<"\t\t | " <<email[i]<< "\t |"<< password[i]<<endl; 
                    
                            ditemukan = true;
                            break;
                        }
                        
                    }
                    if (!ditemukan)
                    {
                        cout << "data tidak ditemukan!"<<endl;
                    }
                    
                    
                }


                case 0:
                {
                    out = true;
                    break;
                }

                default:
                cout << "menu tidak ditemukan"<<endl
                    <<endl;
                    break;
            }
            if (out)
            {
            
                break;
            }
        }
        else{
            cout << "hanya angka!"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }

        
    }
    cout << endl;
}


void tampiladmin(){

    int totalbaris = 0,index = 0;
    
    // mencari total baris
    {
        ifstream bacafile("admin.txt");
        if (bacafile.is_open())
        {
            string baris1;
            while (getline(bacafile,baris1))
            {
                size_t posisi = baris1.find("kode akun : ");
                if (posisi != string::npos)
                {
                    totalbaris++;
                }

            }
        }
    }
    
    string tmp,baris,nama[totalbaris],kodeakun[totalbaris],idstr[totalbaris],email[totalbaris],pass[totalbaris];
    int id[totalbaris];

    {
        ifstream bacafile("admin.txt");
        while (getline(bacafile,baris))
        {
            
            if ((baris.find("kode akun : ")) != string::npos)
            {
                kodeakun[index] = baris.substr(baris.find(":")+1);//mengambil nilai setelah kata kunci ":"
                while (kodeakun[index][0] == ' ')
                {
                    kodeakun[index].erase(0,1);
                }
            }
            if ((baris.find("nama : ")) != string::npos)
            {
                nama[index] = baris.substr(baris.find(":")+1);//mengambil nilai setelah kata kunci ":"
                while (nama[index][0] == ' ')
                {
                    nama[index].erase(0,1);
                }
            }
            if ((baris.find("id : ")) != string::npos)
            {
                tmp = baris.substr(baris.find(":")+1);//mengambil nilai setelah kata kunci ":"
                idstr[index] = tmp;
                while (idstr[index][0] == ' ')
                {
                    idstr[index].erase(0,1);
                }
                id[index] = atoi(tmp.c_str());
            }
            if ((baris.find("email : ")) != string::npos)
            {
                email[index] = baris.substr(baris.find(":")+1);//mengambil nilai setelah kata kunci ":"
                while (email[index][0] == ' ')
                {
                    email[index].erase(0,1);
                }
            }
            if ((baris.find("password : ")) != string::npos)
            {
                pass[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                while (pass[index][0] == ' ')
                {
                    pass[index].erase(0,1);
                }
                index++;
            }
            
        }
    }
    
    // sort
    for (int i = 0; i < totalbaris - 1; i++)
    {
        for (int j = 0; j < totalbaris - i - 1; j++)
        {
            if (nama[j] > nama[j + 1])
            {
                swap(nama[j],nama[j+1]);
                swap(idstr[j],idstr[j + 1]);
                swap(email[j],email[j + 1]);
                swap(pass[j],pass[j + 1]);
                swap(kodeakun[j],kodeakun[j + 1]);
            }
            
        }
        
    }
    cout << "nama \t\t | id \t | email \t\t | password"<<endl;
    for (int i = 0; i < totalbaris; i++)
    {
        cout << nama[i] << "\t | "<<idstr[i]<<"|"<< email[i]<< "\t\t | "<< pass[i]<<endl;
    }
    
    
    
    
}


void tampildatabuku(){

    int totalbaris = 0,index = 0;
    
    // mencari total baris
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            string baris1;
            while (getline(bacafile,baris1))
            {
                size_t posisi = baris1.find("judul buku : ");
                if (posisi != string::npos)
                {
                    totalbaris++;
                }

            }
        }
    }
    string tmp;
    string judul[totalbaris],pengarang[totalbaris],penerbit[totalbaris],idstr[totalbaris],isbn[totalbaris],status[totalbaris];
    int id[totalbaris],tahunterbit[totalbaris],stock[totalbaris];

    // baca file
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            
            string baris;
            while (getline(bacafile,baris))
            {
                if ((baris.find("judul buku : ")) != string::npos)
                {
                    judul[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (judul[index][0] == ' ')
                    {
                        judul[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("isbn : ")) != string::npos)
                {
                    isbn[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (isbn[index][0] == ' ')
                    {
                        isbn[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("id : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    id[index] = atoi(tmp.c_str());
                    idstr[index] = tmp;
                    while (idstr[index][0] == ' ')
                    {
                        idstr[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("pengarang : ")) != string::npos)
                {
                    pengarang[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (pengarang[index][0] == ' ')
                    {
                        pengarang[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("penerbit : ")) != string::npos)
                {
                    penerbit[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (penerbit[index][0] == ' ')
                    {
                        penerbit[index].erase(0,1);
                    }
                    
                }
                
                if ((baris.find("tahun terbit : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    tahunterbit[index] = atoi(tmp.c_str());
                    
                }
                
                if ((baris.find("stock : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    stock[index] = atoi(tmp.c_str());
                    
                }
                if ((baris.find("status : ")) != string::npos)
                {
                    status[index] = baris.substr(baris.find(":") + 1);
                    while (status[index][0] == ' ')
                    {
                        status[index].erase(0,1);
                    }
                    index++;
                }
                
                
                
                
            }
            
        }
        
    }

    // sort
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (id[j] > id[j+1])
            {
                swap(id[j],id[j + 1]);
                swap(idstr[j],idstr[j + 1]);
                swap(judul[j],judul[j + 1]);
                swap(isbn[j],isbn[j + 1]);
                swap(pengarang[j],pengarang[j + 1]);
                swap(penerbit[j],penerbit[j + 1]);
                swap(tahunterbit[j],tahunterbit[j + 1]);
                swap(stock[j],stock[j + 1]);
                swap(status[j],status[j + 1]);

            }
            
        }
        

    }

    int menu;
    bool out = false;
    while (true)
    {
        
        cout << endl;
        cout << "jika digit id pertama"<<endl
            << "1 = nonfiksi" <<endl
            << "0 = fiksi"<<endl;
        cout << "pilih metode tampil data!" <<endl
            << "1.id"<<endl
            << "2.nama"<<endl
            << "0.kembali"<<endl
            << "input : ";
        cin >> menu;
        if (cin)
        {
            switch (menu)
            {
                case 1:
                {

                    cout << "id \t| isbn \t\t | judul \t | pengarang \t | penerbit \t | tahun terbit | stok  | status"<<endl;
                    for (int i = 0; i < index; i++)
                    {

                        cout << idstr[i]<< " \t|" << isbn[i]<< "\t |"<< judul[i] << "\t |"<< pengarang[i]<< "\t |"<<penerbit[i]<< "\t |"<< tahunterbit[i]<< "\t\t|"<< stock[i]<< " \t|"<<status[i];
                        cout <<endl;
                    }
                    cout << endl;
                
                    break;
                }
                case 2:
                {
                    
                    // sort
                    for (int i = 0; i < index - 1; i++)
                    {
                        
                        for (int j = 0; j < index - i - 1; j++)
                        {
                            
                            if (judul[j] > judul[j + 1])
                            {
                                swap(id[j],id[j + 1]);
                                swap(idstr[j],idstr[j + 1]);
                                swap(judul[j],judul[j + 1]);
                                swap(isbn[j],isbn[j + 1]);
                                swap(pengarang[j],pengarang[j + 1]);
                                swap(penerbit[j],penerbit[j + 1]);
                                swap(tahunterbit[j],tahunterbit[j + 1]);
                                swap(stock[j],stock[j + 1]);
                                swap(status[j],status[j + 1]);
                            }

                        }
                        
                    }
                    cout << "berdasarkan judul"<<endl;
                    cout << "judul buku \t| isbn \t\t | id \t | pengarang \t | penerbit \t | tahun terbit | stok   | status"<<endl;
                    for (int i = 0; i < index; i++)
                    {
                        cout << judul[i]<< " \t|" << isbn[i]<< "\t |"<< id[i] << " |"<< pengarang[i]<< "\t |"<<penerbit[i]<< "\t |"<< tahunterbit[i]<< "\t\t|"<< stock[i]<< "\t | "<< status[i];
                        cout << endl;
                    }
                    break;

                }
                case 0:
                {
                    out = true;
                    cout << "kembali ke menu sebelum nya!"<<endl;
                    break;
                }
                default:
                    cout << "menu tidak ditemukan!"<<endl;
                    break;
    
            }
            if (out)
            {
                cout << endl;
                break;
            }
            

        }
        else{
            cout << "hanya angka"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }

    }
    


    
}


void caribuku(){

    bool out = false;
    int totalbaris = 0,index = 0;
    
    #pragma region baca file buku
    // mencari total baris
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            string baris1;
            while (getline(bacafile,baris1))
            {
                size_t posisi = baris1.find("judul buku : ");
                if (posisi != string::npos)
                {
                    totalbaris++;
                }

            }
        }
    }
    string tmp;
    string judul[totalbaris],pengarang[totalbaris],penerbit[totalbaris],idstr[totalbaris],isbn[totalbaris],tahunterbitstr[totalbaris],status[totalbaris];
    int id[totalbaris],tahunterbit[totalbaris],stock[totalbaris];

    // baca file
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            
            string baris;
            while (getline(bacafile,baris))
            {
                if ((baris.find("judul buku : ")) != string::npos)
                {
                    judul[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (judul[index][0] == ' ')
                    {
                        judul[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("isbn : ")) != string::npos)
                {
                    isbn[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (isbn[index][0] == ' ')
                    {
                        isbn[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("id : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    id[index] = atoi(tmp.c_str());
                    idstr[index] = tmp;
                    while (idstr[index][0] == ' ')
                    {
                        idstr[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("pengarang : ")) != string::npos)
                {
                    pengarang[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (pengarang[index][0] == ' ')
                    {
                        pengarang[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("penerbit : ")) != string::npos)
                {
                    penerbit[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (penerbit[index][0] == ' ')
                    {
                        penerbit[index].erase(0,1);
                    }
                    
                }
                
                if ((baris.find("tahun terbit : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    tahunterbit[index] = atoi(tmp.c_str());
                    tahunterbitstr[index] = tmp;
                    while (tahunterbitstr[index][0] == ' ')
                    {
                        tahunterbitstr[index].erase(0,1);
                    }
                }
                
                if ((baris.find("stock : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    stock[index] = atoi(tmp.c_str());
                    
                }
                if ((baris.find("status : ")) != string::npos)
                {
                    status[index] = baris.substr(baris.find(":") + 1);
                    while (status[index][0] == ' ')
                    {
                        status[index].erase(0,1);
                    }
                    index++;
                }
                
                
                
                
            }
            
        }
        
    }

    #pragma endregion    


    #pragma region tampilan
    while (true)
    {
    
        char menu;
        cout << endl 
            << "pencarian!"<<endl
            << "1.cari!"<<endl
            << "2.filter berdasarkan genre!"<<endl
            << "0.kembali!"<<endl
            << "input : ";
        cin >> menu;
        
        switch(menu)
        {
            case '1':     
            {
                string cari;
                cout << endl<<"cari!"<<endl
                    << "anda bisa mencari : judul buku ,isbn,id,pengarang,penerbit,tahun terbit"<< endl
                    << "disclaimer!,input anda akan menjadi lower case semua!"<<endl
                    << "input : ";
                cin.ignore();
                getline(cin,cari);
                for (int i = 0; i < cari.length(); i++)
                {
                    cari[i] = tolower(cari[i]);
                }
                
                cout << "anda mencari : "<< cari<<endl<<endl;
                for (int i = 0; i < index; i++)
                {
                    if (((judul[i].find(cari)) != string::npos) || 
                        ((isbn[i].find(cari)) != string::npos) || 
                        ((idstr[i].find(cari)) != string::npos) || 
                        ((pengarang[i].find(cari)) != string::npos) || 
                        ((penerbit[i].find(cari)) != string::npos) || 
                        ((tahunterbitstr[i].find(cari)) != string::npos))
                    {
                        if (status[i] == "1")
                        {
                        
                            cout << "judul buku : "<<judul[i]<<endl;
                            cout << "isbn : "<<isbn[i]<<endl;
                            cout << "id : "<< idstr[i]<<endl;
                            cout << "pengarang : "<< pengarang[i]<< endl;
                            cout << "penerbit : "<< penerbit[i] << endl;
                            cout << "tahun terbit : "<< tahunterbit[i]<< endl;
                            cout << "stock : "<< stock[i]<< endl;
                            cout << endl;
                        }
                    }
                    
                }
                
                
                break;
            }
            case '2':
            {
                string genre;
                cout << endl<< "filter!"<<endl
                    << "genre : nonfiksi(1) dan fiksi(0)"<< endl
                    << "keterangan : "<<endl
                    << "1.nonfiksi"<<endl
                    << "    1.sejarah"<<endl
                    << "    2.sains"<<endl
                    << "    3.biografi"<<endl
                    << "    4.sosial dan budaya"<<endl
                    << "    5.motivasi / pengembangan diri"<<endl
                    << "    6.teknologi"<<endl
                    << "    7.kesahatan"<<endl
                    << "0.fiksi"<<endl
                    << "    1.fiksi umum"<<endl
                    << "    2.fantasy"<<endl
                    << "    3.fiksi ilmiah"<<endl
                    << "    4.misteri / detektif"<<endl
                    << "    5.horor"<<endl
                    << "    6.petualangan"<<endl
                    << "    7.roman"<<endl
                    << "    8.fiksi sejarah"<<endl
                    << "    9.young adult"<<endl
                    << "contoh format id : genre,subgenre,urutan = 16xxxx"<<endl
                    << "                   1 = genre(nonfiksi),6 = subgenre(teknologi)"<<endl
                    << "input (jangan ada spasi): ";

                    cin >> genre;
                    for (int i = 0; i < index; i++)
                    {
                        if ((idstr[i].find(genre)) != string::npos)
                        {
                            if (status[i] == "1")
                            {
                                
                                cout << endl;
                                cout << "judul buku : "<<judul[i]<<endl;
                                cout << "isbn : "<<isbn[i]<<endl;
                                cout << "id : "<< idstr[i]<<endl;
                                cout << "pengarang : "<< pengarang[i]<< endl;
                                cout << "penerbit : "<< penerbit[i] << endl;
                                cout << "tahun terbit : "<< tahunterbit[i]<< endl;
                                cout << "stock : "<< stock[i]<< endl;
                                cout << endl;
                            }
                        }
                        
                    }
                    
                    

                break;
            }
            
            case '0':
                cout << endl << "user memilih kembali!"<<endl;
                out = true;
                break;

            default:
                cout << endl
                    << "input invalid"<<endl;
                continue;
        }

        if (out)
        {
            break;
        }
        
    }
    #pragma endregion
}

void hapusbuku(){

    #pragma region input data
    int totalbaris = 0,index = 0;
    
    // mencari total baris
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            string baris1;
            while (getline(bacafile,baris1))
            {
                size_t posisi = baris1.find("judul buku : ");
                if (posisi != string::npos)
                {
                    totalbaris++;
                }

            }
        }
    }
    string tmp;
    string judul[totalbaris],pengarang[totalbaris],penerbit[totalbaris],idstr[totalbaris],isbn[totalbaris],status[totalbaris],tahunterbitstr[totalbaris];
    int id[totalbaris],tahunterbit[totalbaris],stock[totalbaris];

    // baca file
    {
        ifstream bacafile("buku.txt");
        if (bacafile.is_open())
        {
            
            string baris;
            while (getline(bacafile,baris))
            {
                if ((baris.find("judul buku : ")) != string::npos)
                {
                    judul[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (judul[index][0] == ' ')
                    {
                        judul[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("isbn : ")) != string::npos)
                {
                    isbn[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (isbn[index][0] == ' ')
                    {
                        isbn[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("id : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    id[index] = atoi(tmp.c_str());
                    idstr[index] = tmp;
                    while (idstr[index][0] == ' ')
                    {
                        idstr[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("pengarang : ")) != string::npos)
                {
                    pengarang[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (pengarang[index][0] == ' ')
                    {
                        pengarang[index].erase(0,1);
                    }
                    
                }

                if ((baris.find("penerbit : ")) != string::npos)
                {
                    penerbit[index] = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    while (penerbit[index][0] == ' ')
                    {
                        penerbit[index].erase(0,1);
                    }
                    
                }
                
                if ((baris.find("tahun terbit : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    tahunterbit[index] = atoi(tmp.c_str());
                    tahunterbitstr[index] = tmp;
                    while (tahunterbitstr[index][0] == ' ')
                    {
                        tahunterbitstr[index].erase(0,1);
                    }
                    
                }
                
                if ((baris.find("stock : ")) != string::npos)
                {
                    tmp = baris.substr(baris.find(":") + 1);//mengambil nilai setelah kata kunci ":"
                    stock[index] = atoi(tmp.c_str());
                    
                }
                if ((baris.find("status : ")) != string::npos)
                {
                    status[index] = baris.substr(baris.find(":") + 1);
                    while (status[index][0] == ' ')
                    {
                        status[index].erase(0,1);
                    }   
                    index++;
                }
                
            }
            
        }
        
    }

    #pragma endregion

    bool ditemukan = false;
    bool out = false;
    int menu;
    while (true)
    {
        cout << endl 
            << "1.list buku"<<endl
            << "2.edit status buku"<<endl
            << "0.kembali"<<endl
            << "input : ";
        cin >> menu;
        if (cin)
        {
            switch (menu)
            {
                case 1:
                {
                    tampildatabuku();
                    break;
                }
                case 2:
                {
                    int hasil,editstatus;
                    string cari;
                    cout << "edit status buku!,anda harus mencari buku dulu!"<<endl;

                    cout<< "anda bisa mencari : judul buku ,isbn,id,pengarang,penerbit,tahun terbit"<< endl
                        << "disclaimer!,input anda akan menjadi lower case semua!"<<endl
                        << "input : ";
                    cin.ignore();
                    getline(cin,cari);
                    for (int i = 0; i < cari.length(); i++)
                    {
                        cari[i] = tolower(cari[i]);
                    }

                    cout << "anda mencari : "<< cari<<endl<<endl;
                    for (int i = 0; i < index; i++)
                    {
                        if (((judul[i].find(cari)) != string::npos) || 
                            ((isbn[i].find(cari)) != string::npos) || 
                            ((idstr[i].find(cari)) != string::npos) || 
                            ((pengarang[i].find(cari)) != string::npos) || 
                            ((penerbit[i].find(cari)) != string::npos) || 
                            ((tahunterbitstr[i].find(cari)) != string::npos))
                        {
                            ditemukan = true;
                            hasil = i;
                            cout << "judul buku : "<<judul[i]<<endl;
                            cout << "isbn : "<<isbn[i]<<endl;
                            cout << "id : "<< idstr[i]<<endl;
                            cout << "pengarang : "<< pengarang[i]<< endl;
                            cout << "penerbit : "<< penerbit[i] << endl;
                            cout << "tahun terbit : "<< tahunterbit[i]<< endl;
                            cout << "stock : "<< stock[i]<< endl;
                            cout << "status : "<<status[i]<<endl;
                            cout << endl;
                        }

                    }
                    if (!ditemukan)cout << "tidak ditemukan!"<<endl;

                    while (ditemukan)
                    {
                        cout << "edit status buku"<<endl
                            << "1.aktif"<<endl
                            << "0.hapus(soft del)"<<endl
                            << "input : ";
                        cin >> editstatus;
                        if (cin &&(editstatus == 1 || editstatus == 0))
                        {
                            status[hasil] = to_string(editstatus);
                            {
                                ofstream tulisfile("buku.txt");
                                for (int i = 0; i < index; i++)
                                {
                                    tulisfile << "judul buku : "<<judul[i]<<endl;
                                    tulisfile << "isbn : "<<isbn[i]<<endl;
                                    tulisfile << "id : "<< idstr[i]<<endl;
                                    tulisfile << "pengarang : "<< pengarang[i]<< endl;
                                    tulisfile << "penerbit : "<< penerbit[i] << endl;
                                    tulisfile << "tahun terbit : "<< tahunterbit[i]<< endl;
                                    tulisfile << "stock : "<< stock[i]<< endl;
                                    tulisfile << "status : "<<status[i]<<endl;
                                    tulisfile << endl;
                                }
                            
                            }       
                            break;
                        }
                        else{
                            cout << "invalid!"<<endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        }
                    }
                    

                    break;
                }
                case 0:
                {
                    out = true;
                    break;
                }
                default:
                    break;
            }
            if (out)
            {
                cout << "kembali!"<<endl;
                break;
            }
            
        }
        else{
            cout << "hanya angka!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        if (out)
        {
            break;
        }
        
    }

}
// sudah selesai

void tambahadmin(data_admin admin){
    ifstream bacafile("admin.txt");
    ofstream tulisfile("admin.txt",ios::app);
    string id,email,passw,nama,kodeakun;
    string konfirmasi;
    int urutan = 1; // urutan id admin
    if(bacafile.is_open())
    {
        string baris;
        while (getline(bacafile,baris))
        {
            size_t posisi = baris.find("nama : ");
            if (posisi != string::npos)
            {
                urutan++;
            }
            
        }
        
    }

    string idstr = to_string(urutan);
    if (urutan < 10) //jika urutan kurang dari 10
    {
        idstr = "00000" + idstr; //contoh 000003
    }
    else if (urutan < 100) // urutan kurang dari 100 
    {
        idstr = "0000" + idstr;//contoh 000011
    }
    else if (urutan < 1000)
    {
        idstr = "000" + idstr;
    }
    else if (urutan < 10000)
    {
        idstr = "00" + idstr;
    }
    
    #pragma region input data admin
    cout << endl;
    cin.ignore();
    cout << "nama : ";
    getline(cin,nama);
    cout << "email : ";
    getline(cin,email);
    while (true)
    {
        cout << "password : ";
        getline(cin,passw);
        cout << "konfirmasi password : ";
        getline(cin,konfirmasi);
        if (passw == konfirmasi)
        {
            break;
        }
        else{
            cout << "password tidak sama!"<<endl;
            cout << "==========="  <<endl;
        }
    }

    kodeakun = email + "-" + passw;

    if (tulisfile.is_open())
    {
        tulisfile << "kode akun : "<<kodeakun<<endl;
        tulisfile << "nama : "<<nama<< endl;
        tulisfile << "id : "<< idstr << endl;
        tulisfile << "email : "<<email << endl;
        tulisfile << "password : "<< passw << endl;
        tulisfile << endl;
        
    }
    cout << endl;
    #pragma endregion

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
    cout << endl;
    cout << "menambah anggota!" <<endl;
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
        if (cin && ( 0 < anggota.ttl.tgl && anggota.ttl.tgl<= 31)) //jika input int dan kurang dari atau sama dengan 31 maka looping berhenti
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
        if (cin &&  (0 < anggota.ttl.bulan && anggota.ttl.bulan <= 12))//jika input int dan kurang dari atau sama dengan 12 maka looping berhenti
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
            cout << "password tidak sama!(tekan enter atau apa saja untuk lanjut XD) ";
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
    
    // tanggal
    if (anggota.ttl.tgl < 10)
    {
        tgl = "0" + tgl;
    }
    
    // bulan
    if (anggota.ttl.bulan < 10)
    {
        bulan = "0" + bulan;
    }
    

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
    cout << endl;
}

bool cekbuku(string inputbuku){
    ifstream bacafile("buku.txt");
    string baris,kode;
    bool cek = false;
    int stock;
    string tmp;
    while (getline(bacafile,baris))
    {
        if ((baris.find("id : ")) != string::npos)
        {
            kode = baris.substr(baris.find(":") + 1);
            while (kode[0] == ' ')
            {
                kode.erase(0,1);
            }
            // reset stock setiap bertemmu id baru
            stock = -1;
            
        }
        if (baris.find("stock : ") != string::npos)
        {
            tmp = baris.substr(baris.find(":") + 1);
            stock = atoi(tmp.c_str());
        }
        if (kode == inputbuku && stock > 0)
        {
            cek = true;
        }
        if (cek)
        {
            break;
        }
        
    }
    return cek;
}

bool cekkodeanggota(string kode){
    ifstream bacafile("anggota.txt");
    string baris,kodeanngota;
    bool cek = false;
    while (getline(bacafile,baris))
    {
        if ((baris.find("kode : ")) != string::npos)
        {
            kodeanngota = baris.substr(baris.find(":") + 1);
            while (kodeanngota[0] == ' ')
            {
                kodeanngota.erase(0,1);
            }
            if (kode == kodeanngota)
            {
                cek = true;
            }
            
        }
        if (cek)
        {
            break;
        }
        
    }
    return cek;
}

void tambahpeminjaman(){
    ifstream bacafile("peminjaman.txt");
    int id = 1;
    peminjaman data;
    string kode,kodebuku,baris;
    waktutanggal waktu = waktunyata();

    while (getline(bacafile,baris))
    {
        if ((baris.find("id peminjaman : ")) != string::npos)
        {
            id++;
        }
        
    }
    
    
    data.id_peminjaman = to_string(id);
    
    cout << "peminjaman!"<<endl<<endl;
    tampildataanggota();
    cout << endl << "mohon input kode berdasar kan tabel di atas!"<<endl<<endl;
    while (true)
    {
        cout <<"input kode anggota : ";
        cin >> kode;
        if (cekkodeanggota(kode))
        {
            cout << "input kode anggota berhasil!"<<endl;
            break;
        }
        else{
            cout << "data tidak ditemukan!"<<endl<<endl;
            
        }

    }
    
    while (true)
    {
        cout << "input kode buku : ";
        cin >> kodebuku;
        if (cekbuku(kodebuku))
        {
            cout << "input kode buku berhasil!"<<endl<<endl;
            break;
        }
        else{
            cout << "gagal!,mungkin karena stock 0 atau, anda salah input id!"<<endl<<endl;
        }
    }
    // deadline
    time_t now = time(0);
    tm ltm = *localtime(&now);

    // tambah 7 hari
    ltm.tm_mday += 7;

    // mktime akan menormalkan tanggal, misal jika melewati akhir bulan
    time_t t_deadline = mktime(&ltm);// contoh nyata 28 desember + 7 hari maka akan otomatis 4 januari  

    // pindah ke var deadline 
    waktutanggal deadline;
    tm *d = localtime(&t_deadline);
    deadline.tgl = d->tm_mday;// -> adalah pointer to struct (*d).tm_mday
    deadline.bulan = d->tm_mon + 1;
    deadline.tahun = d->tm_year + 1900;

    cout << "id peminjaman : "<< id<<endl;
    cout << "kode anggota : "<< kode<<endl;
    cout << "id buku : "<< kodebuku <<endl;
    cout << "tanggal pinjam : " << waktu.tgl << "-"<< waktu.bulan << "-"<<waktu.tahun<<endl;
    cout << "deadline : " << deadline.tgl << "-"<< deadline.bulan << "-"<< deadline.tahun << endl;
    cout << "status : "<< 1<<endl;
    cout << "denda : "<< 0<<endl;

    ofstream tulisfile("peminjaman.txt",ios::app);
    tulisfile << "id peminjaman : "<< id<<endl;
    tulisfile << "kode anggota : "<< kode<<endl;
    tulisfile << "id buku : "<< kodebuku <<endl;
    tulisfile << "tanggal pinjam : " << waktu.tgl << "-"<< waktu.bulan << "-"<<waktu.tahun<<endl;
    tulisfile << "deadline : " << deadline.tgl << "-"<< deadline.bulan << "-"<< deadline.tahun << endl;
    tulisfile << "status : "<< 1<<endl;
    tulisfile << "denda : "<< 0<<endl;
    tulisfile << endl;

}

// hampir selesai 
void dasboranggota(data_anggota anggota,string kodeakun,string email,string password){
    string menu;// variabel menu
    while (true)
    {
        cout <<endl;
        cout << "dasbor anggota"<<endl;
        cout << "1.pencarian buku"<<endl
            << "2.profile"<<endl
            << "0.keluar"<<endl
            << "input: ";
        cin >> menu;
        
        // pengecekan,menu apa yang di input oleh user
        if (menu == "1")
        {
            caribuku();
        }
        else if (menu == "2")
        {
	        profileanggota(anggota,kodeakun,email,password);
        }
        else if (menu == "0")
        {
            cout << "user memilih keluar!"<<endl;
            cout << "tekan tombol apa saja untuk lanjut sekaligus bersihkan terminal!";
            cin.get(); cin.get();// menunggu input user 

            clearCMD_ln();

            break;
        }
        else{ // jika input tidak sesuai dengan yang ditampilkan maka looping
            cout << "input invalid!"<<endl;
            cout <<endl;
            continue;
        }
    }
    cout << endl;
}


//belum selesai
void dasboradmin(){
    waktutanggal waktu = waktunyata();
    string menu;
    data_anggota anggota;
    data_admin admin;
    while (true)
    {
        cout << endl
            << "dasbor admin"<<endl
            << endl
            << "waktu hari ini : "<< waktu.tgl << "-"<< waktu.bulan << "-"<< waktu.tahun<<endl;
        cout << "1.tampil data anggota"<<endl
            << "2.cari / tampil buku"<<endl
            << "3.tambah admin"<<endl
            << "4.tambah anggota"<<endl
            << "5.tambah buku"<<endl
            << "6.peminjaman"<<endl
            << "7.pengembalian"<< endl
            << "8.tampil semua anggota admin"<<endl
            << "9.edit status buku"<<endl
            << "0.keluar"<< endl
            << "input : ";
        cin >> menu;
        
        if (menu == "1")
        {
            cout << "tampil data anggota"<<endl;
            tampildataanggota();
        }
        else if (menu == "2")
        {
            while (true)
            {
            
                cout << endl 
                    << "1.cari buku"<<endl
                    << "2.tampil data buku"<<endl
                    << "0.kembali"<<endl
                    << "input : ";
                cin >> menu;
                if (menu == "1")
                {
                    caribuku();
                }
                else if (menu == "2")
                {
                    tampildatabuku();
                }
                else if (menu == "0")
                {
                    break;
                }
                else{
                    cout << "input invalid"<<endl;
                }
            }
            
        }
        else if (menu == "3")
        {
            cout << "tambah admin "<<endl;
            tambahadmin(admin);
        }
        else if (menu == "4")
        {
            cout << "tambah anggota"<<endl;
            daftar(anggota);
        }
        else if (menu == "5")
        {
            cout << "tambah buku"<<endl;
            tambahbuku();
        }
        else if (menu == "6")
        {
            cout << "peminjaman"<<endl;
        }
        else if (menu == "7")
        {
            cout << "pengembalian"<<endl;
        }
        else if (menu == "8")
        {
            cout << "tampil admin"<<endl;
            tampiladmin();
        }
        else if (menu == "9")
        {
            hapusbuku();
        }
        else if (menu == "0")
        {
            cout << "super user memilih keluar!"<<endl;
            cout << "tekan tombol apa saja untuk lanjut sekaligus bersihkan terminal!";

            cin.get();cin.get();// menunggu input user

            clearCMD_ln();
            break;
        }
        else{
            cout << "input invalid!"<<endl;
            cout << "==========="<<endl;
            cout << endl;
        }
        
        cout << endl;
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

    cout <<endl<< "login" <<endl;
    cout << "email : ";
    cin.ignore();// menghilangkan buffer
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
                email2 = kodeakun2.substr(0,kodeakun2.find('-'));
                pass2 = kodeakun2.substr(kodeakun2.find("-") + 1,kodeakun2.find('\n'));
                
            }
            
        }
        
    }
    // pengecekan apakah input login ada di data anggota atau admin atau malah akun tidak ada
    if (kodeakun1 == kodeakunlog) // jika anggota
    {
        clearCMD_ln();
        dasboranggota(anggota,kodeakun1,email1,pass1);
    }
    else if (kodeakun2 == kodeakunlog) // jika admin
    {
        clearCMD_ln();
        dasboradmin();
    }
    else{ // jika tidak ditemukan 
        clearCMD_ln();
        cout << "akun tidak ditemukan!"<<endl<<endl;
    }
    
}


// kode utama
int main(){
    
    bool out = false;
    int menu;
    data_anggota anggota;
    data_admin admin;
    
    while (true)
    {
        
        cout << endl
            << "halaman login!"<<endl;
        cout << endl 
            <<"1.login!"<<endl
            << "0.keluar"<<endl
            << "input : ";
        cin >> menu;
        if (cin)
        {
            switch (menu)
            {
            case 1:
                clearCMD_ln();
                login(anggota,admin);
                break;
            
            case 0:
                
                cout << "user memilih keluar!"<<endl;
                out = true;
                break;
            
            default:

                clearCMD_ln();
                cout << endl 
                    << "menu tidak ditemukan!"<<endl;
                continue;
            }
            if (out){
                break;
            }
        }
        else{
            clearCMD_ln();
            cout << "hanya angka!"<<endl;
            cin.clear();// menghapus sisa input yang salah
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//menghapus buffer
        }
    }
    tambahpeminjaman();
}
