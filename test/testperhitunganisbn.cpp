#include<iostream>
#include<fstream>
using namespace std;

void checkdigit(int n ,int arr[]){
    int hasilawal = 0;
    int hasilakhir;
    int temp;
    int arrakhir[13];
    for (int i = 0; i < 13; i++)
    {
        arrakhir[i] = arr[i];
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
    arrakhir[12] = hasilakhir;
    cout << "check digit adalah : " << hasilakhir<<endl;
    cout << "isbn : ";
    for (int i = 0; i < 13; i++)
    {
       if (i == 3 || i == 6 || i == 9 || i == 12)
       {
            cout<< "-" << arrakhir[i];
       }
       else{
            cout << arrakhir[i];
       }
       
    }
    
}

void isbn(){
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
    for (int i = 0; i < panjang; i++)
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
    
    checkdigit(panjang,digit);
}


int main(){
    isbn();
}
