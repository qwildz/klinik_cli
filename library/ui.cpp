#include <iostream>
#include <cstdlib>

#include <cstdio>
#include <conio2.h>
#include <windows.h>

#include "ui.h"
#include "utils.h"

using namespace std;

/*
	Fungsi untuk mendapatkan warna text dan background text
*/
WORD GetColor ()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hConsole, &con_info);
	return con_info.wAttributes;
}

/*
	Fungsi untuk mengeset warna text dan background text
	color			Warna kombinasi (text + bg * 16)
*/
void SetColor(int color)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hConsole, color);
}

/*
	Fungsi untuk mengeset warna text dan background text
	bg				Warna background
	color			Warna text
*/
void SetColor(int bg, int color)
{
	SetColor(color + bg * 16);
}

/*
	Fungsi untuk mengeset besar window dan buffer screen console dan menghilangkan scroll
	Width			Lebar window
	Height			Tinggi window
	keepWindowSize	Mengubah besar window
*/
void SetWindow(int Width, int Height, bool keepWindowSize) 
{ 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);       // Set Buffer Size 
    if(!keepWindowSize)
		SetConsoleWindowInfo(Handle, TRUE, &Rect);   // Set Window Size 
} 

/*
	Fungsi untuk menyembunyikan dan menampilkan blink cursor text
	showFlag		(true = tampil, false = sembunyi)
*/
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

/*
	Fungsi untuk membetulkan tampilan
*/
void refix_window()
{
	SetWindow(79,30, true);
	SetWindow(80,30, false);
	
	ShowConsoleCursor(false);
}

/*
	Fungsi untuk membuat kotak
	
	bg			Warna background kotak
	text		Warna text
	x1			Koordinat awal x
	y1			Koordinat awal y
	x2			Koordinat akhir	x
	y2			Koordinat akhir y
	bayangan	Menampilkan bayangan kotak
	border		Tambahkan garis tepi
*/
void kotak(int bg, int text, int x1, int y1, int x2, int y2, bool bayangan, bool border)
{
	// Buat kotak abu terlebih dahulu
	if(bayangan) 
		kotak(DARKGRAY, DARKGRAY, x1+1, y1+1, x2+1, y2+1, false, false);
	
	SetColor(bg, bg);
	
	for(int i=y1; i<=y2; i++)
	{
		gotoxy(x1, i);
		for(int k=x1; k<=x2; k++)
		{
			cout << ' ';
		}
	}
	
	SetColor(bg, text);
	
	if(border)
	{			
		// Garis atas dan bawah
		for(int i=x1; i<=x2; i++)
		{
			gotoxy(i,y1);
			cout << char(205);
			
			gotoxy(i,y2);
			cout << char(205);
		}
		
		// Garis kiri dan kanan
		for(int i=y1+1; i<=y2-1; i++)
		{
			gotoxy(x1,i);
			cout << char(186);
			
			gotoxy(x2,i);
			cout << char(186);
		}	
		
		// Garis ujung	
		gotoxy(x1,y1);
		cout << char(201);
		
		gotoxy(x2,y1);
		cout << char(187);
		
		gotoxy(x1,y2);
		cout << char(200);
		
		gotoxy(x2,y2);
		cout << char(188);
	}
	
	if(border)
		gotoxy(x1+1, y1+1);
	else
		gotoxy(x1, y1);
	
	// Membetulkan tampilan karakter yang tidak berdempetan
	refix_window();
}

/*
	Fungsi untuk membuat kotak (tanpa bayangan dan border)
*/
void kotak(int bg, int text, int x1, int y1, int x2, int y2)
{
	kotak(bg, text, x1, y1, x2, y2, false, false);
}

/*
	Fungsi untuk membuat garis lurus horz/vert
	
	bg			Warna background garis
	color		Warna garis
	x1			Koordinat awal x
	y1			Koordinat awal y
	x2			Koordinat akhir	x
	y2			Koordinat akhir y
	garis		Karakter untuk membuat garis
*/
void garis(int bg, int color, int x1, int y1, int x2, int y2, char garis)
{
	
	// Menyimpan warna text dan background ke variable saved_colors	
	int saved_colors = GetColor();
	
	// Mengeset warna garis dan background yang ditentukan
	SetColor(bg, color);
	
	gotoxy(x1, y1);
	
	if(x1 == x2)
	{
		for(int i=y1; i<=y2; i++)
		{
			gotoxy(x1, i);
			cout << garis;
		}
	}
	else
	{
		for(int i=x1; i<=x2; i++)
			cout << garis;
	}
	
	// Mengembalikan warna ke semula
	SetColor(saved_colors);
	
	refix_window();
}

