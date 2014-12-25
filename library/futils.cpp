#include <iostream>
#include <cstdlib>

#include <fstream>
#include <conio2.h>

#include "futils.h"
#include "utils.h"

using namespace std;

vector<STpasien> ambilDataPasien()
{
	vector<STpasien> datas;
	STpasien data;
	
	ifstream myFile(FILE_PASIEN, ios::binary);
	
	if(!myFile)
    {
       return datas;
    }
     
	myFile.read((char*)&data, sizeof(STpasien));
    while(!myFile.eof())
    {
    	datas.push_back(data);	
		myFile.read((char*)&data, sizeof(STpasien));
    }
    
	myFile.close();
	
	return datas; 
}

vector<STpasien> ambilDataPasien(int type, string keyword)
{
	vector<STpasien> datas = ambilDataPasien();
	vector<STpasien> found;
	
	if(type == PASIEN_ALL) return datas;
	
	for(int i = 0; i < datas.size(); i++)
	{
		switch(type)
		{
			case PASIEN_ID :
				if(int2string(datas[i].id).compare(keyword) == 0)
					found.push_back(datas[i]);
			break;
			
			case PASIEN_UMUR :
				if(int2string(datas[i].umur).compare(keyword) == 0)
					found.push_back(datas[i]);
			break;
			
			case PASIEN_NAMA :
				if(tolower(string(datas[i].nama)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
			
			case PASIEN_ALAMAT :
				if(tolower(string(datas[i].alamat)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
			
			case PASIEN_KELAMIN :
				if(tolower(char2string(datas[i].kelamin)).compare(tolower(keyword)) == 0)
					found.push_back(datas[i]);
			break;
		}
	}
	
	return found;
}

vector<STpenyakit> ambilDataPenyakit()
{
	vector<STpenyakit> datas;
	STpenyakit data;
	
	ifstream myFile(FILE_PENYAKIT, ios::binary);
	
	if(!myFile)
    {
       return datas;
    }
     
	myFile.read((char*)&data, sizeof(STpenyakit));
    while(!myFile.eof())
    {
    	datas.push_back(data);	
		myFile.read((char*)&data, sizeof(STpenyakit));
    }
    
	myFile.close();
	
	return datas; 
}

vector<STpenyakit> ambilDataPenyakit(int type, string keyword)
{
	vector<STpenyakit> datas = ambilDataPenyakit();
	vector<STpenyakit> found;
	
	if(type == PENYAKIT_ALL) return datas;
	
	for(int i = 0; i < datas.size(); i++)
	{
		switch(type)
		{
			case PENYAKIT_ID :
				if(int2string(datas[i].id).compare(keyword) == 0)
					found.push_back(datas[i]);
			break;
			
			case PENYAKIT_NAMA :
				if(tolower(string(datas[i].nama)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
			
			case PENYAKIT_JENIS :
				if(tolower(char2string(datas[i].jenis)).compare(tolower(keyword)) == 0)
					found.push_back(datas[i]);
			break;
		}
	}
	
	return found;
}

vector<STobat> ambilDataObat()
{
	vector<STobat> datas;
	STobat data;
	
	ifstream myFile(FILE_OBAT, ios::binary);
	
	if(!myFile)
    {
       return datas;
    }
     
	myFile.read((char*)&data, sizeof(STobat));
    while(!myFile.eof())
    {
    	datas.push_back(data);	
		myFile.read((char*)&data, sizeof(STobat));
    }
    
	myFile.close();
	
	return datas; 
}

vector<STobat> ambilDataObat(int type, string keyword)
{
	vector<STobat> datas = ambilDataObat();
	vector<STobat> found;
	
	if(type == OBAT_ALL) return datas;
	
	for(int i = 0; i < datas.size(); i++)
	{
		switch(type)
		{
			case OBAT_ID :
				if(int2string(datas[i].id).compare(keyword) == 0)
					found.push_back(datas[i]);
			break;
			
			case OBAT_UMUR :
				if(datas[i].umur >= atoi(keyword.c_str()))
					found.push_back(datas[i]);
			break;
			
			case OBAT_NAMA :
				if(tolower(string(datas[i].nama)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
			
			case OBAT_HARGA :
				if(tolower(int2string(datas[i].harga)).compare(tolower(keyword)) == 0)
					found.push_back(datas[i]);
			break;
		}
	}
	
	return found;
}

vector<STresep> ambilDataResep()
{
	vector<STresep> datas;
	STresep data;
	
	ifstream myFile(FILE_RESEP, ios::binary);
	
	if(!myFile)
    {
       return datas;
    }
     
	myFile.read((char*)&data, sizeof(STresep));
    while(!myFile.eof())
    {
    	vector<STobat> obat = ambilDataObat(OBAT_ID, int2string(data.obat.id));
    	vector<STpenyakit> penyakit = ambilDataPenyakit(PENYAKIT_ID, int2string(data.penyakit.id));

		if(obat.size() != 0 && penyakit.size() != 0)
		{
			data.obat = obat[0];
			data.penyakit = penyakit[0];
			datas.push_back(data);	
		}
		
		myFile.read((char*)&data, sizeof(STresep));
    }
    
	myFile.close();
	
	return datas; 
}

vector<STresep> ambilDataResep(int id_penyakit)
{
	vector<STresep> datas = ambilDataResep();
	vector<STresep> found;
	
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].penyakit.id == id_penyakit)
			found.push_back(datas[i]);
	}
	
	return found;
}

vector<STcekup> ambilDataCekup()
{
	vector<STcekup> datas;
	STcekup data;
	
	ifstream myFile(FILE_CEKUP, ios::binary);
	
	if(!myFile)
    {
       return datas;
    }
     
	myFile.read((char*)&data, sizeof(STcekup));
    while(!myFile.eof())
    {
    	vector<STpenyakit> penyakit = ambilDataPenyakit(PENYAKIT_ID, int2string(data.penyakit.id));
    	vector<STpasien> pasien = ambilDataPasien(PASIEN_ID, int2string(data.pasien.id));

		if(penyakit.size() != 0 && pasien.size() != 0)
		{
			data.penyakit = penyakit[0];
			data.pasien = pasien[0];
			datas.push_back(data);	
		}
		
		myFile.read((char*)&data, sizeof(STcekup));
    }
    
	myFile.close();
	
	return datas; 
}

vector<STcekup> ambilDataCekup(int type, string keyword)
{
	vector<STcekup> datas = ambilDataCekup();
	vector<STcekup> found;
	
	if(type == CEKUP_ALL) return datas;
	
	for(int i = 0; i < datas.size(); i++)
	{
		switch(type)
		{
			case CEKUP_ID :
				if(int2string(datas[i].id).compare(keyword) == 0)
					found.push_back(datas[i]);
			break;
			
			case CEKUP_NAMA_PASIEN :
				if(tolower(string(datas[i].pasien.nama)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
			
			case CEKUP_NAMA_PENYAKIT :
				if(tolower(string(datas[i].penyakit.nama)).find(tolower(keyword)) != string::npos)
					found.push_back(datas[i]);
			break;
		}
	}
	
	return found;
}

vector<STcekup> ambilDataCekup(int id_pasien)
{
	vector<STcekup> datas = ambilDataCekup();
	vector<STcekup> found;
	
	for(int i = 0; i < datas.size(); i++)
	{
		if(datas[i].pasien.id == id_pasien)
			found.push_back(datas[i]);
	}
	
	return found;
}


/*--------------------------------- TAMBAH DATA KE FILE ------------------------------------*/

void tambahData(STpasien data)
{
	ofstream myFile(FILE_PASIEN, ios::binary | ios::app);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
    vector<STpasien> datas = ambilDataPasien();
    if(datas.size())
    {
		int lastID = datas[datas.size()-1].id;
		data.id = lastID+1;
	}
    else
    {
    	data.id = 1;	
	}
    
	myFile.write((char*)&data, sizeof(STpasien));
	
	myFile.close();
}

void tambahData(STpenyakit data)
{
	ofstream myFile(FILE_PENYAKIT, ios::binary | ios::app);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
    vector<STpenyakit> datas = ambilDataPenyakit();
    if(datas.size())
    {
		int lastID = datas[datas.size()-1].id;
		data.id = lastID+1;
	}
    else
    {
    	data.id = 1;	
	}
    
	myFile.write((char*)&data, sizeof(STpenyakit));
	
	myFile.close();
}

void tambahData(STobat data)
{
	ofstream myFile(FILE_OBAT, ios::binary | ios::app);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
    vector<STobat> datas = ambilDataObat();
    if(datas.size())
    {
		int lastID = datas[datas.size()-1].id;
		data.id = lastID+1;
	}
    else
    {
    	data.id = 1;	
	}
    
	myFile.write((char*)&data, sizeof(STobat));
	
	myFile.close();
}

void tambahData(STresep data)
{
	ofstream myFile(FILE_RESEP, ios::binary | ios::app);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
    vector<STresep> datas = ambilDataResep();
    if(datas.size())
    {
		int lastID = datas[datas.size()-1].id;
		data.id = lastID+1;
	}
    else
    {
    	data.id = 1;	
	}
    
	myFile.write((char*)&data, sizeof(STresep));
	
	myFile.close();
}

void tambahData(STcekup data)
{
	ofstream myFile(FILE_CEKUP, ios::binary | ios::app);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
    vector<STcekup> datas = ambilDataCekup();
    if(datas.size())
    {
		int lastID = datas[datas.size()-1].id;
		data.id = lastID+1;
	}
    else
    {
    	data.id = 1;	
	}
    
	myFile.write((char*)&data, sizeof(STcekup));
	
	myFile.close();
}


/*--------------------------------- REWRITE FILE ------------------------------------*/

void timpaFile(vector<STpasien> datas)
{
	ofstream myFile(FILE_PASIEN, ios::binary);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
	for(int i = 0; i < datas.size(); i++)
	{
		myFile.write((char*)&datas[i], sizeof(STpasien));
	}
	
	myFile.close();
}

void timpaFile(vector<STpenyakit> datas)
{
	ofstream myFile(FILE_PENYAKIT, ios::binary);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
	for(int i = 0; i < datas.size(); i++)
	{
		myFile.write((char*)&datas[i], sizeof(STpenyakit));
	}
	
	myFile.close();
}

void timpaFile(vector<STobat> datas)
{
	ofstream myFile(FILE_OBAT, ios::binary);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
	for(int i = 0; i < datas.size(); i++)
	{
		myFile.write((char*)&datas[i], sizeof(STobat));
	}
	
	myFile.close();
}

void timpaFile(vector<STresep> datas)
{
	ofstream myFile(FILE_RESEP, ios::binary);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
	for(int i = 0; i < datas.size(); i++)
	{
		myFile.write((char*)&datas[i], sizeof(STresep));
	}
	
	myFile.close();
}

void timpaFile(vector<STcekup> datas)
{
	ofstream myFile(FILE_CEKUP, ios::binary);
	
	if(!myFile)
    {
       cout << "Terjadi kesalahan pada file";
       getch();
       exit(1);
    }
    
	for(int i = 0; i < datas.size(); i++)
	{
		myFile.write((char*)&datas[i], sizeof(STcekup));
	}
	
	myFile.close();
}
