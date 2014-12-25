#ifndef Mpenyakit
#define Mpenyakit

using namespace std;

void TambahPenyakit();
bool HapusPenyakit(int i);
bool EditPenyakit(int i);
void MenuPenyakit(int id);
void ListPenyakit(int type, string keyword, int page);
bool PilihPenyakit(int type, string keyword, int page, STpenyakit* penyakit);

#endif
