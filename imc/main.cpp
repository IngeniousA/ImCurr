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
#define SMX 16
#define MX 256
#define MMX 65535
#define LMX 1500000
#define FIRST_SYM 33
#define HIDELIM 89
#define INCINP cout << "---------------------" << endl;\
			   cout << "---Incorrect input---" << endl;\
			   cout << "---------------------" << endl;
#define SUCCESS cout << endl;\
				cout << "-------SUCCESS-------" << endl;
#define FAILURE cout << endl;\
				cout << "-------FAILURE-------" << endl;
#define INPVIOLATION cout << "Input string had an unacceptable symbol(s). Please, try again" << endl; cout << endl;

using namespace std;

void sw(int st);
void Credits();
char inputch[MX];
bool inp = true;

//CREATE A STRING CHECKING FUNCTION TO REMOVE ISSUES

class Image
{
public:
	Image();
	void setp(char * path); //set path
	void Corrupt(); //hide a message
	void GetMSG(); //get a message
	void Shuffle(); //Merged corruption and ressurection into one function
	void RecogN(); //UPD: Advanced ASCII symbols recognition
	void Unable(); //UPD: Inability to get a message
	void Party();
	~Image(); 

private:
	//local strings
	char fullpath[MX];
	char fullpathN[MX];
	char msg[MX];
	char num = '!';
	char getn;
	//corrupting data
	int segment = 0;
	//file streams
	fstream imgW;
	ifstream imgI; //UPD: Separated file streams for segmentation
	ofstream imgO;
	vector<char> tmpA;
	vector<char> tmpB;
	vector<char> tmp;
};

Image img;

void menu() {
	memset(inputch, 0, sizeof(inputch));
	short int ch = 0;
	cout << "Enter the full name of image to work with (1 to exit) \n>";
	while (strlen(inputch) == 0) {
		cin.getline(inputch, LMX);
	}
	if ((inputch[0] == '1') && (strlen(inputch) == 1)) {
		exit(0);
	}
	else {
		img.setp(inputch);
	}
	cout << "Please, choose an option:" << endl;
	cout << "1 - Hide a message in an image" << endl;
	cout << "2 - Get a message from an image" << endl;
	cout << "3 - Corrupt/Ressurect an image" << endl;
	cout << "4 - Advanced ASCII search" << endl;
	cout << "5 - Make a glitch party!" << endl;
	cout << "6 - Credits" << endl;
	cout << "7 - Exit" << endl;
	cout << ">";
	cin.clear();
	cin >> ch;
	sw(ch);
}

void sw(int st) {
	if ((st > 6) || (st < 0)) {
		INCINP;
		menu();
	}
	else {
		switch (st)
		{
		case 1:
			img.Corrupt();
			break;
		case 2:
			img.GetMSG();
			break;
		case 3:
			img.Shuffle();
			break;
		case 4:
			img.RecogN();
			break;
		case 5:
			img.Party();
			break;
		case 6:
			Credits();
			break;
		case 7:
			exit(0);
			break;
		default:
			INCINP;
			memset(inputch, 0, sizeof(inputch));
			menu();
			break;
		}
	}
}

void Credits() {
	system("cls");
	cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
	cout << "+                                 +" << endl;
	cout << "=        ImCurr v0.2.1a           =" << endl;
	cout << "+                                 +" << endl;
	cout << "=             Made by             =" << endl;
	cout << "+   Sergey 'Ingenious' Rakhmanov  +" << endl;
	cout << "=        vk.com/1ngenious         =" << endl;
	cout << "+                                 +" << endl;
	cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
	menu();
}

void Salutation() {
	setlocale(LC_ALL, "Russian");
	cout << "===========================" << endl;
	cout << "=====Welcome to ImCurr=====" << endl;
	cout << "===========================" << endl;
	menu();
}

