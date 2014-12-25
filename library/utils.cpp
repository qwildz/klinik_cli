#include <ctime>

#include "utils.h"

STtanggal getDate()
{
	STtanggal tanggal;
	
	time_t t = time(0); // get time now 
	struct tm * now = localtime( & t ); 
	
    tanggal.yy = now->tm_year + 1900;
    tanggal.mm = now->tm_mon + 1;
    tanggal.dd = now->tm_mday;

    return tanggal;
}

string char2Kelamin(char kelamin)
{
	switch(kelamin)
	{
		case 'L' :
			return "Pria";
		break;
		
		case 'P' :
			return "Wanita";
		break;
	}
}

string char2Jenis(char jenis)
{
	switch(toupper(jenis))
	{
		case 'D' :
			return "Dalam";
		break;
		
		case 'L' :
			return "Luar";
		break;
	}
}

string int2string(int number)
{
	std::stringstream sstm;
	sstm << number;
	return sstm.str();	
}

string char2string(char ch)
{
	std::stringstream sstm;
	sstm << ch;
	return sstm.str();	
}

string tolower(string text)
{
	for(int i=0; i < text.size(); i++)
		text[i] = tolower(text[i]);
	
	return text;
}

bool allisalnum(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(!isalnum(text[i]))
			return false;
	}
	
    return true;
}

bool allisdigit(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(!isdigit(text[i]))
			return false;
	}
	
    return true;
}

bool allisalpha(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(!isalpha(text[i]))
			return false;
	}
	
    return true;
}

bool allistext(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(!isalnum(text[i]) && !isspace(text[i]) && !ispunct(text[i]))
			return false;
	}
	
    return true;
}

bool validationtext(int type, string text)
{
	switch(type)
	{
		case TIPE_TEXT:
			return allistext(text);
		break;
		
		case TIPE_ALNUM:
			return allisalnum(text);
		break;
		
		case TIPE_ALPHA:
			return allisalpha(text);
		break;
		
		case TIPE_NUMBER:
			return allisdigit(text);
		break;
	}
}

bool validationchar(char* allowed, int nAllowed, char ch)
{
	for(int i = 0; i < nAllowed; i++)
	{
		if(tolower(allowed[i]) == tolower(ch))
			return true;
	}
		
	return false;
}

int id2pos(vector<STpasien> datas, int id)
{
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].id == id)
			return i;
	}
}

int id2pos(vector<STpenyakit> datas, int id)
{
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].id == id)
			return i;
	}
}

int id2pos(vector<STobat> datas, int id)
{
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].id == id)
			return i;
	}
}

int id2pos(vector<STresep> datas, int id)
{
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].id == id)
			return i;
	}
}

int id2pos(vector<STcekup> datas, int id)
{
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].id == id)
			return i;
	}
}

