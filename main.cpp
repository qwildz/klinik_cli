/*
	Tugas Besar Pemrogramman Dasar
	
	Kelompok 1 - Program Klinik Dokter Umum
	
	Muhammad Resna Rizki Pratama - 10112335
	Dera Rahmat Nugraha - 10112336
	Asmunanda Imam - 10112344
	Rifanda Yulio Difelani - 10112352

*/

#include <iostream>
#include <cstdlib>
#include <conio2.h>

#include "struct.h"
#include "library/ui.h"

#include "menu/mpasien.h"
#include "menu/mpenyakit.h"
#include "menu/mobat.h"
#include "menu/mcekup.h"

using namespace std;

void MenuUtama()
{	
	int pilih;
	do {
		clearscreen();
		element_header();
		
		string menu[5] = {"Pasien", "Penyakit", "Obat", "Cekup", "Keluar"};
		dialogMenu(LIGHTGRAY, WHITE, "Menu Utama", menu, 5, "Pilih menu", &pilih);
		
		switch(pilih)
		{
			case 1 : 
				ListPasien(PASIEN_ALL, "", 1);
			break;
			
			case 2 : 
				ListPenyakit(PENYAKIT_ALL, "", 1);
			break;
			
			case 3 :
				ListObat(OBAT_ALL, "", 1);
			break;
			
			case 4 :
				ListCekup(CEKUP_ALL, "", 1, -1);
			break;	 
			
			case 5:
				exit(0);
			break;
		}
	} while(pilih != 5);
}

int main(int argc, char** argv)
{
	refix_window();
	
	clearscreen();
	element_header();	
	
	MenuUtama();
	
	getch();
	return 0;
}