bool msgchk(char raw[MX]) {
	for (int i = 0; i < strlen(raw); i++)
	{
		if (__isascii(raw[i])) {
			if ((!isalpha(raw[i]))&&(!isdigit(raw[i]))) {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

Image::Image()
{
	
}

void Image::setp(char * path)
{
	strcpy(fullpath, path);
}

void Image::Corrupt()
{
	num = '!';
	memset(msg, 0, sizeof(msg));
	system("cls");
	if (inp) {
		cout << "Message encryption mode" << endl;
		imgW.open(fullpath, ios::app);
		cout << "Message: ";		
		while(strlen(msg) == 0) {
			cin.getline(msg, LMX);
		}
		if (strlen(msg) >= 89) {
			msg[89] = '\0';
		}
	}
	else {
		FAILURE
		cout << endl;
		INPVIOLATION;
		imgW.open(fullpath, ios::app);
		cout << "Message: ";
		while (strlen(msg) == 0) {
			cin.getline(msg, LMX);
		}
		if (strlen(msg) >= 89) {
			msg[89] = '\0';
		}
		inp = true;
	}
 	if (msgchk(msg)) {
		num += strlen(msg);
		imgW << msg << num;
		SUCCESS
		cout << endl;
		cout << "---------------------" << endl;
		cout << "Filename: " << fullpath << ", message: " << msg << endl;
		cout << "---------------------" << endl;
		cout << endl;
		imgW.close();
		menu(); 
	}
	else {
		inp = false;
		memset(msg, 0, sizeof(msg));
		imgW.close();
		Corrupt();
	}
} 

void Image::GetMSG()
{
	bool st = true;
	memset(msg, 0, sizeof(msg));
	system("cls");	
	cout << "Message ressurection mode" << endl;
	imgW.open(fullpath);
	imgW.seekg(-1, imgW.end);
	imgW >> getn;
	//cout << "Filename: " << fullpath << ", lng: " << imgW.tellg() << ", sym: " << getn << endl; <- Debug time!
	if ((getn > FIRST_SYM) && (getn < (FIRST_SYM + HIDELIM))) {
		int delta = abs(getn - (FIRST_SYM - 1));
		imgW.seekg(-delta, imgW.cur);
		imgW.getline(msg, getn - FIRST_SYM + 1);
		if (strlen(msg) > 0)
		{
			for (int i = 0; i < strlen(msg); i++)
			{
				if (__isascii(msg[i])) {
					if ((!isalpha(msg[i])) && (!isdigit(msg[i]))) {
						st = false;
					}
				}
				else {
					st = false;
				}
			}
			if (st)
			{
				SUCCESS
				cout << "Hidden message: " << msg << endl;
				cout << endl;
			}
			else {
				Unable();
			}
		}
		else {
			Unable();	
		}
	}
	else {
		Unable();
	}
	imgW.close();
	menu();
}

void Image::Unable() {
	char YorN[SMX] = { 0 };
	FAILURE
	cout << "---------------------" << endl;
	cout << "Unable to decrypt a message, probably the file doesn't exist \n or the name given is wrong." << endl;
	cout << "---------------------" << endl;
	cout << endl;
	cout << "Would you like an advanced ASCII symbols search?" << endl;
	cout << "1 - Yes, 0 - No" << endl << endl << ">";
	while (strlen(YorN) == 0) {
		cin.getline(YorN, LMX);
	}
	if (YorN[0] == '1')
	{
		imgW.close();
		RecogN();
	}
	else
	{
		imgW.close();
		menu();
	}
}

void Image::Party()
{
	memset(fullpathN, 0, sizeof(fullpathN));
	srand(time(NULL));
	system("cls");
	cout << "Enter output file name: \n>";
	while (strlen(fullpathN) == 0) {
		cin.getline(fullpathN, LMX);
	}
	imgO.open(fullpathN, ios::trunc | ios::binary);
	imgI.open(fullpath);
	imgI.seekg(0, 2);
	int size = imgI.tellg();
	imgI.close();
	int s1 = rand() % size;
	int s2 = 0;
	while (s2 < s1) 
	{
		s2 = rand() % size;
	}
	imgI.open(fullpath, ios::binary);
	std::vector<char> fulldata((
		std::istreambuf_iterator<char>(imgI)),
		(std::istreambuf_iterator<char>()));
	vector<char> dong;
	dong.resize(size);
	for (int i = 0; i < s1; i++)
	{
		dong[i] = fulldata[i];
	}
	for (int i = s2; i < fulldata.size(); i++)
	{
		dong[i-s2+s1] = fulldata[i];
	}
	for (int i = 0; i < dong.size(); i++)
	{
		imgO << dong[i];
	}
	imgI.close();
	imgO.close();
	system("cls");
	menu();
}

void Image::Shuffle()
{
	system("cls");
	tmpA.clear();
	tmpB.clear();
	tmp.clear();
	int a = 0;
	int buffer = 0;
	int endpos = 0;
	cout << "Image's segments shuffling mode." << endl;
	imgW.open(fullpath);
	imgW.seekg(0, 2);
	int size = imgW.tellg();
	cout << "File size: " << size << endl;
	cout << "Enter segment size (MUST be less then file size): ";
	cin >> segment;
	if (segment < size)
	{
		buffer = size % segment;
		endpos = size - buffer;
	}
	else
	{
		INCINP;
		cout << "I said LESS!" << endl;
		imgW.close();
		menu();
	}
	imgW.close();
	cout << "Enter destination file name: ";
	while (strlen(fullpathN) == 0) {
		cin.getline(fullpathN, LMX);
	}
	imgI.open(fullpath, ios::binary);
	imgI.seekg(0, imgW.beg);
	imgO.open(fullpathN, ios::trunc | ios::binary);
	//cout << "size: " << size << ", buffer: " << buffer << ", endpos:" << endpos << endl;
	//cout << "Pos1: " << imgW.tellg() << endl;												<- Another debugging
	vector<char> fulldata((
		std::istreambuf_iterator<char>(imgI)),
		(std::istreambuf_iterator<char>()));
	tmpA.resize(segment);
	tmpB.resize(segment);
	tmp.resize(buffer);
	while (a < endpos)
	{
		for (int i = a; i < a + segment; i++)
		{
			tmpA[i - a] = fulldata[i];
		}		
		a += segment;
		for (int i = a; i < a + segment; i++)
		{
			tmpB[i - a] = fulldata[i];
		}
		a += segment;
		for (int i = 0; i < tmpB.size(); i++)
		{
			imgO << tmpB[i];
		}
		for (int i = 0; i < tmpA.size(); i++)
		{
			imgO << tmpA[i];
		}
	}
	for (int i = endpos; i < size; i++)
	{
		tmp[i - endpos] = fulldata[i];
	}
	for (int i = 0; i < tmp.size(); i++)
	{
		imgO << tmp[i];
	}
	cout << endl;
	imgI.close();
	imgO.close();
	//exit(42);
	menu();
}

void Image::RecogN() 
{
	bool st = false;
	char inp[MMX] = { 0 };
	char ascii[MMX] = { 0 };
	char asciiL[MMX] = { 0 };
	char asciiU[MMX] = { 0 };
	char asciiD[MMX] = { 0 };
	char asciiS[MMX] = { 0 };
	int a = 0;
	int L = 0;
	int U = 0;
	int D = 0;
	int S = 0;
	system("cls");
	imgI.open(fullpath, ios::binary);
	std::vector<char> fulldata((
		std::istreambuf_iterator<char>(imgI)),
		(std::istreambuf_iterator<char>()));
	for (size_t i = 0; i < fulldata.size(); i++)
	{
		if (__isascii(fulldata[i])) {
			if ((isdigit(fulldata[i])) || (isalpha(fulldata[i])))
			{
				ascii[a] = fulldata[i];
				a++;
				st = true;
			}
			if (isdigit(fulldata[i]))
			{
				asciiD[D] = fulldata[i];
				D++;
			}
			else if (isalpha(fulldata[i]))
			{
				if (islower(fulldata[i]))
				{
					asciiL[L] = fulldata[i];
					L++;
				}
				else
				{
					asciiU[U] = fulldata[i];
					U++;
				}
			}
			else 
			{
				asciiS[S] = fulldata[i];
				S++;
			}
		}
	}
	if (st) {
		if (U > 0) {
			cout << "ASCII Upper symbols:" << endl;
			cout << asciiU << endl;
			cout << endl;
		}
		if (L > 0)
		{
			cout << "ASCII Lower symbols:" << endl;
			cout << asciiL << endl;
			cout << endl;
		}
		if (D > 0)
		{
			cout << "ASCII Digits: " << endl;
			cout << asciiD << endl;
			cout << endl;
		}
	}
	if (st) {
		cout << "---------------------" << endl;
		cout << "Save it to file? (type full name to save or type 1 to skip)" << endl;
		while (strlen(inp) == 0) {
			cin.getline(inp, LMX);
		}
		if ((strlen(inp) == 1)&&(inp[0] == 1))
		{
			memset(ascii, 0, sizeof(ascii));
			memset(asciiL, 0, sizeof(asciiL));
			memset(asciiU, 0, sizeof(asciiU));
			memset(asciiD, 0, sizeof(asciiD));
			memset(asciiS, 0, sizeof(asciiS));
			menu();
		}
		else 
		{
			strcpy(fullpathN, inp);
			imgO.open(fullpathN);
			imgO << "----------------------------------------" << endl;
			imgO << "ASCII Advanced search results, file name - " << fullpath << ": " << endl;
			imgO << "----------------------------------------" << endl;
			imgO << "All ASCII symbols:" << endl;
			imgO << ascii << endl;
			imgO << endl;
			if (st) {
				if (U > 0) {
					imgO << "ASCII Upper symbols:" << endl;
					imgO << asciiU << endl;
					imgO << endl;
				}
				if (L > 0)
				{
					imgO << "ASCII Lower symbols:" << endl;
					imgO << asciiL << endl;
					imgO << endl;
				}
				if (D > 0)
				{
					imgO << "ASCII Digits: " << endl;
					imgO << asciiD << endl;
					imgO << endl;
				}
				if (S > 0)
				{
					imgO << "ASCII Specs: " << endl;
					imgO << asciiS << endl;
					imgO << endl;
				}
			}
			imgO << "----------------------------------------" << endl;
			imgO.close();
		}
	}
	menu();
}

Image::~Image()
{

}

int main(){
	Salutation();
	return 0;
}

/*
	Code made by Sergey 'Ingenious' Rakhmanov, for free non-profit use. 
	If you want to contact me, there are my credits:
	
	GitHub: IngeniousA
	VK: vk.com/1ngenious
	E-Mail: crashtranslator@yandex.ru
*/
