#include <vector>
#include <cmath>
#include <conio2.h>

#include "../struct.h"
#include "../library/futils.h"
#include "../library/ui.h"
#include "../library/utils.h"

#include "mpenyakit.h"
#include "mresep.h"

void TambahPenyakit()
{
	STpenyakit penyakit;
	bool confr;
	
	confr = dialogKonfirmasi("Ingin menambah penyakit?");
	if(confr)
	{
		dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, penyakit.nama, sizeof(penyakit.nama));

		char allowed[2] = {'D','L'};
		penyakit.jenis = dialogInput(BLUE, WHITE, "Masukkan D(Dalam)/L(Luar)", allowed, 2);
		
		tambahData(penyakit);
	}	
}

bool HapusPenyakit(int i)
{
	vector<STpenyakit> penyakit = ambilDataPenyakit();
	
	if(i > penyakit.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
	
	if(dialogKonfirmasi("Hapus penyakit?"))
	{
		penyakit.erase(penyakit.begin() + (i));
		timpaFile(penyakit);
		dialogSuccess("Data telah dihapus");
		
		return false;
	}
	
	return true;
}

bool EditPenyakit(int i)
{
	vector<STpenyakit> penyakit = ambilDataPenyakit();
	int field;
	int pilih;
	
	bool confr;
	
	if(i > penyakit.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
    
	do {
		string menu[5] = {"Nama" , "Jenis", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Edit Pasien", menu, 3, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				dialogInput(BLUE, WHITE, "Masukkan Nama", TIPE_TEXT, penyakit[i].nama, sizeof(penyakit[i].nama));
			break;
			
			
			case 3 :
				confr = true;
			break;
			
			case 2 : 
				char allowed[2] = {'D','L'};
				penyakit[i].jenis = dialogInput(BLUE, WHITE, "Masukkan D(Dalam)/L(Luar)", allowed, 2);

			break;

		}
		
		if(pilih != 3)
			confr = dialogKonfirmasi("Edit data?");
	} while((pilih < 1 || pilih > 3) || !confr);
	
	if(pilih !=3 && confr)
	{
		timpaFile(penyakit);
		dialogSuccess("Data telah diubah");
		return false;
	}
	else
		return true;
}

void MenuPenyakit(int id)
{
	int i = id2pos(ambilDataPenyakit(), id);
	
    int pilih;
    bool back;
	do {
		string menu[5] = {"Edit", "Hapus", "Lihat Resep Obat", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Penyakit", menu, 4, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				back = EditPenyakit(i);
			break;
			
			case 2 : 
				back = HapusPenyakit(i);
			break;
			
			case 3 :
				ListResepObat(id);
				back = false;
			break;
			
			case 4 :
				back = false;
			break;
		}
	} while(pilih < 1 || pilih > 4 || back);
}

void ListPenyakit(int type, string keyword, int page)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STpenyakit> data = ambilDataPenyakit(type, keyword); // Ambil data obat dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "A(Tmbh Dta) F(Cari) B(Back)"; // Text petunjuk menu
			char menu[3]       = {'A', 'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 3;                               // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian
			string pilihanCari = "1: Nama | 2: Jenis                                    "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
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
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama penyakit (alphanumeric)");
								return ListPenyakit(PENYAKIT_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan jenis penyakit");
								return ListPenyakit(PENYAKIT_JENIS, carikeyword, 1);
							break;	
						}
					break;
					
					case 'A' : 
						TambahPenyakit();
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
			sstm << "Daftar Penyakit (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     */
			char table_header[81] = "| No |              Nama                       |             Jenis             |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(62, 11+k, char2Jenis(data[i].jenis));
		    	k++;
		    }
		    
		    string pilihan;
			char menu[7] = {'N', 'P', 'A', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != PENYAKIT_ALL)
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
			string pilihanCari = "1: Nama | 2: Jenis                                                             "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
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
						return ListPenyakit(type, keyword, page + 1);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return ListPenyakit(type, keyword, page - 1);
					break;
					
					case 'A' : 
						TambahPenyakit();
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
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama penyakit (alphanumeric)");
								return ListPenyakit(PENYAKIT_NAMA, carikeyword, 1);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan jenis penyakit");
								return ListPenyakit(PENYAKIT_JENIS, carikeyword, 1);
							break;	
						}
					break;
					
					// User memilih menu pilih obat
					case 'X' :
						int iPenyakit; // Variable untuk memilih nomor obat yang dipilih
						barSelect(start+1, end, &iPenyakit); // Membuat tampilan untuk pilih obat
						if(iPenyakit != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							MenuPenyakit(data[iPenyakit-1].id); // Tampilkan dialog menu 
							needRefresh = true; // set refresh menjadi true agar table dibuat ulang ketika dialog menu ditutup
						}
					break;
					
					case 'C' :
						return ListPenyakit(PENYAKIT_ALL, "", 1);
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
	} while(pilih != 'B');
}

