#ifndef Hstruct
#define Hstruct

#define C_PASIEN 1
#define C_PENYAKIT 2
#define C_OBAT 3
#define C_RESEP 4
#define C_CEKUP 5

#define FILE_PASIEN 	"database/pasien.txt"
#define FILE_PENYAKIT 	"database/penyakit.txt"
#define FILE_OBAT		"database/obat.txt"
#define FILE_RESEP		"database/resep.txt"
#define FILE_CEKUP		"database/cekup.txt"

typedef struct
{
	int id, umur;
	char nama[20], alamat[30];
	char kelamin;
} STpasien;

typedef struct
{
	int id;
	char nama[20], jenis;
} STpenyakit;

typedef struct
{
	int id, umur, harga;
	char nama[20];
} STobat;

typedef struct
{
	int id, dosis;
	STobat obat;
	STpenyakit penyakit;
} STresep;

typedef struct
{
	int dd, mm, yy;
} STtanggal;

typedef struct
{
	int id;
	STpasien pasien;
	STpenyakit penyakit;
	STtanggal tanggal;
} STcekup;

/*--------------- Untuk Pencarian --------------*/
typedef enum
{
	TIPE_TEXT,
	TIPE_CHAR,
	TIPE_ALNUM,
	TIPE_ALPHA,
	TIPE_NUMBER
} TipeInputan;

typedef enum
{
	PASIEN_ALL,
	PASIEN_ID,
	PASIEN_UMUR,
	PASIEN_NAMA,
	PASIEN_ALAMAT,
	PASIEN_KELAMIN
} SearchPasien;

typedef enum
{
	PENYAKIT_ALL,
	PENYAKIT_ID,
	PENYAKIT_NAMA,
	PENYAKIT_JENIS
} SearchPenyakit;

typedef enum
{
	OBAT_ALL,
	OBAT_ID,
	OBAT_UMUR,
	OBAT_HARGA,
	OBAT_NAMA
} SearchObat;

typedef enum
{
	CEKUP_ALL,
	CEKUP_ID,
	CEKUP_NAMA_PASIEN,
	CEKUP_NAMA_PENYAKIT
} SearchCekup;

#endif
