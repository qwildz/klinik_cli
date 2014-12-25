#ifndef Hutils
#define Hutils

#include <sstream>
#include <vector>

#include "../struct.h"

using namespace std;

STtanggal getDate();

string char2Kelamin(char kelamin);
string char2Jenis(char jenis);

string int2string(int number);
string char2string(char ch);

string tolower(string text);

bool allisalnum(string text);
bool allisdigit(string text);
bool allisalpha(string text);
bool allistext(string text);

bool validationtext(int type, string text);
bool validationchar(char* allowed, int nAllowed, char ch);

int id2pos(vector<STpasien> datas, int id);
int id2pos(vector<STpenyakit> datas, int id);
int id2pos(vector<STobat> datas, int id);
int id2pos(vector<STresep> datas, int id);
int id2pos(vector<STcekup> datas, int id);

#endif
