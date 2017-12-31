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
const unsigned long MX = ULONG_MAX; // <4.3 Gb is safe, >512 Mb is slow
char sizes[256][256] = { 0 };
char names[256][256] = { 0 };

typedef vector<char> strV;

void core(const char sr[], const char des[], const char k[], bool isEncrypt)
{
 	ifstream src;
	ofstream dst;
	strV key;
	key.resize(0);
	for (int i = 0; i < strlen(k); i++)
	{
		key.push_back(k[i]);
	}
	strV srcV;
	Blowfish bf(key);
	src.open(sr, ios::binary);
	src.unsetf(std::ios::skipws);
	std::streampos fileSize;
	src.seekg(0, std::ios::end);
	fileSize = src.tellg();
	src.seekg(0, std::ios::beg);
	if (fileSize > MX)
	{
		char ch;
		srcV.resize(MX);
		for (long i = 0; i < MX; i++)
			srcV[i] = src.get();
		strV dstV;
		if (isEncrypt)
			dstV = bf.Encrypt(srcV);
		else
			dstV = bf.Decrypt(srcV);
		dst.open(des, ios::out | ios::binary);
		for (int i = 0; i < dstV.size(); i++)
			dst.put(dstV[i]);
		dst << src.rdbuf();
		src.close();
	}
	else
	{
		srcV.reserve(fileSize);
		srcV.insert(srcV.begin(),
			std::istream_iterator<char>(src),
			std::istream_iterator<char>());
		src.close();
		strV dstV;
		if (isEncrypt)
			dstV = bf.Encrypt(srcV);
		else
			dstV = bf.Decrypt(srcV);
		dst.open(des, ios::out | ios::binary);
		for (int i = 0; i < dstV.size(); i++)
			dst.put(dstV[i]);
	}
	dst.close();
}

void end()
{
	ofstream  ready("ready.icsys", ios::binary | ios::trunc);
	ready << '\0';
	ready.close();
}

int main(int argc, char *argv[])
{
	char src[MMX];
	char dst[MMX];
	char pwd[MMX];
	if (argv[argc - 1][0] == '1')
	{
		strcpy(src, argv[1]);
		strcpy(dst, argv[2]);
		strcpy(pwd, argv[3]);
		cout << "Processing...\n";
		core(src, dst, pwd, 1);
	}
	else if (argv[argc - 1][0] == '0')
	{
		strcpy(src, argv[1]);
		strcpy(dst, argv[2]);
		strcpy(pwd, argv[3]);
		cout << "Processing...\n";
		core(src, dst, pwd, 0);
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