bool PilihPenyakit(int type, string keyword, int page, STpenyakit* penyakit)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STpenyakit> data = ambilDataPenyakit(type, keyword); // Ambil data obat dengan tipe pencarian dan keyword
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(30, 17, "Data tidak ditemukan!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "F(Cari) B(Back)"; // Text petunjuk menu
			char menu[2]       = {'F', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 2;                               // Jumlah menu yang ada
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian
			string pilihanCari = "1: Nama | 2: Jenis                                    "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
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
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama penyakit (alphanumeric)");
								return PilihPenyakit(PENYAKIT_NAMA, carikeyword, 1, penyakit);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan jenis penyakit");
								return PilihPenyakit(PENYAKIT_JENIS, carikeyword, 1, penyakit);
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
			sstm << "PILIH PENYAKIT : Daftar Penyakit (" << start+1 << " - " << end << " dari " << data.size() << ")" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     */
			char table_header[81] = "| No |              Nama                       |             Jenis             |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, nData);
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = start; i < end; i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].nama);
		    	textxy(62, 11+k, char2Jenis(data[i].jenis));
		    	k++;
		    }
		    
		    string pilihan;
			char menu[6] = {'N', 'P', 'X', 'F', 'B', 'C'}; // Karakter yang valid untuk dipilih
			int nMenu;
			
			if(type != PENYAKIT_ALL)
			{
				/*            "                                                                               "*/
			    pilihan     = "N(Next Pg) P(Prev Pg) X(Pilih Data) F(Cari) B(Back) C(Tmplkan Smua)            "; // Text petunjuk menu
				nMenu = 6; // Jumlah menu yang ada
			}
			else
			{
				/*            "                                                                               "*/
				pilihan     = "N(Next Pg) P(Prev Pg) X(Plih Data) F(Cari) B(Back)                             "; // Text petunjuk menu
				nMenu = 5; // Jumlah menu yang ada
			}
			
			// Persiapan untuk membuat menu pencarian
			char pilihCari;	// Variable untuk menampung pilihan menu pencarian 
			/*                   "                                                                               "*/
			string pilihanCari = "1: Nama | 2: Jenis                                                             "; // Text petunjuk menu pencarian
			char menuCari[4]   = {'1', '2', 'B'}; // Karakter yang valid untuk pilihan pencarian
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
						return PilihPenyakit(type, keyword, page + 1, penyakit);
					break;
					
					// User memilih menu halaman sebelumnya
					case 'P' : 
						return PilihPenyakit(type, keyword, page - 1, penyakit);
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
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan nama penyakit (alphanumeric)");
								return PilihPenyakit(PENYAKIT_NAMA, carikeyword, 1, penyakit);
							break;	
							
							case '2':
								carikeyword = barSearch(TIPE_ALNUM, "Masukkan jenis penyakit");
								return PilihPenyakit(PENYAKIT_JENIS, carikeyword, 1, penyakit);
							break;	
						}
					break;
					
					// User memilih menu pilih obat
					case 'X' :
						int iPenyakit; // Variable untuk memilih nomor obat yang dipilih
						barSelect(start+1, end, &iPenyakit); // Membuat tampilan untuk pilih obat
						if(iPenyakit != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							*penyakit = data[iPenyakit - 1];
							return true;
						}
					break;
					
					case 'C' :
						return PilihPenyakit(PENYAKIT_ALL, "", 1, penyakit);
					break;
					
					case 'B' :
						return false;
					break;
				}
			} while(pilih != 'B');
		}
	} while(pilih != 'B');
}
