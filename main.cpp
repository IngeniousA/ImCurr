#define _CRT_SECURE_NO_WARNINGS
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
#include <io.h>
#include "sha256.h"

#define SMX 16
#define MX 256
#define MMX 65535
#define LMX 1500000
#define FIRST_SYM 33
#define HIDELIM 255
#define SAFE_BORDER 256
#define HASH 65

using namespace std;

char inputch[MX];
int qIndex = 0;

struct BasicKey
{
	int size = 64;
	char fwd = 0;
	const int startpos = size + 1;
	string raw;
	string toCheck;
	string hash;
};

struct Segment
{
	int toEdit;
	long int size;
	int buffer;
	int endpos;
	int segments;
};

struct Translocation
{
	int limit = MMX;
	string tmpA;
	string tmpB;
};

class BasicFile
{
public:
	void setp(char * path); //set path
	void additional();
	void scsn();
	void scsnE(); //SCSN - encryption
	void scsnD(); //SCSN - decryption
	void hide(); //hide a message
	void get(); //get a message

private:
	char fullpath[MX]; //Input path
	char fullpathN[MX]; //Output path
	fstream imgW; //Size detection
	ifstream imgI; //Separated file streams for segmentation (inactive in 0.4)
	ofstream imgO; 
};

vector<BasicFile> ImQ;

void BasicFile::scsnD() //decryption
{
	BasicKey key; //initialization for key, shuffling strings and segment parameters
	key.raw.clear();
	key.raw.resize(MX);
	key.toCheck.clear();
	key.toCheck.resize(MX);
	Translocation trs;
	Segment segm;
	bool amode = false; //automatic mode = false
	int segment = 0; //segment size
	segm.buffer = 0; //setting zeros to prevent data mess
	segm.endpos = 0;
	key.fwd = 0;
	imgW.open(fullpath); //opening file stream for file size detection
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	segm.size -= HASH;
	imgW.close();
	cout << "Enter private key: \n"; //implementation for input mask
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
			key.fwd--; //counting char shifting
		}
		else if (isalnum(ch))
		{
			putchar('*');
			key.toCheck[it++] = (char)ch;
			key.fwd++; //counting char shifting
		}
	}
	key.toCheck.resize(it);
	key.hash.resize(64);	
	imgI.open(fullpath, ios::in); //getting hash
	for (size_t i = 0; i < 64; i++)
	{
		imgI.get(key.hash[i]);
	}
	imgI.close();
	if (sha256(key.toCheck) == key.hash) //if password is correct
	{		
		cout << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		cout << endl;
		if (segm.size <= 5000) //automatic is now default
		{
			segm.toEdit = segm.size;
			segment = 10;
			segm.segments = segm.toEdit / segment;
			if ((segm.segments % 2) == 1)
			{
				segm.segments--;
				segm.toEdit -= segment;
			}
		}
		else
		{
			segm.toEdit = 1000;
			segment = 10;
			segm.segments = segm.toEdit / segment;
		}
		cout << "Enter destination file name: ";
		while (strlen(fullpathN) == 0) {
			cin.getline(fullpathN, LMX);
		}
		int pointer = HASH;
		ifstream  src(fullpath, ios::binary); //new file streams for I/O
		ofstream  dst(fullpathN, ios::binary);

		char c; //geting chars which were shuffled
		vector<char>toShuffle;
		toShuffle.resize(segm.toEdit);
		src.seekg(pointer, ios::beg);
		for (int i = 0; i < segm.toEdit; i++)
		{
			src.get(c);
			toShuffle[i] = c;
		}
		
		trs.tmpA.resize(segment);
		trs.tmpB.resize(segment);
		int used = 0;
		int uSegments = 0;

		while (uSegments < segm.segments) //SHUFFLE PROCESS
		{
			for (int i = 0; i < segment; i++)
			{
				trs.tmpA[i] = (char)(toShuffle[used + i] - key.fwd);
			}
			uSegments++;
			used += segment;
			for (int i = 0; i < segment; i++)
			{
				trs.tmpB[i] = (char)(toShuffle[used + i] - key.fwd);
			}
			uSegments++;
			used += segment;
			for (int i = 0; i < segment; i++)
			{
				dst << trs.tmpB[i];
			}
			for (int i = 0; i < segment; i++)
			{
				dst << trs.tmpA[i];
			}
		}

		dst << src.rdbuf(); //other information is just copied to destionation file
		cout << endl;
		src.close();
		dst.close();
	}
	else //incorrect password
	{
		cout << "\nIncorrect key!" << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		imgI.close();
		imgO.close();
		scsnD();
	}
	exit(0);
}

void BasicFile::hide()
{
	char num = '!';
	char msg[MMX] = { 0 };
	system("cls");
	imgW.open(fullpath, ios::app);
	cout << "Message: ";
	while (strlen(msg) == 0)
	{
		cin.getline(msg, MMX);
	}
	num += strlen(msg);
	imgW << msg << num;
	imgW.close();
}

