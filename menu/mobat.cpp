#include <vector>
#include <cmath>
#include <conio2.h>

#include "../struct.h"
#include "../library/futils.h"
#include "../library/ui.h"
#include "../library/utils.h"

#include "mobat.h"

void TambahObat()
{
	STobat obat;
	bool confr;
	
	confr = dialogKonfirmasi("Ingin menambah obat?");
	if(confr)
	{
		dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, obat.nama, sizeof(obat.nama));

		dialogInput(BLUE, WHITE, "Masukkan Harga", &obat.harga);
		
		dialogInput(BLUE, WHITE, "Masukkan Umur", &obat.umur);
		
		tambahData(obat);
	}	
}

bool HapusObat(int i)
{
	vector<STobat> obat = ambilDataObat();
	
	if(i > obat.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
	
	if(dialogKonfirmasi("Hapus obat?"))
	{
		obat.erase(obat.begin() + (i));
		timpaFile(obat);
		
		return false;
	}
	
	return true;
}

bool EditObat(int i)
{
	vector<STobat> obat = ambilDataObat();
	int field;
	int pilih;
	
	bool confr;
	
	if(i > obat.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
    
	do {
		string menu[5] = {"Nama" , "Harga", "Umur", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Edit Pasien", menu, 4, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, obat[i].nama, sizeof(obat[i].nama));
			break;
			
			case 2 : 
			    dialogInput(BLUE, WHITE, "Masukkan Harga", &obat[i].harga);

			break;
			
			case 3 : 
			    dialogInput(BLUE, WHITE, "Masukkan Umur", &obat[i].umur);

			break;
			
			case 4 :
				confr = true;
			break;
		}
		
		if(pilih != 4)
			confr = dialogKonfirmasi("Edit data?");
	} while((pilih < 1 || pilih > 4) || !confr);
	
	if(pilih !=4 && confr)
	{
		timpaFile(obat);
		return false;
	}
	else
		return true;
}

void MenuObat(int id)
{
	int i = id2pos(ambilDataObat(), id);
	
    int pilih;
    bool back;
	do {
		string menu[4] = {"Edit", "Hapus", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Obat", menu, 3, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				back = EditObat(i);
			break;
			
			case 2 : 
				back = HapusObat(i);
			break;
			
			case 3 :
				back = false;
			break;
		}
	} while(pilih < 1 || pilih > 3 || back);
}

void ListObat(int type, string keyword, int page)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STobat> data = ambilDataObat(type, keyword); // Ambil data obat dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "A(Tmbh Dta) F(Cari) B(Kembali)"; // Text petunjuk menu
			char menu[3]       = {'A', 'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 3;                               // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian
			string pilihanCari = "1: Nama | 2: Harga | 3: Umur                                   "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', '3', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 4; // Jumlah menu pencarian
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
						// dan kemudian akan memanggil fungsi tampil obat dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama obat (alphanumeric)");
								return ListObat(OBAT_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan harga");
								return ListObat(OBAT_HARGA, carikeyword, 1);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan min. umur");
								return ListObat(OBAT_UMUR, carikeyword, 1);
							break;	
						}
					break;
					
					case 'A' :
						TambahObat();
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
			sstm << "Daftar Obat (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     */
			char table_header[81] = "| No |              Nama                |             Harga             | Umur |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(43, 11+k, data[i].harga);
		    	textxy(75, 11+k, data[i].umur);
		    	k++;
		    }
		    
		    string pilihan;
			char menu[7] = {'N', 'P', 'A', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != OBAT_ALL)
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
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian 
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama | 2: Harga | 3: Umur                                   "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', '3', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 4; // Jumlah menu pencarian
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
						return ListObat(type, keyword, page + 1);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return ListObat(type, keyword, page - 1);
					break;
					
					case 'A' :
						TambahObat();
						needRefresh = true;
					break;
					
					// User memilih menu pencarian
					case 'F' :
						
						// Mulai membuat tampilan pencarian di bawah dan mendengar inputan untuk menu pencarian
						pilihCari = barMenu(pilihanCari, menuCari, nMenuCari);
						
						// Percabangan menu pencarian yang telah dipilih
						// Tiap kategori akan meminta user menginputkan kata kunci yang sesuai 
						// dan kemudian akan memanggil fungsi tampil obat dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama obat (alphanumeric)");
								return ListObat(OBAT_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan harga");
								return ListObat(OBAT_HARGA, carikeyword, 1);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan min. umur");
								return ListObat(OBAT_UMUR, carikeyword, 1);
							break;	
						}
					break;
					
					// User memilih menu pilih obat
					case 'X' :
						int iObat; // Variable untuk memilih nomor obat yang dipilih
						barSelect(start+1, end, &iObat); // Membuat tampilan untuk pilih obat
						if(iObat != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							MenuObat(data[iObat-1].id); // Tampilkan dialog menu 
							needRefresh = true; // set refresh menjadi true agar table dibuat ulang ketika dialog menu ditutup
						}
					break;
					
					case 'C' :
						return ListObat(OBAT_ALL, "", 1);
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
	} while(pilih != 'B');
	
	
	
}
 
