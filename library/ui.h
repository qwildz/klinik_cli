#ifndef Hui
#define Hui

#include <windows.h>

using namespace std;

WORD GetColor ();
void SetColor(int color);
void SetColor(int bg, int color);

void SetWindow(int Width, int Height, bool keepWindowSize);
void ShowConsoleCursor(bool showFlag);
void refix_window();

void kotak(int bg, int text, int x1, int y1, int x2, int y2, bool bayangan, bool border);
void kotak(int bg, int text, int x1, int y1, int x2, int y2);

void garis(int bg, int color, int x1, int y1, int x2, int y2, char garis);
void garis(int bg, int color, int x1, int y1, int x2, int y2);
void garisTable(int bg, int color, int x1, int y1, int x2, int y2);

void textxy(int x, int y, string text);
void textxy(int x, int y, int number);
void textxy(int x, int y, float number);
void gettextxy(int x, int y, char* text);
void gettextxy(int x, int y, char* text, int size);
void gettextxy(int x, int y, int* number);

void clearscreen();
void clearscreentable();

void element_header();
void element_title(int bg, int color, string title);

void buatTable(int bg, int color, char* header, int y, int nData);

char barMenu(string pilihan, char* menu, int nMenu);
void barSelect(int start, int end, int* pilih);
string barSearch(int type, string hint);

void dialogSuccess(string text);
void dialogError(string text);
void dialogMenu(int bg, int color, string judul, string* pilihan, int nPilihan, string konfirmasi, int* pilih);
bool dialogKonfirmasi(string konfirmasi);
void dialogInput(int bg, int color, string judul, int type, char* text, int size);
void dialogInput(int bg, int color, string judul, int* number);
char dialogInput(int bg, int color, string judul, char* allowed, int nAllowed);

#endif