/*
	Fungsi untuk membuat garis lurus horz/vert (dengan karakter 205 atau 186)
	
	bg			Warna background garis
	color		Warna garis
	x1			Koordinat awal x
	y1			Koordinat awal y
	x2			Koordinat akhir	x
	y2			Koordinat akhir y
*/
void garis(int bg, int color, int x1, int y1, int x2, int y2)
{
	if(x1 == x2)
		garis(bg, color, x1, y1, x2, y2, 186);
	else
		garis(bg, color, x1, y1, x2, y2, 205);
}

/*
	Fungsi untuk membuat garis lurus horz/vert dalam kotak
	
	bg			Warna background garis
	color		Warna garis
	x1			Koordinat awal x
	y1			Koordinat awal y
	x2			Koordinat akhir	x
	y2			Koordinat akhir y
*/
void garisTable(int bg, int color, int x1, int y1, int x2, int y2)
{
	if(x1 == x2)
	{
		garis(bg, color, x1, y1, x2, y2, 186);
		garis(bg, color, x1, y1, x2, y1, 203);
		garis(bg, color, x1, y2, x2, y2, 202);
	}
	else
	{
		garis(bg, color, x1, y1, x2, y2, 205);
		garis(bg, color, x1, y1, x1, y2, 204);
		garis(bg, color, x2, y1, x2, y2, 185);
	}
}

/*
	Fungsi untuk menampikan string pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	text		Text yang akan ditampilkan
*/
void textxy(int x, int y, string text)
{
	gotoxy(x, y);
	cout << text;
}

/*
	Fungsi untuk menampikan integer pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	number		Bilangan bulat yang akan ditampilkan
*/
void textxy(int x, int y, int number)
{
	gotoxy(x, y);
	cout << number;
}

/*
	Fungsi untuk menampikan float pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	number		Bilangan desimal yang akan ditampilkan
*/
void textxy(int x, int y, float number)
{
	gotoxy(x, y);
	printf("%.2f", number);
}

/*
	Fungsi untuk mengambil inputtan string pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	text		Variable string untuk menampung inputtan
*/
void gettextxy(int x, int y, char* text)
{
	fflush(stdin);
	cin.clear();
	gotoxy(x, y);
	
	ShowConsoleCursor(true);
	gets(text);
	ShowConsoleCursor(false);
}

/*
	Fungsi untuk mengambil inputtan string pada koordinat dengan batasan input
	
	x			Koordinat x
	y			Koordinat y
	text		Variable string untuk menampung inputtan
	size		Max panjang karakter
*/
void gettextxy(int x, int y, char* text, int size)
{
	fflush(stdin);
	cin.clear();
	gotoxy(x, y);
	
	ShowConsoleCursor(true);
	cin.getline(text, size);
	ShowConsoleCursor(false);
}


/*
	Fungsi untuk mengambil inputtan integer pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	text		Variable integer untuk menampung inputtan
*/
void gettextxy(int x, int y, int* number)
{
	fflush(stdin);
	cin.clear();
	gotoxy(x, y);
	
	ShowConsoleCursor(true);
	cin >> *number;
	
	if(cin.fail())
	{
		*number	= -9999;
	}
	
	ShowConsoleCursor(false);
}

/*
	Fungsi untuk mengambil inputtan char pada koordinat
	
	x			Koordinat x
	y			Koordinat y
	text		Variable char untuk menampung inputtan
*/
char getcharxy(int x, int y)
{
	char ch;
	fflush(stdin);
	gotoxy(x, y);
	
	ShowConsoleCursor(true);
	ch = getchar();
	ShowConsoleCursor(false);
	
	return ch;
}

/*
	Fungsi untuk membersihkan layar
*/
void clearscreen()
{
	clrscr();
	kotak(WHITE, BLACK, 1, 1, 80, 30);
}

/*
	Fungsi untuk membersihkan layar tampilan table
*/
void clearscreentable()
{
	clrscr();
	kotak(BLACK, WHITE, 1, 1, 80, 30);
	kotak(LIGHTGRAY, BLACK, 1, 1, 80, 29);
	kotak(WHITE, BLACK, 1, 1, 80, 28);
}

