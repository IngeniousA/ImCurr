#define _CRT_SECURE_NO_WARNINGS
#define _D_SCL_SECURE_NO_WARNINGS
#define _ITERATOR_DEBUG_LEVEL 0 

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iterator>
#include <vector>
#include <clocale>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "sha256.h"
//#include "msglib.h"

#define SMX 16
#define MX 256
#define MMX 65535
#define LMX 1500000
#define FIRST_SYM 33
#define HIDELIM 89
#define SAFE_BORDER 20

char inputch[MX];
using namespace std;

struct BasicKey
{
	int size = 64;
	int fwd = 0;
	const int startpos = 65;
	string raw;
	string toCheck;
	string hash;
};

struct Segment
{
	int size;
	int buffer;
	int endpos;
};

struct Trloc
{
	int limit = MMX;
	vector<char> tmpA;
	vector<char> tmpB;
	vector<char> tmp;
};

class Image
{
public:
	void setp(char * path); //set path
	void scsn(); //Subconsciuousness menu
	void scsnE(); //SCSN - encryption
	void scsnD(); //SCSN - decryption

private:
	char fullpath[MX]; //Input path
	char fullpathN[MX]; //Output path
	fstream imgW; //Size detection
	ifstream imgI; //Separated file streams for segmentation
	ofstream imgO; 
};

Image img;

void Image::scsnD()
{
	BasicKey key;
	Trloc trs;
	Segment segm;
	bool amode = false;
	int segment = 0;
	char autochk;
	segm.buffer = 0;
	segm.endpos = 0;
	imgW.open(fullpath);
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	imgW.close();
	cout << "Enter private key: \n";
	fflush(stdout);
	int ch;
	int it = 0;
	while ((ch = _getch()) != EOF
		&& ch != '\n'
		&& ch != '\r'
		&& it < sizeof(key.toCheck) - 1)
	{
		if (ch == '\b' && it > 0)
		{
			printf("\b \b");
			fflush(stdout);
			it--;
			key.toCheck[it] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			key.toCheck[it++] = (char)ch;
		}
	}
	imgI.open(fullpath, ios::binary);
	imgI >> autochk;
	key.hash.resize(64);
	if (autochk == 'A')
	{
		amode = true;
		imgI >> key.hash;
		key.hash.resize(64);
	}
	else
	{
		amode = false;
		imgI >> key.hash;
		key.hash = autochk + key.hash;
		key.hash.resize(64);
	}
	imgI.close();
	if (sha256(key.toCheck) == key.hash)
	{
		key.raw = key.toCheck;
		key.fwd = key.raw.length() % SAFE_BORDER;
		cout << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		cout << endl;
		if (!amode)
		{
			cout << "Size of file: " << segm.size << endl;
			cout << "Enter segment size: \n>";
			cin >> segment;
			if (segment < segm.size)
			{
				segm.buffer = segm.size % segment;
				segm.endpos = segm.size - segm.buffer;
			}
			else
			{
				segment = (segm.size - 64) / 10;
				segm.buffer = segm.size % 10;
				segm.endpos = segm.size - segm.buffer;
			}
		}
		else
		{
			segment = (segm.size - 66) / 10;
			segm.buffer = segm.size % 10;
			segm.endpos = segm.size - segm.buffer;
		}
		cout << "Enter destination file name: ";
		while (strlen(fullpathN) == 0) {
			cin.getline(fullpathN, LMX);
		}
		imgI.open(fullpath, ios::binary);
		imgI.seekg(0, imgW.beg);
		imgO.open(fullpathN, ios::trunc | ios::binary);
		int pointer;
		amode ? pointer = 66 : pointer = 65;
		vector<char> fulldata((
			std::istreambuf_iterator<char>(imgI)),
			(std::istreambuf_iterator<char>()));
		trs.tmpA.resize(segment);
		trs.tmpB.resize(segment);
		trs.tmp.resize(segm.buffer);
		while (pointer < segm.endpos)
		{
			for (int i = pointer; i < pointer + segment; i++)
			{
				trs.tmpA[i - pointer] = fulldata[i] - key.fwd;
			}
			pointer += segment;
			for (int i = pointer; i < pointer + segment; i++)
			{
				trs.tmpB[i - pointer] = fulldata[i] - key.fwd;
			}
			pointer += segment;
			for (int i = 0; i < trs.tmpB.size(); i++)
			{
				imgO << trs.tmpB[i];
			}
			for (int i = 0; i < trs.tmpA.size(); i++)
			{
				imgO << trs.tmpA[i];
			}
		}
		for (int i = segm.endpos; i < segm.size; i++)
		{
			trs.tmp[i - segm.endpos] = fulldata[i] - key.fwd;
		}
		for (int i = 0; i < trs.tmp.size(); i++)
		{
			imgO << trs.tmp[i];
		}
		cout << endl;
		imgI.close();
		imgO.close();
	}
	else
	{
		cout << "Incorrect key!" << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		imgI.close();
		imgO.close();
		//system("cls");
		scsnD();
	}
	exit(0);
}

