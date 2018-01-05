#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <io.h>
#include <limits.h>
#include <iomanip>
#include "blowfish.h"
#define MMX 65536

using namespace std;
const unsigned long long MX = ULLONG_MAX; // <4.3 Gb is safe, >512 Mb is slow
char sizes[256][256] = { 0 };
char names[256][256] = { 0 };

typedef vector<char> strV;

vector<char*> nms;
vector<int> lngs;

void core(const char sr[], const char des[], const char k[], char mode)
{
 	ifstream src;
	ofstream dst;
	strV key;
	key.resize(0);
	for (int i = 0; i < strlen(k); i++)
		key.push_back(k[i]);
	strV srcV;
	Blowfish bf(key);
	src.open(sr, ios::binary);
	src.unsetf(std::ios::skipws);
	std::streampos fileSize;
	src.seekg(0, std::ios::end);
	fileSize = src.tellg();
	src.seekg(0, std::ios::beg);
		srcV.reserve(fileSize);
		srcV.insert(srcV.begin(),
			std::istream_iterator<char>(src),
			std::istream_iterator<char>());
		src.close();
		strV dstV;
		if (mode == '1' || mode == '2')
			dstV = bf.Encrypt(srcV);
		else if (mode == '0')
			dstV = bf.Decrypt(srcV);
		if (mode != '2')
			dst.open(des, ios::out | ios::binary);
		else
			dst.open(des, ios::app | ios::binary);
		for (int i = 0; i < dstV.size(); i++)
			dst.put(dstV[i]);
		if (mode == '2')
			lngs.push_back(dstV.size());
	dst.close();
}

void sendInfo(vector<int> lengths, vector<char*> names)
{
	ofstream data("coninfo.icsys", ios::binary | ios::trunc);
	data << lengths.size() << '\0';
	for (int i = 0; i < lengths.size(); i++)
		data << names[i] << '\0' << lengths[i] << '\0';
	data.close();
}

void unpack(char sr[], char des[], char size[], char k[], long skip)
{
	strV key;
	key.resize(0);
	for (int i = 0; i < strlen(k); i++)
		key.push_back(k[i]);
	long sizel = atol(size);
	ifstream  src(sr, ios::binary);
	ofstream  dst(des, ios::binary | ios::trunc);
	src.seekg(-(sizel + skip), ios::end);
	vector<char> text;
	text.resize(sizel);
	for (int i = 0; i < sizel; i++)
		text[i] = src.get();
	Blowfish bf(key);
	text = bf.Decrypt(text);
	for (int i = 0; i < text.size(); i++)
		dst.put(text[i]);
	dst.close();
	src.close();
}

void end()
{
	ofstream  ready("ready.icsys", ios::binary | ios::trunc);
	ready << '\0';
	ready.close();
}

int main(int argc, char *argv[])
{
	unsigned long skip = 0;
	if (argv[argc - 1][0] == '1' || argv[argc - 1][0] == '0')
	{
		cout << "Processing...\n";
		core(argv[1], argv[2], argv[3], argv[argc - 1][0]);
	}
	else if (argv[argc - 1][0] == '2')
	{
		int num = atoi(argv[argc - 2]);
		cout << "Processing...\n";
		nms.resize(num);
		for (int i = 3; i < num + 3; i++)
		{
			core(argv[argc - i], argv[1], argv[2], '2');
			nms[i - 3] = argv[argc - i];
		}
		sendInfo(lngs, nms);
	}
	else if (argv[argc - 1][0] == '3')
	{
		char key[512] = { 0 };
		int num = atoi(argv[3]);
		strcpy(argv[1], argv[1]);
		strcpy(key, argv[2]);
		for (int i = 4; i < 4 + (num * 2) - 1; i += 2)
		{
			strcpy(names[i - 4], argv[i]);
			strcpy(sizes[i - 4], argv[i + 1]);
		}
		for (int i = 0; i < num * 2; i += 2)
		{
			unpack(argv[1], names[i], sizes[i], key, skip);
			skip += atol(sizes[i]);
			system("cls");
			cout << "Processing: " << fixed << setprecision(2) << ((double)i / 2) / double(num) * 100 << "%";
		}
	}
	else
	{
		cout << "Launched not by IC6, leaving...";
		return 0;
	}
	end();
	cout << "Done!\n";
	return 0;
}