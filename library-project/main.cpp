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

// list revisi
// isbn,kode buku,login daftar,member tidak bisa pinjam atau pengemmbalian liwat program 


string fiksi(){
    int status;
    while (true)
    {
        
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
        if (cin && status <= 9)
        {
            break;
        }
        else{
            cout << "input invalid!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

    }    

    string statusstr = to_string(status);
    return "0" + statusstr;

}

string nonfiksi(){
   
    int status;
    while (true)
    {
        
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
        if (cin && status <= 7)
        {
            cout <<"berhasil"<<endl;
            break;
        }
        else{
            cout << "invalid!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        
    }
    string statusstr = to_string(status);
    return "1" + statusstr;
}

string kodebuku(){
    string status;
    string kode;
    while (true)
    {
        cout << "status"<<endl
            << "0.fiksi"<<endl
            << "1.nonfiksi"<<endl;
        cin >> status;
        if (status == "0")
        {
            cout << "fiksi"<<endl;
            kode = fiksi();
            cout << "fiksi : "<<kode;
            break;
        }
        else if (status == "1")
        {
            cout << "nonfiksi"<<endl;
            kode = nonfiksi();
            cout << "tes lagi : "<<kode<<endl;
            break;
        }
        else{
            cout << "input invalid!"<<endl;
        }

    }

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
    cout << "kode : "  <<idstr<<endl;
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
    cin.ignore();
    cout << "masukkan judul buku : ";
    getline(cin,judulbuku);
    cout << "penerbit : ";
    getline(cin,penerbit);
    cout << "pengarang : ";
    getline(cin,pengarang);
    while (true)
    {
        
        cout << "tahun terbit : ";
        cin >> tahunterbit;
        tahunterbitstr = to_string(tahunterbit);
        if (cin && tahunterbit &&tahunterbitstr.length() == 4 )
        {
            break;
        }
        else{
            cout << "gagal"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }

        // nomor buku
        while (true)
        {
            cout <<"input nomor buku : ";
            cin >> isbn.nomorbuku;
            if (cin && isbn.nomorbuku)
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }

        // checkdigit
        while (true)
        {
            cout <<"input check digit atau digit terakhir : ";
            cin >> isbn.checkdigit;
            if (cin && isbn.checkdigit)
            {
                break;
            }
            else
            {
                cout << "input invalid!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }

        isbnstr = to_string(isbn.previx) + to_string(isbn.kodenegara) + to_string(isbn.kodepenerbit) + to_string(isbn.nomorbuku) + to_string(isbn.checkdigit);
        cout << "isbn : "<< isbnstr<<endl;
        if (isbnstr.length() == 13)
        {
            cout << "berhasil"<<endl;
            break;
        }
        else{
            cout << "invalid!"<<endl
                << "digit adalah " << isbnstr.length()<< " bukan 13!"<<endl;
        }
        
    }

    #pragma endregion

    #pragma endregion

    
    string kode = kodebuku();

    {
        ofstream tulisfile("buku.txt",ios::app);
        if (tulisfile.is_open())
        {
            tulisfile << "judul buku : " << judulbuku << endl;
            tulisfile << "isbn : "<<isbnstr;
            // for (int i = 0; i < 13; i++)
            // {
            //     tulisfile << hasilisbn[i];
            // }
            tulisfile<< endl;
            tulisfile << "id : "<< kode<<endl;
            tulisfile << "pengarang : " << pengarang << endl;
            tulisfile << "penerbit : " << penerbit << endl;
            tulisfile << "tahun terbit : "<<tahunterbit<<endl;
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
}


// belum selesai(tinggal pencarian)
void dasboranggota(data_anggota anggota,string kodeakun,string email,string password){
    string menu;// variabel menu
    while (true)
    {
        cout <<endl;
        cout << "dasbor anggota"<<endl;
        cout << "1.cari"<<endl
            << "2.profile"<<endl
            << "3.keluar"<<endl
            << "input: ";
        cin >> menu;
        
        // pengecekan,menu apa yang di input oleh user
        if (menu == "1")
        {
            cout <<endl<< "pencarian"<<endl;
        }
        else if (menu == "2")
        {
	        profileanggota(anggota,kodeakun,email,password);
        }
        else if (menu == "3")
        {
            cout << "user memilih keluar!"<<endl;
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
        if (cin && anggota.ttl.tgl<= 31) //jika input int dan kurang dari atau sama dengan 31 maka looping berhenti
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
}


//belum selesai
void dasboradmin(){
    string menu;
    data_anggota anggota;
    data_admin admin;
    while (true)
    {
    
        cout << "1.tampil data anggota"<<endl
            << "2.tampil buku"<<endl
            << "3.tambah admin"<<endl
            << "4.tambah anggota"<<endl
            << "5.tambah buku"<<endl
            << "6.peminjaman"<<endl
            << "7.pengembalian"<< endl
            << "8.keluar"<< endl
            << "input : ";
        cin >> menu;
        
        if (menu == "1")
        {
            cout << "tampil data anggota"<<endl;
            // tampildataanggota()
        }
        else if (menu == "2")
        {
            cout << "tampil buku "<< endl;
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
            cout << "super user memilih keluar!"<<endl;
            break;
        }
        else{
            cout << "input invalid!"<<endl;
            cout << "==========="<<endl;
            cout << endl;
        }
        // tambahbuku();
        // tampildataanggota();
        
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

		        // buat tes atau buat debug doang
                /*cout << kodeakun1 << endl;
                cout << email1<<endl;
                cout << pass1<<endl;
                cout <<baris1<<endl;
                for(int i = 1;i <= 8 && getline(bacafileanggota,baris1);i++){
			        cout << baris1 <<endl;
			
                }
                */
                
             
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
                // debug
                // cout << kodeakun2.length()<<endl;
                // cout << email2 <<endl;
                // cout << pass2<<endl;
                
            }
            
        }
        
    }
    // pengecekan apakah input login ada di data anggota atau admin atau malah akun tidak ada
    if (kodeakun1 == kodeakunlog) // jika anggota
    {
        dasboranggota(anggota,kodeakun1,email1,pass1);
    }
    else if (kodeakun2 == kodeakunlog) // jika admin
    {
        dasboradmin();
    }
    else{ // jika tidak ditemukan 
        cout << "akun tidak ditemukan!"<<endl<<endl;
    }
    
}


// kode utama
int main(){
    /*
    string menu;
    data_anggota anggota;
    data_admin admin;
    while (true)
    {
        cout <<"1.login!"<<endl
        << "2.keluar"<<endl
        << "input : ";
        cin >> menu;
        if (menu == "1")
        {
            login(anggota,admin);
        }

        else if (menu == "2")
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
    */
   

}