/*
	Fungsi untuk membuat header
*/
void element_header()
{
	//garis(WHITE, BLACK, 1, 1, 80, 1);
	//garis(WHITE, BLACK, 1, 6, 80, 6);
	
	kotak(BLUE, WHITE, 1, 1, 80, 4);
	
	garis(BLUE, LIGHTGRAY, 1, 1, 80, 1, '=');
	garis(BLUE, LIGHTGRAY, 1, 4, 80, 4, '=');
	
	textxy(31, 2, "KLINIK SUMBER SEHAT");
	textxy(32, 3, "dr.  Asmuri Deres");
	
	gotoxy(1, 6);
}

void element_title(int bg, int color, string title)
{
	garis(bg, color, 1, 5, 80, 5);
	garis(bg, color, 1, 7, 80, 7);
	SetColor(bg, color);
	
	int mid = title.length()/2;
	textxy(40-mid, 6, title);
}

void buatTable(int bg, int color, char* header, int y, int nData)
{
	kotak(bg, color, 1, 8, 80, 28);
	SetColor(bg, color);
	int separator[10];
	
	int nSeparator = 0;
	for(int i = 0; i < 80; i++)
	{
		if(header[i] == '|')
			separator[nSeparator++] = i+1;
	}
	
	textxy(1, y + 1, header);
	
	garis(bg, color, 1, y, 80, y);
	garis(bg, color, 1, y + 2, 80, y + 2);
	garis(bg, color, 1, y + 2 + nData + 1, 80, y + 2 + nData + 1);
	for(int i = 0; i < nSeparator; i++)
	{
		garis(bg, color, separator[i], y, separator[i], y + 2 + nData + 1);
		
		if(i == 0)
		{
			gotoxy(separator[i], y);
			cout << char(201);
			
			gotoxy(separator[i], y + 2);
			cout << char(204);
			
			gotoxy(separator[i], y + 2 + nData + 1);
			cout << char(200);
		}
		else if(i == nSeparator-1)
		{
			gotoxy(separator[i], y);
			cout << char(187);
			
			gotoxy(separator[i], y + 2);
			cout << char(185);
			
			gotoxy(separator[i], y + 2 + nData + 1);
			cout << char(188);
		}
		else
		{
			gotoxy(separator[i], y);
			cout << char(203);
			
			gotoxy(separator[i], y + 2);
			cout << char(206);
			
			gotoxy(separator[i], y + 2 + nData + 1);
			cout << char(202);
		}
	}
}

char barMenu(string pilihan, char* menu, int nMenu)
{
	char pilih;
	bool match = false;
	do
	{
		kotak(LIGHTGRAY, BLACK, 1, 29, 80, 29);
		
		SetColor(BLACK, WHITE);
		textxy(1, 30, pilihan);    
		
	    SetColor(LIGHTGRAY, BLACK);
	    textxy(1, 29, "Pilih menu : [");
		textxy(16, 29, "]");
		pilih = getcharxy(15, 29);
		
		for(int i = 0; i < nMenu; i++)
		{
			if(toupper(menu[i]) == toupper(pilih))
			{
				match = true;
				break;
			}
		}
		
		if(!match)
		{
			kotak(RED, WHITE, 1, 29, 80, 29);
			textxy(1, 29, "Pilihan tidak valid!");
			getch();
		}
	} while(!match);
	
	return toupper(pilih);
}

void barSelect(int start, int end, int* pilih)
{
	do {
		kotak(BROWN, WHITE, 1, 29, 80, 29);
		
	    SetColor(BROWN, WHITE);
	    
	    gotoxy(1, 29);
	    printf("Pilih %2i - %2i atau 0(Kembali): [  ]", start, end);
		
		gettextxy(33, 29, pilih);
		
		if((*pilih < start || *pilih > end) && *pilih != 0)
		{
			kotak(RED, WHITE, 1, 29, 80, 29);
			textxy(1, 29, "Pilihan tidak valid!");
			getch();
		}
	} while((*pilih < start || *pilih > end) && *pilih != 0);
}

string barSearch(int type, string hint)
{
	bool valid;
	char keyword[50];
	hint = hint + " : ";
	
	do {
		kotak(BROWN, WHITE, 1, 29, 80, 29);
		
	    SetColor(BROWN, WHITE);
	    
	    textxy(1, 29, hint);
		gettextxy(hint.length(), 29, keyword);
		
		valid = validationtext(type, keyword);
				
		if(!valid)
		{
			kotak(RED, WHITE, 1, 29, 80, 29);
			textxy(1, 29, "Kata kunci tidak valid!");
			getch();
		}
	} while(!valid);
	
	return string(keyword);
}

