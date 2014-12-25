#ifndef Mpasien
#define Mpasien

using namespace std;

void TambahPasien();
bool HapusPasien(int i);
bool EditPasien(int i);
void MenuPasien(int id);
void ListPasien(int type, string keyword, int page);
bool PilihPasien(int type, string keyword, int page, STpasien* pasien);

#endif
