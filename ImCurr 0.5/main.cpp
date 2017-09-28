#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iterator>
#include <vector>
#include <cstdlib>
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
	void Encrypt(char sr[], char des[], char k[]); 
	void Decrypt(char sr[], char des[], char k[]); 
	void Pack(char sr[], char des[], char k[]);
	void Unpack(char sr[], char des[], char num[], char k[]);
	long toSkip = 0;
private:
	fstream imgW; 
	
};

char sizes[256][256] = { 0 };
char names[256][256] = { 0 };

void BasicFile::Decrypt(char sr[], char des[], char k[]) //decryption
{
	BasicKey key; //initialization for key, shuffling strings and segment parameters
	key.raw.clear();
	key.raw.resize(MX);
	key.toCheck.clear();
	key.toCheck.resize(MX);
	Translocation trs;
	Segment segm;
	int segment = 0; //segment size
	segm.buffer = 0; //setting zeros to prevent data mess
	segm.endpos = 0;
	key.fwd = strlen(k);
	imgW.open(sr); //opening file stream for file size detection
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	segm.size -= HASH;
	imgW.close();
	int ch;
	int it = 0;
	segm.toEdit = 1000;
	segment = 10;
	segm.segments = segm.toEdit / segment;
	int pointer = HASH;
	ifstream  src(sr, ios::binary); //new file streams for I/O
	ofstream  dst(des, ios::binary);
	
	char c;
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
	dst << src.rdbuf();	
	exit(0);
}

void BasicFile::Pack(char sr[], char des[], char k[])
{
	Translocation trs;
	int toEdit = 1000;
	int segment = 10;
	int segments = toEdit / segment;
	int shift = strlen(k);
	ifstream  src(sr, ios::binary); 
	ofstream  dst(des, ios::binary | ios::app);
	dst.seekp(0, ios::end);
	vector<char>toShuffle;
	toShuffle.resize(toEdit);
	char c;
	for (int i = 0; i < toEdit; i++)
	{
		src.get(c);
		toShuffle[i] = c;
	}
	trs.tmpA.resize(segment);
	trs.tmpB.resize(segment);
	int used = 0;
	int uSegments = 0;
	while (uSegments < segments) 
	{
		for (int i = 0; i < segment; i++)
		{
			trs.tmpA[i] = (char)(toShuffle[used + i] + shift);
		}
		uSegments++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			trs.tmpB[i] = (char)(toShuffle[used + i] + shift);
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
	dst.close();
	src.close();
}

void BasicFile::Unpack(char sr[], char des[], char size[], char k[])
{
	Translocation trs;
	int toEdit = 1000;
	int segment = 10;
	int segments = toEdit / segment;
	int shift = strlen(k);
	long sizel = atol(size);
	ifstream  src(sr, ios::binary);
	ofstream  dst(des, ios::binary | ios::trunc);
	src.seekg(sizel, ios::beg);
	vector<char>toShuffle;
	toShuffle.resize(toEdit);
	char c;
	for (int i = 0; i < toEdit; i++)
	{
		src.get(c);
		toShuffle[i] = c;
	}
	trs.tmpA.resize(segment);
	trs.tmpB.resize(segment);
	int used = 0;
	int uSegments = 0;
	while (uSegments < segments)
	{
		for (int i = 0; i < segment; i++)
		{
			trs.tmpA[i] = (char)(toShuffle[used + i] - shift);
		}
		uSegments++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			trs.tmpB[i] = (char)(toShuffle[used + i] - shift);
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
	dst.close();
	src.close();
	ifstream  eraserI(sr, ios::binary);
	vector<char>toSave;
	char e;
	for (long i = 0; i < sizel; i++)
	{
		eraserI.get(e);
		toSave.push_back(e);
	}
	eraserI.close();
	ofstream  eraserO(sr, ios::binary | ios::trunc);
	for (size_t i = 0; i < toSave.size(); i++)
	{
		eraserO << toSave[i];
	}
	eraserO.close();
}

void BasicFile::Encrypt(char sr[], char des[], char k[]) //encryption
{
	BasicKey key;
	key.raw.clear();
	key.raw.resize(MX);
	Translocation trs;
	Segment segm;
	int segment = 0; 
	int pointer = 0;
	bool amode = false;
	segm.buffer = 0;
	segm.endpos = 0;
	key.fwd = 0;
	imgW.open(sr);
	imgW.seekg(0, ios::end);
	segm.size = imgW.tellg();
	imgW.close();
	segm.toEdit = 1000;
	segment = 10;
	segm.segments = segm.toEdit / segment;
	ifstream  src(sr, ios::binary);
	ofstream  dst(des, ios::binary);
	char c;
	vector<char>toShuffle;
	toShuffle.resize(segm.toEdit);
	for (int i = 0; i < segm.toEdit; i++)
	{
		src.get(c);
		toShuffle[i] = c;
	}
	for (size_t i = 0; i < strlen(k); i++)
	{
		key.raw[i] = k[i];
	}
	key.raw.resize(strlen(k));
	key.hash = sha256(key.raw);
	for (int i = 0; i < key.hash.size(); i++)
	{
		dst << key.hash[i];
	}
	dst << '\0'; //send hash and '\0' char to divide the key part from the file part
	key.fwd = strlen(k);
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

int main(int argc, char *argv[])
{
	BasicFile file;
	char src[MMX];
	char dst[MMX];
	char pwd[MMX];
	
	if (argv[argc - 1][0] == '1')
	{
		strcpy(src, argv[argc - 4]);
		strcpy(dst, argv[argc - 3]);
		strcpy(pwd, argv[argc - 2]);
		cout << "Processing...\n";
		file.Encrypt(src, dst, pwd);
	}
	else if (argv[argc - 1][0] == '0')
	{
		strcpy(src, argv[argc - 4]);
		strcpy(dst, argv[argc - 3]);
		strcpy(pwd, argv[argc - 2]);
		cout << "Processing...\n";
		file.Decrypt(src, dst, pwd);
	}
	else if (argv[argc - 1][0] == '2')
	{
		int num = atoi(argv[argc - 2]);
		cout << "Processing...\n";
		for (int i = 3; i < num + 3; i++)
		{
			file.Pack(argv[argc - i], argv[1], argv[2]);
		}
		cout << "Done!\n";
	}
	else
	{
		char key[512] = { 0 };
		int num = atoi(argv[3]);
		strcpy(src, argv[1]);
		strcpy(key, argv[2]);
		for (int i = 4; i < 4 + (num * 2) - 1; i += 2)
		{
			strcpy(names[i - 4], argv[i]);
			strcpy(sizes[i - 4], argv[i + 1]);
		}
		cout << "Processing...\n";
		for (int i = 0; i < num * 2; i += 2)
		{
			file.Unpack(src, names[i], sizes[i], key);
		}
		cout << "Done!\n";
	}
	return 0;
}