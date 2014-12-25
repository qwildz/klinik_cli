#ifndef Mobat
#define Mobat

using namespace std;

void TambahObat();
bool HapusObat(int i);
bool EditObat(int i);
void MenuObat(int id);
void ListObat(int type, string keyword, int page);
bool PilihObat(int type, string keyword, int page, STobat* obat);

#endif
