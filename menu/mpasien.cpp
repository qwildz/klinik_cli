#include <vector>
#include <cmath>
#include <conio2.h>

#include "../struct.h"
#include "../library/futils.h"
#include "../library/ui.h"
#include "../library/utils.h"

#include "mpasien.h"
#include "mcekup.h"

void TambahPasien()
{
	STpasien pasien;
	bool confr;
	confr = dialogKonfirmasi("Tambah data pasien?");
	if (confr)
	{
		dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, pasien.nama, sizeof(pasien.nama));
		dialogInput(BLUE, WHITE, "Masukkan Alamat", TIPE_TEXT, pasien.alamat, sizeof(pasien.alamat));
		dialogInput(BLUE, WHITE, "Masukkan Umur", &pasien.umur);
		char allowed[2] = {'L','P'};
		pasien.kelamin = dialogInput(BLUE, WHITE, "Masukkan L(Laki2)/P(Perempuan)", allowed, 2);
		tambahData(pasien);
		dialogSuccess("Data telah ditambahkan");
	}
}

bool HapusPasien(int i)
{
	vector<STpasien> pasien = ambilDataPasien();
	
	if(i > pasien.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
	
	if(dialogKonfirmasi("Hapus pasien?"))
	{
		pasien.erase(pasien.begin() + (i));
		timpaFile(pasien);
		dialogSuccess("Data telah dihapus");
		
		return false;
	}
	
	return true;
}

bool EditPasien(int i)
{
	vector<STpasien> pasien = ambilDataPasien();
	int field;
	int pilih;
	
	bool confr;
	
	if(i > pasien.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
    
	do {
		string menu[5] = {"Nama" , "Alamat", "Kelamin", "Umur", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Edit Pasien", menu, 5, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, pasien[i].nama, sizeof(pasien[i].nama));
			break;
			
			case 2 : 
				dialogInput(BLUE, WHITE, "Masukkan Alamat", TIPE_TEXT, pasien[i].alamat, sizeof(pasien[i].alamat));
			break;
			
			case 4 : 
				dialogInput(BLUE, WHITE, "Masukkan Umur", &pasien[i].umur);
			break;
			
			case 5 :
				confr = true;
			break;
			
			case 3 :
				char allowed[2] = {'L','P'};
				pasien[i].kelamin = dialogInput(BLUE, WHITE, "Masukkan L(Laki2)/P(Perempuan)", allowed, 2);
			break;
		}
		
		if(pilih != 5)
			confr = dialogKonfirmasi("Edit data?");
	} while((pilih < 1 || pilih > 5) || !confr);
	
	if(pilih !=5 && confr)
	{
		timpaFile(pasien);
		dialogSuccess("Data telah diubah");
		return false;
	}
	else
		return true;
}

void MenuPasien(int id)
{
	int i = id2pos(ambilDataPasien(), id);
	
    int pilih;
    bool back;
	do {
		string menu[4] = {"Edit", "Hapus", "Lihat Data Cekup", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Pasien", menu, 4, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				back = EditPasien(i);
			break;
			
			case 2 : 
				back = HapusPasien(i);
			break;
			
			case 3 :
				ListCekup(CEKUP_ALL, "", 1, id);
			break;
			
			case 4 : 
				back = false;
			break;
		}
	} while(pilih < 1 || pilih > 4 || back);
}

void ListPasien(int type, string keyword, int page)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STpasien> data = ambilDataPasien(type, keyword); // Ambil data pasien dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "A(Tmbh Dta) F(Cari) B(Back)"; // Text petunjuk menu
			char menu[3]       = {'A', 'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 3; // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian	
			string pilihanCari = "1: Nama | 2: Alamat | 3: Kelamin | 4: Umur | B: Kembali            "; // Text petunjuk menu pencarian
			char menuCari[5]   = {'1', '2', '3', '4', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 5; // Jumlah menu pencarian
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
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphabet)");
								return ListPasien(PASIEN_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphanumeric)");
								return ListPasien(PASIEN_ALAMAT, carikeyword, 1);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (L/P)");
								return ListPasien(PASIEN_KELAMIN, carikeyword, 1);
							break;
							
							case '4':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan nama (angka)");
								return ListPasien(PASIEN_UMUR, carikeyword, 1);
							break;		
						}
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
			sstm << "Daftar Pasien (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     ¦ 1  ¦ M. Resna Rizki P.    ¦ Jl. Setia Budhi No. 01 Pekanbaru |  Pria   ¦ 20  ¦*/
			char table_header[81] = "| No |         Nama         |               Alamat             | Kelamin | Umr |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(31, 11+k, data[i].alamat);
		    	textxy(66, 11+k, char2Kelamin(data[i].kelamin));
		    	textxy(76, 11+k, data[i].umur);
		    	k++;
		    }
		    
		    string pilihan;
			char menu[6] = {'N', 'P', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != PASIEN_ALL)
				{
				/*            "                                                                               "*/
			    pilihan     = "N(Next Pg) P(Prev Pg) A(Tmbh Dta) X(Pilih Data) F(Cari) B(Back) C(Tmplkan Smua)"; // Text petunjuk menu
				nMenu = 6; // Jumlah menu yang ada
			}
			else
			{
				/*            "                                                                               "*/
				pilihan     = "N(Next Pg) P(Prev Pg) X(Plih Data) F(Cari) B(Back)                 "; // Text petunjuk menu
				nMenu = 5; // Jumlah menu yang ada
			}
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian 
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama | 2: Alamat | 3: Kelamin | 4: Umur | B: Kembali                        "; // Text petunjuk menu pencarian
			char menuCari[5]   = {'1', '2', '3', '4', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 5; // Jumlah menu pencarian
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
						return ListPasien(type, keyword, page + 1);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return ListPasien(type, keyword, page - 1);
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
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphabet)");
								return ListPasien(PASIEN_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphanumeric)");
								return ListPasien(PASIEN_ALAMAT, carikeyword, 1);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (L/P)");
								return ListPasien(PASIEN_KELAMIN, carikeyword, 1);
							break;
							
							case '4':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan nama (angka)");
								return ListPasien(PASIEN_UMUR, carikeyword, 1);
							break;		
						}
					break;
					
					// User memilih menu pilih pasien
					case 'X' :
						int iPasien; // Variable untuk memilih nomor pasien yang dipilih
						barSelect(start+1, end, &iPasien); // Membuat tampilan untuk pilih pasien
						if(iPasien != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							MenuPasien(data[iPasien-1].id); // Tampilkan dialog menu pasien
							needRefresh = true; // set refresh menjadi true agar table dibuat ulang ketika dialog menu ditutup
						}
					break;
					
					case 'C' :
						return ListPasien(PASIEN_ALL, "", 1);
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
	} while(pilih != 'B');
} 

