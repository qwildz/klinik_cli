#include <vector>
#include <cmath>
#include <conio2.h>

#include "../struct.h"
#include "../library/futils.h"
#include "../library/ui.h"
#include "../library/utils.h"

#include "mcekup.h"
#include "mpasien.h"
#include "mpenyakit.h"

STpasien pasien;

void StrukCekup(int i)
{
	clearscreentable(); // Bersihkan layar
	element_header();	// Tampilkan header
	STcekup data = ambilDataCekup()[i];
	vector<STresep> resep = ambilDataResep(data.penyakit.id);
	
	SetColor(WHITE, BLACK);
	
	char table_header[81] = "| No |           Nama            |      Harga (Rp)    |      Dosis x Sehari    |";
		    
    // Render table 
    buatTable(WHITE, BLACK, table_header, 17, resep.size());
    
    // Mulai menampilan data2 yang ada ke layar
    int k = 0;
    int totalharga = 0;
    for(int i = 0; i < resep.size(); i++)
    {
    	if(resep[i].obat.umur > data.pasien.umur) continue;
    	
    	textxy(3, 20+k, i+1);
    	textxy(8, 20+k, resep[i].obat.nama);
    	textxy(37, 20+k, resep[i].obat.harga);
    	textxy(68, 20+k, resep[i].dosis);
    	k++;
    	
    	totalharga += resep[i].obat.harga;
    }
    
    textxy(2, 20+k+2, "Total Harga Obat : Rp.");
    textxy(30, 20+k+2, totalharga);
    
	garis(WHITE, BLACK, 1, 5, 80, 5);
	textxy(31, 6, "Detail Pemeriksaan");
	garis(WHITE, BLACK, 1, 7, 80, 7);
	
	textxy(2, 9,  "Nama pasien : "); textxy(16, 9, data.pasien.nama);
	textxy(2, 10, "Alamat      : "); textxy(16, 10, data.pasien.alamat);
	textxy(2, 11, "Kelamin     : "); textxy(16, 11, char2Kelamin(data.pasien.kelamin));
	textxy(2, 12, "Umur (tahun): "); textxy(16, 12, data.pasien.umur);
	
	textxy(47, 9,  "Nama pasien : "); textxy(61, 9, data.penyakit.nama);
	textxy(47, 10, "Alamat      : "); textxy(61, 10, char2Jenis(data.penyakit.jenis));
	textxy(47, 11, "Tgl Cekup   : "); textxy(61, 11, data.tanggal.dd);
							    	  textxy(63, 11, "/");
							    	  textxy(65, 11, data.tanggal.mm);
							    	  textxy(67, 11, "/");
							    	  textxy(69, 11, data.tanggal.yy);
	
	garis(WHITE, BLACK, 1, 14, 80, 14);
	textxy(34, 15, "Daftar Obat");
	garis(WHITE, BLACK, 1, 16, 80, 16);
    
	string pilihan = "B(Back)"; // Text petunjuk menu
	char menu[1] = {'B'}; // Karakter yang valid untuk dipilih
	int nMenu = 1;
	
	char pilih;
	do {
		pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
	} while(pilih != 'B');
}

void TambahCekup()
{
	STcekup cekup;
	STpenyakit penyakit;
	STtanggal tanggal = getDate();
	
	bool confr;
	confr = dialogKonfirmasi("Tambah data cekup?");
	bool pasienlama = dialogKonfirmasi("Pasien sudah terdaftar?");
	if(confr)
	{	
		if(!pasienlama)
		{
			TambahPasien();
			vector<STpasien> dataPasien = ambilDataPasien();
			cekup.pasien = dataPasien[dataPasien.size()-1];
			if(PilihPenyakit(PENYAKIT_ALL, "", 1, &penyakit))
				{
					cekup.penyakit = penyakit;
					cekup.tanggal = tanggal;
						
					tambahData(cekup);
					dialogSuccess("Data telah ditambahkan");	
				}
				else
					dialogError("Gagal menambahkan data");	
		}
		else
		{
			if(pasien.id == -1)
			{
				if(PilihPasien(PASIEN_ALL, "", 1, &pasien))
				{
					cekup.pasien = pasien;
					if(PilihPenyakit(PENYAKIT_ALL, "", 1, &penyakit))
					{
						cekup.penyakit = penyakit;
						cekup.tanggal = tanggal;
						
						tambahData(cekup);
						dialogSuccess("Data telah ditambahkan");	
					}
					else
						dialogError("Gagal menambahkan data");	
				}
				else
					dialogError("Gagal menambahkan data");
			}
			else
			{
				cekup.pasien = pasien;
				if(PilihPenyakit(PENYAKIT_ALL, "", 1, &penyakit))
				{
					cekup.penyakit = penyakit;
					cekup.tanggal = tanggal;
						
					tambahData(cekup);
					dialogSuccess("Data telah ditambahkan");	
				}
				else
					dialogError("Gagal menambahkan data");	
			}
		}
	}
}