void BasicFile::get()
{
	bool st = true;
	char msg[MMX] = { 0 };
	char getn = '\0';
	memset(msg, 0, sizeof(msg));
	system("cls");
	cout << "Message ressurection mode" << endl;
	imgW.open(fullpath);
	imgW.seekg(-1, imgW.end);
	imgW >> getn;
	if ((getn > FIRST_SYM) && (getn < (FIRST_SYM + HIDELIM))) {
		int delta = abs(getn - (FIRST_SYM - 1));
		imgW.seekg(-delta, imgW.cur);
		imgW.getline(msg, getn - FIRST_SYM + 1);
		if (strlen(msg) > 0)
		{
			cout << "Hidden message: " << msg << endl;
			system("pause");
		}
		else 
		{
			cout << "Failed to find a message, probably the file doesn't exist \n or the name given is wrong." << endl;
			system("pause");
		}
	}
	else
	{
		cout << "Failed to find a message, probably the file doesn't exist \n or the name given is wrong." << endl;
		system("pause");
	}
	imgW.close();
	scsn();
}

void BasicFile::scsnE() //encryption
{
	BasicKey key; //initialization for key, shuffling strings and segment parameters
	key.raw.clear();
	key.raw.resize(MX);
	Translocation trs;
	Segment segm;
	int segment = 0; //setting default values
	int pointer = 0;
	bool amode = false;
	segm.buffer = 0;
	segm.endpos = 0;
	key.fwd = 0;
	imgW.open(fullpath); //size detection
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	imgW.close();
	cout << "Enter output file name: \n>";
	while (strlen(fullpathN) == 0)
	{
		cin.getline(fullpathN, LMX);
	}
	strcat(fullpathN, ".scsn");
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
			key.fwd--;
			key.raw[it] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			key.raw[it++] = (char)ch;
			key.fwd++;
		}
	}	
	key.raw.resize(it);
	key.hash = sha256(key.raw);
	if (segm.size <= 5000) //automatic is now default
	{
		segm.toEdit = segm.size;
		segment = 10;
		segm.segments = segm.toEdit / segment;
		if ((segm.segments % 2) == 1)
		{
			segm.segments--;
			segm.toEdit -= segment;
		}
	}
	else
	{
		segm.toEdit = 1000;
		segment = 10;
		segm.segments = segm.toEdit / segment;
	}	
	ifstream  src(fullpath, ios::binary);
	ofstream  dst(fullpathN, ios::binary); 

	char c;
	vector<char>toShuffle;
	toShuffle.resize(segm.toEdit);
	for (int i = 0; i < segm.toEdit; i++)
	{
		src.get(c);
		toShuffle[i] = c;
	}

	dst << key.hash << '\0'; //send hash and '\0' char to divide the key part from the file part
	
	trs.tmpA.resize(segment);
	trs.tmpB.resize(segment);
	int used = 0;
	int uSegments = 0; 
	while (uSegments < segm.segments) //SHUFFLE PROCESS
	{
		for (int i = 0; i < segment; i++)
		{
			trs.tmpA[i] = (char)(toShuffle[used + i] + key.fwd);
		}
		uSegments++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			trs.tmpB[i] = (char)(toShuffle[used + i] + key.fwd); 
		}
		uSegments++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			dst << trs.tmpB[i];
		}
		for (int i = 0; i < segment; i++)
		{
			dst << trs.tmpA[i];
		}
	}
	dst << src.rdbuf();
	src.close();
	dst.close();
}

void BasicFile::scsn() //menu
{
	system("cls");
	cout << "1 - Encrypt a file" << endl
		<< "2 - Decrypt a file" << endl
		<< "3 - Other" << endl
		<< "4 - Exit" << endl;
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
		additional();
		exit(0);
		break;
	case '4':
		break;
	default:
		cout << "Incorrect input!" << endl;
		scsn();
		break;
	}
}

inline bool fileOK(const char * name) 
{
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

void BasicFile::setp(char * path) //set path to file
{
	if (fileOK(path))
	{
		strcpy(fullpath, path);
	}
	else
	{
		cout << "Incorrect path!\n";
		system("pause");
		exit(0);
		return;
	}
}

void BasicFile::additional()
{
	system("cls");
	cout << "1 - Hide a message" << endl
		<< "2 - Get a message" << endl
		<< "3 - Back" << endl;
	char ch;
	cin >> ch;
	cin.clear();
	switch (ch) {
	case '1':
		hide();
		break;
	case '2':
		get();
		break;
	case '3':
		scsn();
	default:
		cout << "Incorrect input!" << endl;
		additional();
		break;
	}
}

int main()
{
	memset(inputch, 0, sizeof(inputch));
	short int ch = 0;
	int qSize = 0;
	cout << "Name (1 to exit) \n>";
	while (strlen(inputch) == 0)
	{
		cin.getline(inputch, LMX);		
	}
	if ((inputch[0] == '1') && (strlen(inputch) == 1))
	{
		exit(0);
	}
	else if ((inputch[0] == 'Q') && (strlen(inputch) == 1))
	{
		cout << "Enter the size of queue: ";
		cin >> qSize;
		ImQ.resize(qSize);
	}
	else
	{
		qIndex = 0;
		ImQ.resize(1);
		ImQ[0].setp(inputch);
		ImQ[0].scsn();
	}
	return 0;
}

/*
	ImCurr 0.4.1.1 source code.
	Made by Sergey 'Ingenious' Rakhmanov, for free non-profit use.
	If you want to contact me, there are my credits:

	GitHub: IngeniousA
	VK: vk.com/1ngenious
	E-Mail: IngeniousA@yandex.ru
*/