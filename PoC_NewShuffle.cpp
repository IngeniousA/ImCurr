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

using namespace std;

int main()
{
	ifstream  src("INPUT.zip", ios::binary);
	ofstream  dst("OPUTPUT.zip", ios::binary); 
	vector<char>toE2;
	vector<char>A;
	vector<char>B;
	toE2.resize(1000);   //TO EDIT
	char c;
	for (int i = 0; i < 1000; i++)
	{
		src.get(c);
		toE2[i] = c;
	}
	int segment = 20; //SIZE OF SEGMENT
	int segments = 1000 / segment; //AMOUNT OF SEGMENTS
	int used = 0; //USED BYTES
	int k = 0; //USED SEGMENTS
	A.resize(segment);
	B.resize(segment);
	while (k < segments) //SHUFFLE PROCESS
	{
		for (int i = 0; i < segment; i++)
		{
			A[i] = toE2[used + i];
		}
		k++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			B[i] = toE2[used + i];
		}
		k++;
		used += segment;
		for (int i = 0; i < segment; i++)
		{
			dst << B[i];
		}
		for (int i = 0; i < segment; i++)
		{
			dst << A[i];
		}
	}
	dst << src.rdbuf(); //OTHER PART OF FILE
	src.close();
	dst.close();
	return 0;
}