void dialogSuccess(string text)
{
	kotak(GREEN, WHITE, 22, 16, 58, 18, false, true);
	
	int mid = text.length()/2;
	textxy(40-mid, 17, text);
	
	getch();
}

void dialogError(string text)
{
	kotak(RED, WHITE, 22, 16, 58, 18, false, true);
	
	int mid = text.length()/2;
	textxy(40-mid, 17, text);
	
	getch();
}

void dialogMenu(int bg, int color, string judul, string* pilihan, int nPilihan, string konfirmasi, int* pilih)
{	
	do {
		*pilih = 0;
		kotak(bg, color, 20, 10, 60, 24, true, true);
		garisTable(bg, color, 20, 14, 60, 14);
		
		int mid = judul.length()/2;
		textxy(40-mid, 12, judul);
		
		for(int i = 0; i < nPilihan; i ++)
		{
			gotoxy(22, 16 + i);
			printf("%i. %s", i+1, pilihan[i].c_str());
		}
		
		textxy(22, 16 + nPilihan + 1, konfirmasi);
		textxy(22 + konfirmasi.length(), 16 + nPilihan + 1, " : [");
		textxy(22 + konfirmasi.length() + 5, 16 + nPilihan + 1, "]");
		
		
		gettextxy(22 + konfirmasi.length() + 4, 16 + nPilihan + 1 , pilih);
		if(*pilih < 1 || *pilih > nPilihan)
		{
			dialogError("Pilihan tidak valid!");
		}
	} while(*pilih < 1 || *pilih > nPilihan);
}

bool dialogKonfirmasi(string konfirmasi)
{
	char pilih;
	
	do {
		kotak(BROWN, WHITE, 20, 15, 60, 19, true, true);
		
		textxy(23, 17, konfirmasi);
		textxy(23 + konfirmasi.length(), 17, " (Y/T) : [");
		textxy(23 + konfirmasi.length() + 11, 17, "]");
		
		pilih = getcharxy(23 + konfirmasi.length() + 10, 17);
		
		if(toupper(pilih) != 'Y' && toupper(pilih) != 'T')
		{
			dialogError("Pilih Y(Ya) atau T(Tidak)");
		}
	} while(toupper(pilih) != 'Y' && toupper(pilih) != 'T');
	
	if(toupper(pilih) == 'Y')
		return true;
	else
		return false;
}

void dialogInput(int bg, int color, string judul, int type, char* text, int size)
{
	bool valid;
	
	do {
		kotak(bg, color, 20, 13, 60, 21, true, true);
		garisTable(bg, color, 20, 15, 60, 15);
		
		int mid = judul.length()/2;
		textxy(40-mid, 14, judul);
		
		kotak(DARKGRAY, WHITE, 22, 17, 58, 19);
		
		gettextxy(23, 18, text, size);
		
		valid = validationtext(type, text);
				
		if(!valid)
		{
			dialogError("Inputtan tidak valid!");
		}
	} while(!valid);
}

void dialogInput(int bg, int color, string judul, int* number)
{
	bool valid;
	
	do {
		kotak(bg, color, 20, 13, 60, 21, true, true);
		garisTable(bg, color, 20, 15, 60, 15);
		
		int mid = judul.length()/2;
		textxy(40-mid, 14, judul);
		
		kotak(DARKGRAY, WHITE, 22, 17, 58, 19);
		
		gettextxy(23, 18, number);
		
		valid = validationtext(TIPE_NUMBER, int2string(*number));
				
		if(!valid)
		{
			dialogError("Inputtan tidak valid!");
		}
	} while(!valid);
}

char dialogInput(int bg, int color, string judul, char* allowed, int nAllowed)
{
	bool valid;
	char ch;
	
	do {
		kotak(bg, color, 20, 13, 60, 21, true, true);
		garisTable(bg, color, 20, 15, 60, 15);
		
		int mid = judul.length()/2;
		textxy(40-mid, 14, judul);
		
		kotak(DARKGRAY, WHITE, 22, 17, 58, 19);
		
		ch = getcharxy(23, 18);
		
		valid = validationchar(allowed, nAllowed, ch);
				
		if(!valid)
		{
			dialogError("Inputtan tidak valid!");
		}
	} while(!valid);
	
	return toupper(ch);
}

