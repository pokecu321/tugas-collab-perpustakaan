#include<iostream>
#include<fstream>
using namespace std;

void checkdigit(int arrayakhir[],int arr[]){
    int hasilawal = 0;
    int hasilakhir;
    int temp;
    for (int i = 0; i < 13; i++)
    {
        arrayakhir[i] = arr[i];
    }
    
    for (int i = 0; i < 12; i++)
    {
        if (i % 2 == 0)
        {
            temp = arr[i] * 1;
            arr[i] = temp;
        }
        else{
            temp = arr[i] * 3;
            arr[i] = temp;
        }
        
    }
    cout << "hasil : ";
    for (int i = 0; i < 12; i++)
    {
        if (i < 11)
        {
            cout << arr[i] << " + ";
        }
        else{
            cout << arr[i] << " = ";
        }
        hasilawal += arr[i];
    }
    cout << hasilawal<<endl;
    hasilakhir = (10 - (hasilawal % 10)) % 10;
    arrayakhir[12] = hasilakhir;
    cout << "check digit adalah : " << hasilakhir<<endl;
    // cout << "isbn : ";
    // for (int i = 0; i < 13; i++)
    // {
    //    if (i == 3 || i == 6 || i == 9 || i == 12)
    //    {
    //         cout<< "-" << arrakhir[i];
    //    }
    //    else{
    //         cout << arrakhir[i];
    //    }
       
    // }
    
    
}

void isbn(int hasilisbn[]){
    // Prefix – Kode Negara – Kode Penerbit – Nomor Buku – Check Digit
    string prefixstr = "978";
    string kodenegarastr = "602";
    string kodepenerbitstr = "999";
    string nomorbukustr = "001";
    string sementara = prefixstr + kodenegarastr + kodepenerbitstr + nomorbukustr;
    int panjang = sementara.length();
    cout << sementara << endl;
    cout << panjang << endl;
    int digit[panjang];
    int hasil[13];
    for (int i = 0; i < 12; i++)
    {
        digit[i] = sementara[i] - '0';
    }
    for (int i = 0; i < panjang; i++)
    {
        if (i < panjang-1)
        {
            cout << digit[i] << ",";
        }
        else{
            cout << digit[i]<< ""<<endl;
        }
    }
    
    
    checkdigit(hasilisbn,digit);
    
}

void tambahbuku(){
    int urutan = 1;
    {
        ifstream inputfile("buku.txt");
        
        if (inputfile.is_open())
        {
            string baris;
            while (getline(inputfile,baris))
            {
                size_t posisi = baris.find("nama buku : ");
                if (posisi != string::npos)
                {
                    urutan++;
                }

            }

        }
    }
    // id
    string urutanstr = to_string(urutan);
    if (urutan < 10)
    {
        urutanstr = "00000" + urutanstr;
    }
    else if (urutan < 100)
    {
        urutanstr = "0000" + urutanstr;
    }
    else if (urutan < 1000)
    {
        urutanstr = "000" + urutanstr;
    }
    else if (urutan < 10000)
    {
        urutanstr = "00" + urutanstr;
    }
    int hasil[13];
    isbn(hasil);
    cout << urutanstr <<endl;
    string judulbuku,penerbit,pengarang,tahunterbit;
    cout << "nama buku : " ;
    getline(cin,judulbuku);
    ofstream outputfile("buku.txt",ios::app);
    if (outputfile.is_open())
    {
        outputfile << endl;
        outputfile << "nama buku : " << judulbuku <<endl;
        outputfile << "id : " << urutanstr <<endl;
        for (int i = 0; i < 13; i++)
        {
            if (i == 3 || i == 6 || i == 9 || i == 12)
            {
                outputfile<< "-" << hasil[i];
            }
            else{
                outputfile << hasil[i];
            }
       
        
        }
        outputfile << endl;
        
    }
    
    
}

int main(){
    tambahbuku();
    
}