bool PilihObat(int type, string keyword, int page, STobat* obat)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STobat> data = ambilDataObat(type, keyword); // Ambil data obat dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "F(Cari) B(Kembali)"; // Text petunjuk menu
			char menu[2]       = {'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 2;                               // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian
			string pilihanCari = "1: Nama | 2: Harga | 3: Umur                                   "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', '3', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 4; // Jumlah menu pencarian
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
						// dan kemudian akan memanggil fungsi tampil obat dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama obat (alphanumeric)");
								return PilihObat(OBAT_NAMA, carikeyword, 1, obat);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan harga");
								return PilihObat(OBAT_HARGA, carikeyword, 1, obat);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan min. umur");
								return PilihObat(OBAT_UMUR, carikeyword, 1, obat);
							break;	
						}
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
			sstm << "PILIH OBAT : Daftar Obat (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     */
			char table_header[81] = "| No |              Nama                |             Harga             | Umur |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(43, 11+k, data[i].harga);
		    	textxy(75, 11+k, data[i].umur);
		    	k++;
		    }
		    
		    string pilihan;
			char menu[6] = {'N', 'P', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != OBAT_ALL)
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
			string pilihanCari = "1: Nama | 2: Harga | 3: Umur                                   "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', '3', 'B'}; // Karakter yang valid untuk pilihan pencarian
			int nMenuCari = 4; // Jumlah menu pencarian
			string carikeyword; // Variable untuk menampung keyword pencarian hasil ketikan
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{
					// User memilih menu halaman selanjutnya
					case 'N' : 
						return PilihObat(type, keyword, page + 1, obat);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return PilihObat(type, keyword, page - 1, obat);
					break;
					
					// User memilih menu pencarian
					case 'F' :
						
						// Mulai membuat tampilan pencarian di bawah dan mendengar inputan untuk menu pencarian
						pilihCari = barMenu(pilihanCari, menuCari, nMenuCari);
						
						// Percabangan menu pencarian yang telah dipilih
						// Tiap kategori akan meminta user menginputkan kata kunci yang sesuai 
						// dan kemudian akan memanggil fungsi tampil obat dengan memberikan 
						// parameter pencarian yang cocok dengan indikator pencarian dan kata kuncinya.
						switch(pilihCari)
						{
							case '1':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama obat (alphanumeric)");
								return PilihObat(OBAT_NAMA, carikeyword, 1, obat);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan harga");
								return PilihObat(OBAT_HARGA, carikeyword, 1, obat);
							break;	
							
							case '3':
								carikeyword = barSearch(TIPE_NUMBER, "Masukkan min. umur");
								return PilihObat(OBAT_UMUR, carikeyword, 1, obat);
							break;	
						}
					break;
					
					// User memilih menu pilih obat
					case 'X' :
						int iObat; // Variable untuk memilih nomor obat yang dipilih
						barSelect(start+1, end, &iObat); // Membuat tampilan untuk pilih obat
						if(iObat != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							*obat = data[iObat - 1];
							
							return true;
						}
					break;
					
					case 'C' :
						return PilihObat(OBAT_ALL, "", 1, obat);
					break;
					
					case 'B' :
						return false;
					break;
				}
			} while(pilih != 'B');
		}
	} while(pilih != 'B');
}