bool PilihPasien(int type, string keyword, int page, STpasien* pasien)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STpasien> data = ambilDataPasien(type, keyword); // Ambil data pasien dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "F(Cari) B(Back)"; // Text petunjuk menu
			char menu[2]       = {'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 2; // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian	
			string pilihanCari = "1: Nama | 2: Alamat | 3: Kelamin | 4: Umur | B: Kembali            "; // Text petunjuk menu pencarian
			char menuCari[5]   = {'1', '2', '3', '4', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 5; // Jumlah menu pencarian
			string carikeyword; // Variable untuk menampung keyword pencarian hasil ketikan
			
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
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphabet)");
								return PilihPasien(PASIEN_NAMA, carikeyword, 1, pasien);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphanumeric)");
								return PilihPasien(PASIEN_ALAMAT, carikeyword, 1, pasien);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (L/P)");
								return PilihPasien(PASIEN_KELAMIN, carikeyword, 1, pasien);
							break;
							
							case '4':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan nama (angka)");
								return PilihPasien(PASIEN_UMUR, carikeyword, 1, pasien);
							break;		
						}
					break;
					
					case 'B' :
						return false;
					break;
				}
			} while(pilih != 'B');
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
			sstm << "PILIH PASIEN : Daftar Pasien (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     ¦ 1  ¦ M. Resna Rizki P.    ¦ Jl. Setia Budhi No. 01 Pekanbaru |  Pria   ¦ 20  ¦*/
			char table_header[81] = "| No |         Nama         |               Alamat             | Kelamin | Umr |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(31, 11+k, data[i].alamat);
		    	textxy(66, 11+k, char2Kelamin(data[i].kelamin));
		    	textxy(76, 11+k, data[i].umur);
		    	k++;
		    }
		    
		    string pilihan;
			char menu[6] = {'N', 'P', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != PASIEN_ALL)
				{
				/*            "                                                                               "*/
			    pilihan     = "N(Next Pg) P(Prev Pg) X(Pilih Data) F(Cari) B(Back) C(Tmplkan Smua)"; // Text petunjuk menu
				nMenu = 6; // Jumlah menu yang ada
			}
			else
			{
				/*            "                                                                               "*/
				pilihan     = "N(Next Pg) P(Prev Pg) X(Plih Data) F(Cari) B(Back)                 "; // Text petunjuk menu
				nMenu = 5; // Jumlah menu yang ada
			}
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian 
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama | 2: Alamat | 3: Kelamin | 4: Umur | B: Kembali                        "; // Text petunjuk menu pencarian
			char menuCari[5]   = {'1', '2', '3', '4', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 5; // Jumlah menu pencarian
			string carikeyword; // Variable untuk menampung keyword pencarian hasil ketikan
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{
					// User memilih menu halaman selanjutnya
					case 'N' : 
						return PilihPasien(type, keyword, page + 1, pasien);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return PilihPasien(type, keyword, page - 1, pasien);
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
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphabet)");
								return PilihPasien(PASIEN_NAMA, carikeyword, 1, pasien);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (alphanumeric)");
								return PilihPasien(PASIEN_ALAMAT, carikeyword, 1, pasien);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_ALPHA, "Masukkan nama (L/P)");
								return PilihPasien(PASIEN_KELAMIN, carikeyword, 1, pasien);
							break;
							
							case '4':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan nama (angka)");
								return PilihPasien(PASIEN_UMUR, carikeyword, 1, pasien);
							break;			
						}
					break;
					
					// User memilih menu pilih pasien
					case 'X' :
						int iPasien; // Variable untuk memilih nomor pasien yang dipilih
						barSelect(start+1, end, &iPasien); // Membuat tampilan untuk pilih pasien
						if(iPasien != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							*pasien = data[iPasien-1];
							
							return true;
						}
					break;
					
					case 'C' :
						return PilihPasien(PASIEN_ALL, "", 1, pasien);
					break;
					
					case 'B' :
						return false;
					break;
				}
			} while(pilih != 'B');
		}
	} while(pilih != 'B');
}
