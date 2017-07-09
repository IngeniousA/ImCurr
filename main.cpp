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
	int toEdit;
	int size;
	int buffer;
	int endpos;
};

struct Trloc
{
	int limit = MMX;
	string tmpA;
	string tmpB;
	string tmp;
	//vector<char>toShuffle;
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
	ifstream imgI; //Separated file streams for segmentation (inactive in 0.4)
	ofstream imgO; 
};

Image img;

/*
	TODO (0.4)
	1. Processing label - DONE
	2. Speed boost - DONE
	3. Odd segments
*/

void Image::scsnD() //decryption
{
	BasicKey key; //initialization for key, shuffling strings and segment parameters
	Trloc trs;
	Segment segm;
	bool amode = false; //automatic mode = false
	int segment = 0; //segment size
	segm.buffer = 0; //setting zeros to prevent data mosh
	segm.endpos = 0;
	imgW.open(fullpath); //opening file stream for file size detection
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
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
		}
		else if (isalnum(ch))
		{
			putchar('*');
			key.toCheck[it++] = (char)ch;
		}
	}
	imgI.open(fullpath, ios::binary); //getting hash
	imgI >> key.hash;
	key.hash.resize(64);
	imgI.close();
	if (sha256(key.toCheck) == key.hash) //if password is correct
	{
		key.raw = key.toCheck;
		key.fwd = key.raw.length() % SAFE_BORDER; //counting char shifting
		cout << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		cout << endl;
		cout << "Size of file: " << segm.size << endl;
		cout << "Enter size of part of file which was shuffled:\n";
		cin >> segm.toEdit;
		cout << "Enter segment size: \n";
		cin >> segment; //getting segment size, buffer, etc
		if (segment < segm.toEdit)
		{
			segm.buffer = segm.toEdit % segment;
			segm.endpos = segm.toEdit - segm.buffer;
		}
		else
		{
			segment = (segm.toEdit - 64) / 10;
			segm.buffer = segm.toEdit % 10;
			segm.endpos = segm.toEdit - segm.buffer;
		}		
		cout << "Enter destination file name: ";
		while (strlen(fullpathN) == 0) {
			cin.getline(fullpathN, LMX);
		}
		int pointer;
		amode ? pointer = 66 : pointer = 65;
		cout << "Prepairing to work...\n";
		ifstream  src(fullpath, ios::binary); //new file streams for I/O
		ofstream  dst(fullpathN, ios::binary);
		char c; //geting chars which were shuffled
		vector<char>toE2;
		toE2.resize(segm.toEdit);
		for (int i = 0; i < segm.toEdit; i++)
		{
			src.get(c);
			toE2[i] = c;
		}
		trs.tmpA.resize(segment);
		trs.tmpB.resize(segment);
		trs.tmp.resize(segm.buffer);
		int percentage = 0;
		while (pointer < segm.endpos) //shuffle them back
		{
			for (int i = pointer; i < pointer + segment; i++) //get segment A
			{
				trs.tmpA[i - pointer] = toE2[i] - key.fwd;
			}
			pointer += segment;
			for (int i = pointer; i < pointer + segment; i++) //get segment B 
			{
				trs.tmpB[i - pointer] = toE2[i] - key.fwd;
			}
			pointer += segment;
			for (int i = 0; i < trs.tmpB.size(); i++) //send segment B
			{
				dst << trs.tmpB[i];
			}
			for (int i = 0; i < trs.tmpA.size(); i++) //send segment A
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
		cout << "Incorrect key!" << endl;
		cout << "SHA-256 of entered string: \n/" + sha256(key.toCheck) + "/\n";
		cout << "SHA-256 of key: \n/" + key.hash + "/\n";
		imgI.close();
		imgO.close();
		scsnD();
	}
	exit(0);
}

void Image::scsnE() //encryption
{
	BasicKey key; //initialization for key, shuffling strings and segment parameters
	Trloc trs;
	Segment segm;
	int segment = 0; //setting default values
	int pointer = 0;
	char yn;
	bool amode = false;
	segm.buffer = 0;
	segm.endpos = 0;
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
	cout << "\nOriginal size of file: " << segm.size << endl;
	segm.toEdit = segm.size;
	if (!amode)
	{
		char charr[MX] = "\0";
		while ((charr[0] != 'y')&&(strlen(charr) != 1))
		{
			memset(charr, 0, sizeof(charr));
			cout << "Enter size of part of file to encrypt: \n";
			cin >> segm.toEdit; //get size of part of file which will be encrypted
			cout << "To shuffle: " << ((double)segm.toEdit / (double)segm.size)*100 << "% of file size \n";
			cout << "Enter y to continue" << "\n";
			cin >> charr;
		}	
		
		cout << "Enter segment size: \n>";
		cin >> segment;
		if (segment < segm.toEdit) //segment size less than the file size
		{
			segm.buffer = segm.toEdit % segment;
			segm.endpos = segm.toEdit - segm.buffer;
			if (((segm.toEdit - segm.buffer) % 2) == 1) //if the number of segments doesn't divide by 2, it recreates suitable values
			{
				segm.buffer += segment;
				segm.endpos = segm.toEdit - segm.buffer;
			}
		}
		else
		{
			segment = segm.toEdit / 10;
			segm.buffer = segm.toEdit % 10;
			segm.endpos = segm.toEdit - segm.buffer;
			if (((segm.toEdit - segm.buffer) % 2) == 1)
			{
				segm.buffer += segment;
				segm.endpos = segm.toEdit - segm.buffer;
			}
		}
	}
	else
	{
		segment = segm.size / 10;
		segm.buffer = segm.size % 10;
		segm.endpos = segm.size - segm.buffer;
		if ((segm.toEdit - segm.buffer) % 2)
		{
			segm.buffer += segment;
			segm.endpos = segm.toEdit - segm.buffer;
		}
	}
	ifstream  src(fullpath, ios::binary);
	ofstream  dst(fullpathN, ios::binary); 
	char c;
	vector<char>toE2;
	toE2.resize(segm.toEdit);
	for (int i = 0; i < segm.toEdit; i++)
	{
		src.get(c);
		toE2[i] = c;
	}
	dst << key.hash << '\0'; //send hash and '\0' char to divide the key part from the file part
	trs.tmpA.resize(segment);
	trs.tmpB.resize(segment);
	trs.tmp.resize(segm.buffer);
	while (pointer < segm.endpos)
	{
		for (int i = pointer; i < pointer + segment; i++)
		{
			trs.tmpA[i - pointer] = toE2[i] + key.fwd; //get segment A
		}
		pointer += segment;
		for (int i = pointer; i < pointer + segment; i++)
		{
			trs.tmpB[i - pointer] = toE2[i] + key.fwd; //get segment B
		}
		pointer += segment;
		for (int i = 0; i < trs.tmpB.size(); i++)
		{
			dst << trs.tmpB[i]; //send segment B
		}
		for (int i = 0; i < trs.tmpA.size(); i++)
		{
			dst << trs.tmpA[i]; //send segment A
		}
	}
	dst << src.rdbuf();
	src.close();
	dst.close();
	system("pause");
}

void Image::scsn() //menu
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

void Image::setp(char * path) //set path to file
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
	ImCurr 0.4.0a source code.
	Made by Sergey 'Ingenious' Rakhmanov, for free non-profit use.
	If you want to contact me, there are my credits:

	GitHub: IngeniousA
	VK: vk.com/1ngenious
	E-Mail: crashtranslator@yandex.ru
*/