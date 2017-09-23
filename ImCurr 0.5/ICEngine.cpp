#define _CRT_SECURE_NO_WARNINGS
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
	void scsnE(char sr[], char des[], char k[]); //SCSN - encryption
	void scsnD(char sr[], char des[], char k[]); //SCSN - decryption

private:
	char fullpath[MX]; //Input path
	char fullpathN[MX]; //Output path
	fstream imgW; //Size detection
	ifstream imgI; //Separated file streams for segmentation (inactive in 0.4)
	ofstream imgO;
};

vector<BasicFile> ImQ;

void BasicFile::scsnD(char sr[], char des[], char k[]) //decryption
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

void BasicFile::scsnE(char sr[], char des[], char k[]) //encryption
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
	strcpy(src, argv[argc - 4]);
	strcpy(dst, argv[argc - 3]);
	strcpy(pwd, argv[argc - 2]);
	if (argv[4][0] == '1')
	{
		file.scsnE(src, dst, pwd);
	}
	else
	{
		file.scsnD(src, dst, pwd);
	}
	return 0;
}