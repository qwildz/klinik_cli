#ifndef Hfutils
#define Hfutils

#include <iostream>
#include <vector>

#include "../struct.h"

using namespace std;

vector<STpasien> ambilDataPasien();
vector<STpasien> ambilDataPasien(int type, string keyword);

vector<STpenyakit> ambilDataPenyakit();
vector<STpenyakit> ambilDataPenyakit(int type, string keyword);

vector<STobat> ambilDataObat();
vector<STobat> ambilDataObat(int type, string keyword);

vector<STresep> ambilDataResep();
vector<STresep> ambilDataResep(int id_penyakit);

vector<STcekup> ambilDataCekup();
vector<STcekup> ambilDataCekup(int type, string keyword);
vector<STcekup> ambilDataCekup(int id_pasian);

/*--------------------------------- TAMBAH DATA KE FILE ------------------------------------*/

void tambahData(STpasien data);
void tambahData(STpenyakit data);
void tambahData(STobat data);
void tambahData(STresep data);
void tambahData(STcekup data);

/*--------------------------------- REWRITE FILE ------------------------------------*/

void timpaFile(vector<STpasien> datas);
void timpaFile(vector<STpenyakit> datas);
void timpaFile(vector<STobat> datas);
void timpaFile(vector<STresep> datas);
void timpaFile(vector<STcekup> datas);

#endif