void Image::scsnE()
{
	BasicKey key;
	Trloc trs;
	Segment segm;
	int segment = 0;
	int pointer = 0;
	char yn;
	bool amode = false;
	segm.buffer = 0;
	segm.endpos = 0;
	imgW.open(fullpath);
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	imgW.close();
	cout << "Turn auto mode on? (1 - Yes, 0 - No) \n>";
	cin >> yn;
	cin.clear();
	yn == '1' ? amode = true : amode = false;
	
	cout << "Enter output file name: \n>";
	while (strlen(fullpathN) == 0)
	{
		cin.getline(fullpathN, LMX);
	}

	cout << "Enter private key: \n>";
	fflush(stdout);
	int ch;
	int it = 0;
	while ((ch = _getch()) != EOF
		&& ch != '\n'
		&& ch != '\r'
		&& it < sizeof(key.raw) - 1)
	{
		if (ch == '\b' && it > 0)
		{
			printf("\b \b");
			fflush(stdout);
			it--;
			key.raw[it] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			key.raw[it++] = (char)ch;
		}
	}	
	key.fwd = key.raw.length() % SAFE_BORDER;
	key.hash = sha256(key.raw);
	
	cout << "Size of file: " << segm.size << endl;
	if (!amode)
	{
		cout << "Enter segment size: \n>";
		cin >> segment;
		if (segment < segm.size)
		{
			segm.buffer = segm.size % segment;
			segm.endpos = segm.size - segm.buffer;
		}
		else
		{
			segment = segm.size / 10;
			segm.buffer = segm.size % 10;
			segm.endpos = segm.size - segm.buffer;
		}
	}
	else
	{
		segment = segm.size / 10;
		segm.buffer = segm.size % 10;
		segm.endpos = segm.size - segm.buffer;
	}

	strcat(fullpathN, ".scsn");
	cout << "Destination file name: " << fullpathN << endl;
	
	imgO.open(fullpathN, ios::trunc | ios::binary);
	imgI.open(fullpath, ios::binary);
	imgI.seekg(0, imgW.beg);
	if (amode)
	{
		imgO << 'A';
	}
	imgO << key.hash << '\0';
	cout << endl;
	vector<char> fulldata((
		std::istreambuf_iterator<char>(imgI)),
		(std::istreambuf_iterator<char>()));
	trs.tmpA.resize(segment);
	trs.tmpB.resize(segment);
	trs.tmp.resize(segm.buffer);
	while (pointer < segm.endpos)
	{
		for (int i = pointer; i < pointer + segment; i++)
		{
			trs.tmpA[i - pointer] = fulldata[i] + key.fwd;
		}
		pointer += segment;
		for (int i = pointer; i < pointer + segment; i++)
		{
			trs.tmpB[i - pointer] = fulldata[i] + key.fwd;
		}
		pointer += segment;
		for (int i = 0; i < trs.tmpB.size(); i++)
		{
			imgO << trs.tmpB[i];
		}
		for (int i = 0; i < trs.tmpA.size(); i++)
		{
			imgO << trs.tmpA[i];
		}
	}
	for (int i = segm.endpos; i < segm.size; i++)
	{
		trs.tmp[i - segm.endpos] = fulldata[i] + key.fwd;
	}
	for (int i = 0; i < trs.tmp.size(); i++)
	{
		imgO << trs.tmp[i];
	}
	cout << endl;
	imgI.close();
	imgO.close();
}

void Image::scsn()
{
	system("cls");
	cout << "1 - Encrypt a file" << endl 
		 << "2 - Decrypt a file" << endl 
		 << "3 - Exit" << endl;
	char ch;
	cin >> ch;
	cin.clear();
	switch (ch) {
	case '1':
		scsnE();
		break;
	case '2':
		scsnD();
		break;
	case '3':
		exit(0);
		break;
	default:
		cout << "Incorrect input!" << endl;
		scsn();
		break;
	}
}

void Image::setp(char * path)
{
	strcpy(fullpath, path);
}

int main()
{
	memset(inputch, 0, sizeof(inputch));
	short int ch = 0;
	cout << "Name (1 to exit) \n>";
	while (strlen(inputch) == 0) {
		cin.getline(inputch, LMX);
	}
	if ((inputch[0] == '1') && (strlen(inputch) == 1)) {
		exit(0);
	}
	else {
		img.setp(inputch);
	}
	img.scsn();
	return 0;
}

/*
	ImCurr 0.3.1 source code.
	Made by Sergey 'Ingenious' Rakhmanov, for free non-profit use.
	If you want to contact me, there are my credits:

	GitHub: IngeniousA
	VK: vk.com/1ngenious
	E-Mail: crashtranslator@yandex.ru
*/