bool HapusCekup(int i)
{
	vector<STcekup> cekup = ambilDataCekup();
	
	if(i > cekup.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
	
	if(dialogKonfirmasi("Hapus data cekup?"))
	{
		cekup.erase(cekup.begin() + (i));
		timpaFile(cekup);
		dialogSuccess("Data telah dihapus");
		
		return false;
	}
	
	return true;	
}

void MenuCekup(int id)
{
	int i = id2pos(ambilDataCekup(), id);
	
	int pilih;
    bool back;
	do {
		string menu[3] = {"Lihat Struk Cekup", "Hapus", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Cekup", menu, 3, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 2 : 
				back = HapusCekup(i);
			break;
			
			case 1 :
				StrukCekup(i);
				back = false;
			break;
			
			case 3 : 
				back = false;
			break;
		}
	} while(pilih < 1 || pilih > 3 || back);
}

void ListCekup(int type, string keyword, int page, int id_pasien)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STcekup> data = (id_pasien == -1) ? ambilDataCekup(type, keyword) : ambilDataCekup(id_pasien);
		
		if(id_pasien == -1)
			pasien.id = -1;
		else
			pasien = ambilDataPasien(PASIEN_ID, int2string(id_pasien))[0];
		
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan;
			char menu[3]       = {'A', 'B', 'F'};             // Karakter yang valid untuk dipilih
			int nMenu = 3; // Jumlah menu yang ada
			
			if(id_pasien == -1)
			{
				pilihan = "A(Tmbh Dta) F(Cari) B(Back)"; // Text petunjuk menu
				nMenu = 2;
			}
			else
			{
				pilihan = "A(Tmbh Dta) B(Back)"; // Text petunjuk menu
			}
				     
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian	
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama Pasien | 2: Nama Penyakit                                              "; // Text petunjuk menu pencarian
			char menuCari[3]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 3; // Jumlah menu pencarian
			string carikeyword; // Variable untuk menampung keyword pencarian hasil ketikan
			
			bool needRefresh = false; // Untuk menentukan apakah table perlu dibuat ulang karena dialog menu muncul
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{
					// User memilih menu pencarian
					case 'F' :
						
						// Mulai membuat tampilan pencarian di bawah dan mendengar inputan untuk menu pencarian
						pilihCari = barMenu(pilihanCari, menuCari, nMenuCari);
						
						// Percabangan menu pencarian yang telah dipilih
						// Tiap kategori akan meminta user menginputkan kata kunci yang sesuai 
						// dan kemudian akan memanggil fungsi tampil pasien dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama pasien (alphabet)");
								return ListCekup(CEKUP_NAMA_PASIEN, carikeyword, 1, -1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama penyakit (alphanumeric)");
								return ListCekup(CEKUP_NAMA_PENYAKIT, carikeyword, 1, -1);
							break;
						}
					break;
					
					case 'A' :
						TambahCekup();
						needRefresh = true;
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
		// Jika data tersedia
		else
		{
			float perPage = 15; // Jumlah data per halaman
			int nPage = ceil(data.size()/perPage); // Menghitung jumlah halaman yang tersedia
			
			if(page < 1) // Jika halaman yang diminta < 1, paksa halaman menjadi 1
				page = 1;
			else if(page > nPage) // Jika halaman yang diminta > jumlah halaman yang tersedia, paksa halaman menjadi halaman terakhir
				page = nPage;
			
			int start = (page-1) * perPage; // Menghitung index awal data yang akan ditampilkan
			int end = (page != nPage) ? start + perPage : data.size(); // Menghitung index akhir data yang akan ditampilkan
			int nData = (page == nPage) ? end - start : perPage; // Menghitung jumlah data yang akan ditampilkan
			
			// Mulai membuat judul / title dengan memberikan status data
			string title; 
			std::stringstream sstm;
			
			if(id_pasien == -1)
				sstm << "Daftar Cekup (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			else
				sstm << "Daftar Cekup Pasien " << pasien.nama << "  (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			
			if(id_pasien == -1)
			{	
				/* Membuat header untuk table
								         00000000011111111112222222222333333333344444444445555555555666666666677777777778
								         12345678901234567890123456789012345678901234567890123456789012345678901234567890
								         ¦ 1  ¦ M. Resna Rizki P.    ¦ Jl. Setia Budhi No.  |  Pria   ¦  31 / 12 / 2014 |*/
				char table_header[81] = "| No |     Nama Pasien      |       Penyakit       | Kelamin |    Tgl Cekup    |";
				// Render table 
		    	buatTable(WHITE, BLACK, table_header, 8, nData);
		    	
		    	// Mulai menampilan data2 yang ada ke layar
			    int k = 0;
			    for(int i = start; i < end; i++)
			    {
			    	textxy(3, 11+k, i+1);
			    	textxy(8, 11+k, data[i].pasien.nama);
			    	textxy(31, 11+k, data[i].penyakit.nama);
			    	textxy(54, 11+k, char2Kelamin(data[i].pasien.kelamin));
			    	textxy(65, 11+k, data[i].tanggal.dd);
			    	textxy(68, 11+k, "/");
			    	textxy(70, 11+k, data[i].tanggal.mm);
			    	textxy(73, 11+k, "/");
			    	textxy(75, 11+k, data[i].tanggal.yy);
			    	k++;
			    }
			}
			else
			{
				char table_header[81] = "| No |                      Penyakit                         |    Tgl Cekup    |";
				// Render table 
		    	buatTable(WHITE, BLACK, table_header, 8, nData);
		    	
		    	// Mulai menampilan data2 yang ada ke layar
			    int k = 0;
			    for(int i = start; i < end; i++)
			    {
			    	textxy(3, 11+k, i+1);
			    	textxy(8, 11+k, data[i].penyakit.nama);
			    	textxy(65, 11+k, data[i].tanggal.dd);
			    	textxy(68, 11+k, "/");
			    	textxy(70, 11+k, data[i].tanggal.mm);
			    	textxy(73, 11+k, "/");
			    	textxy(75, 11+k, data[i].tanggal.yy);
			    	k++;
			    }
			}
		    
		    string pilihan;
			char menu[7] = {'N', 'P', 'A', 'X', 'B', 'F', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(id_pasien == -1)
			{
				if(type != CEKUP_ALL)
					{
					/*            "                                                                               "*/
				    pilihan     = "N(Next Pg) P(Prev Pg) A(Tmbh Dta) X(Pilih Data) F(Cari) B(Back) C(Tmplkan Smua)"; // Text petunjuk menu
					nMenu = 7; // Jumlah menu yang ada
				}
				else
				{
					/*            "                                                                               "*/
					pilihan     = "N(Next Pg) P(Prev Pg) A(Tmbh Dta) X(Plih Data) F(Cari) B(Back)                 "; // Text petunjuk menu
					nMenu = 6; // Jumlah menu yang ada
				}
			}
			else
			{
				/*            "                                                                               "*/
				pilihan     = "N(Next Pg) P(Prev Pg) A(Tmbh Dta) X(Plih Data) B(Back)                         "; // Text petunjuk menu
				nMenu = 5; // Jumlah menu yang ada
			}
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian 
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama Pasien | 2: Nama Penyakit                                              "; // Text petunjuk menu pencarian
			char menuCari[3]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 3; // Jumlah menu pencarian
			string carikeyword; // Variable untuk menampung keyword pencarian hasil ketikan
			
			bool needRefresh = false; // Untuk menentukan apakah table perlu dibuat ulang karena dialog menu muncul
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{
					// User memilih menu halaman selanjutnya
					case 'N' : 
						return ListCekup(type, keyword, page + 1, id_pasien);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return ListCekup(type, keyword, page - 1, id_pasien);
					break;
					
					// User memilih menu pencarian
					case 'F' :
						// Mulai membuat tampilan pencarian di bawah dan mendengar inputan untuk menu pencarian
						pilihCari = barMenu(pilihanCari, menuCari, nMenuCari);
						
						// Percabangan menu pencarian yang telah dipilih
						// Tiap kategori akan meminta user menginputkan kata kunci yang sesuai 
						// dan kemudian akan memanggil fungsi tampil pasien kembali dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama pasien (alphabet)");
								return ListCekup(CEKUP_NAMA_PASIEN, carikeyword, 1, -1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama penyakit (alphanumeric)");
								return ListCekup(CEKUP_NAMA_PENYAKIT, carikeyword, 1, -1);
							break;
						}
					break;
					
					// User memilih menu pilih pasien
					case 'X' :
						int iCekup; // Variable untuk memilih nomor pasien yang dipilih
						barSelect(start+1, end, &iCekup); // Membuat tampilan untuk pilih pasien
						if(iCekup != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							MenuCekup(data[iCekup-1].id); // Tampilkan dialog menu pasien
							needRefresh = true; // set refresh menjadi true agar table dibuat ulang ketika dialog menu ditutup
						}
					break;
					
					case 'A' :
						TambahCekup();
						needRefresh = true;
					break;
					
					case 'C' :
						return ListCekup(CEKUP_ALL, "", 1, -1);
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
	} while(pilih != 'B');
}
