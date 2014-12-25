#include <vector>
#include <cmath>
#include <conio2.h>

#include "../struct.h"
#include "../library/futils.h"
#include "../library/ui.h"
#include "../library/utils.h"

#include "mresep.h"
#include "mobat.h"

STpenyakit penyakit;

void TambahResepObat()
{
	STresep resep;
	STobat obat;
	
	bool confr;
	confr = dialogKonfirmasi("Tambah obat ke resep?");
	if (confr)
	{
		resep.penyakit = penyakit;
		
		if(PilihObat(OBAT_ALL, "", 1, &obat))
		{
			resep.obat = obat;
			dialogInput(BLUE, WHITE, "Masukkan Dosis", &resep.dosis);
			tambahData(resep);
			dialogSuccess("Sukses menambahkan obat");
		}
		else
			dialogError("Gagal menambahkan obat");
	}
}

bool HapusResepObat(int i)
{
	vector<STresep> resep = ambilDataResep();
	
	if(i > resep.size()) {
		cout << "Urutan data tidak ada!";
		getch();
		return true;
	}
	
	if(dialogKonfirmasi("Hapus obat dari resep?"))
	{
		resep.erase(resep.begin() + (i));
		timpaFile(resep);
		dialogSuccess("Data telah dihapus");
		
		return false;
	}
	
	return true;
}

bool EditResepObat(int i)
{
	vector<STresep> resep = ambilDataResep();
	
	dialogInput(BLUE, WHITE, "Masukkan Dosis", &resep[i].dosis);
	
	if(dialogKonfirmasi("Ubah dosis obat?"))
	{
		timpaFile(resep);
		dialogSuccess("Data telah diubah");
		return false;
	}
	else
		return true;
}

void MenuResepObat(int id)
{
	int i = id2pos(ambilDataResep(), id);
	
    int pilih;
    bool back;
	do {
		string menu[3] = {"Edit Dosis", "Hapus", "Kembali"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Resep Obat", menu, 3, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				back = EditResepObat(i);
			break;
			
			case 2 : 
				back = HapusResepObat(i);
			break;
			
			case 3 :
				back = false;
			break;
		}
	} while(pilih < 1 || pilih > 3 || back);
}

void ListResepObat(int id_penyakit)
{
	// Variable untuk menampung pilihan menu
	char pilih;
	
	// Tampilkan table sampai menu yang dipilih B (kembali)
	do {
		clearscreentable(); // Bersihkan layar
		element_header();	// Tampilkan header
		
		vector<STresep> data = ambilDataResep(id_penyakit);
		penyakit = ambilDataPenyakit(PENYAKIT_ID, int2string(id_penyakit))[0];
		
		// Jika data tidak tersedia
		if(!data.size())
		{
			kotak(RED, WHITE, 22, 16, 58, 18, true, true); // Buat kotak merah
			textxy(34	, 17, "Resep kosong!");	   // Tampilkan text tak ditemukan
			
			// Persiapan untuk membuat menu di bagian bawah
			string pilihan     = "A(Tmbh Obat) B(Back)"; // Text petunjuk menu
			char menu[2]       = {'A', 'B'};             // Karakter yang valid untuk dipilih
			int nMenu = 2; // Jumlah menu yang ada
			
			bool needRefresh = false; // Untuk menentukan apakah table perlu dibuat ulang karena dialog menu muncul
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{		
					case 'A' :
						TambahResepObat();
						needRefresh = true;
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
		// Jika data tersedia
		else
		{
			// Mulai membuat judul / title dengan memberikan status data
			string title; 
			std::stringstream sstm;
			sstm << "Daftar Resep Obat Penyakit " << data[0].penyakit.nama << " (" << data.size() << " obat)" ;
			title = sstm.str();
			
			// Render title yang telah dibuat
			element_title(WHITE, BLACK, title);
			
			/* Membuat header untuk table
								     00000000011111111112222222222333333333344444444445555555555666666666677777777778
								     12345678901234567890123456789012345678901234567890123456789012345678901234567890
								     ¦	  |							  |                    |                 |      |*/
			char table_header[81] = "| No |           Nama            |        Harga       |       Dosis     | Umur |";
		    
		    // Render table 
		    buatTable(WHITE, BLACK, table_header, 8, data.size());
		    
		    // Mulai menampilan data2 yang ada ke layar
		    int k = 0;
		    for(int i = 0; i < data.size(); i++)
		    {
		    	textxy(3, 11+k, i+1);
		    	textxy(8, 11+k, data[i].obat.nama);
		    	textxy(37, 11+k, data[i].obat.harga);
		    	textxy(64, 11+k, data[i].dosis);
		    	textxy(75, 11+k, data[i].obat.umur);
		    	k++;
		    }
		    
			/*                   "                                                                   "*/
			string pilihan = "A(Tmbh Obat) X(Plih Obat) B(Back)                                      "; // Text petunjuk menu
			char menu[7] = {'A', 'X', 'B'}; // Karakter yang valid untuk dipilih
			int nMenu = 6; // Jumlah menu yang ada
			
			bool needRefresh = false; // Untuk menentukan apakah table perlu dibuat ulang karena dialog menu muncul
			
			// Lakukan terus menanyakan menu yang akan dipilih sampai menu yang dipilih B (kembali)
			do {
				pilih = barMenu(pilihan, menu, nMenu); // Mulai membuat tampilan menu di bawah dan mendengar inputan untuk menu
				
				// Percabangan menu yang telah dipilih
				switch(pilih)
				{		
					// User memilih menu pilih pasien
					case 'X' :
						int iResep; // Variable untuk memilih nomor pasien yang dipilih
						barSelect(1, data.size(), &iResep); // Membuat tampilan untuk pilih pasien
						if(iResep != 0) // Jika yang diinputkan bukan 0 (Kembali)
						{
							MenuResepObat(data[iResep-1].id); // Tampilkan dialog menu pasien
							needRefresh = true; // set refresh menjadi true agar table dibuat ulang ketika dialog menu ditutup
						}
					break;
					
					case 'A' :
						TambahResepObat();
						needRefresh = true;
					break;
				}
			} while(pilih != 'B' && !needRefresh);
		}
	} while(pilih != 'B');
}
