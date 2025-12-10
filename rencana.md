rencana

1. fungsi login dan daftar
2. dasbor anggota
3. dasbor admin





dasbor anggota

* cari
* pinjam
* pengembalian
* profil



dasbor admin

* menambah admin
* menampilkan profil
* mmenampilkan buku



kode buku = 1

digit pertama = status fiksi / nonfiksi

digit ke dua = check digit

check digit tergantung genre nya







tahun terbit dan isbn bisa di akali karena hanya menggunakan string bukan int = selesai



dasbor anggota,user memmilih keluar kurang endl



tampil data



kode | nama | id



tampil buku

id | isbn | judul | pengarang | penerbit | tahun terbit | stock





cout << "nama"<<endl

<<"nama \\t\\t | id\\t    |status| ttl \\t\\t\\t | kode \\t| email \\t\\t | passwd "<<endl;



for loop

cout << nama\[i] << "\\t | " << idstr\[i] <<"   | "<< statusakun\[i]<< " | " << ttl\[i]<<" \\t |"<< kode\[i]<< "\\t|"<< email\[i]<< "\\t | "<< password\[i]<<endl;

 

nama             |



nama                  |

nama           |









000006  |20090605001  |1    |surabaya, 05, 06, 2009      |m.saifuddin    | adin@gmail.com        |sudo

000008  |20091123003  |1    |tulungagung, 23, 11, 2009   |pandra 153     | eka153@gmail.com      |kilometer ajah



pandra 153       | 000008   | 1 | tulungagung, 23, 11, 2009      |20091123003   |eka153@gmail.com        | kilometer ajah

m.saifuddin      | 000006   | 1 | surabaya, 05, 06, 2009         |20090605001   |adin@gmail.com  | sudo









20090605001|000006  |1    |surabaya, 05, 06, 2009        |m.saifuddin    |adin@gmail.com         |sudo

20091123001|000004  |1    |the gunung, 23, 11, 2009      |kuadrat        |ultah  |buyut sekarang 16

20091123002|000007  |1    |tulungagung, 23, 11, 2009     |kuadratt       |pancong1@gmail.com     |enak1

20091123003|000008  |1    |tulungagung, 23, 11, 2009     |pandra 153     |eka153@gmail.com       |kilometer ajah





000007  |20091123002  |1    |tulungagung, 23, 11, 2009   |kuadratt       | pancong1@gmail.com    |enak1

000002  |20091210002  |1    |tulungagung, 10, 12, 2009   |lagilagi adin  | member@gmail.com      |member









Fitur pada aplikasi

a. tambah buku, anggota, peminjaman

b. tampil data buku secara ascending berdasarkan judul buku, anggota ascending berdasarkan nama anggota, peminjaman yang blm dikembalikan, petugas

c. pengembalian buku (jika terlambat (peminjaman lebih dari 7 hari) denda Rp. 1000 per buku per hari)

d. cari buku berdasarkan judul, cari anggota berdasarkan kode anggota, cari peminjaman berdasarkan id peminjaman

e. hapus buku



sudah

tambah buku,admin,anggota

tampil data buku,admin,anggota

cari buku,cari anggota

hapus buku
tampil peminjaman,cari 
edit buku(jadi bukan cuman hapus buku,jadi bisa up stock juga)


sudah lumayan!

peminjaman(tinggal kurangi stock buku)



belum tapi sudah dapat algoritma!

(peminjaman dan pengembalian sudah 90% minimal,barubisa mengerjakan fungsi ini)

denda(setelah peminjaman)





belum

pengembalian

denda(setelah peminjaman)






format pengembalian.txt



ID Pinjam : 10

Kode Anggota : AG003

Kode Buku : BK010

Tanggal Pinjam : 09-12-2025

Deadline : 16-12-2025

Tanggal Kembali : -

Status : 1

Denda : 0



