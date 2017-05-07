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
#define MX 256
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
	//void Ressurect(); ressurect a corrupted picture
	//void RIP(); corrupt a picture
	void Shuffle(); //UPD: Merged corruption and ressurection into one function
	~Image(); 

private:
	//local strings
	char fullpath[MX];
	char fullpathN[MX];
	char msg[MX];
	char num = '!';
	char getn;
	//corrupting data
	unsigned int segment = 0;
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
	cout << "4 - Credits" << endl;
	cout << "5 - Exit" << endl;
	cout << ">";
	cin.clear();
	cin >> ch;
	sw(ch);
}

void sw(int st) {
	if ((st > 5) || (st < 0)) {
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
			Credits();
			break;
		case 5:
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
	cout << "=           ImCurr v0.2           =" << endl;
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

bool msgchk(char * raw) {
	for (int i = 0; i < strlen(raw); i++)
	{
		if (isascii(raw[i])) {
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
		SUCCESS
		cout << "Hidden message: " << msg << endl;
		cout << endl;
	}
	else {
		FAILURE
		cout << "---------------------" << endl;
		cout << "Unable to decrypt a message, probably the file doesn't exist \n or the name given is wrong." << endl;
		cout << "---------------------" << endl;
		cout << endl;
	}
	imgW.close();
	menu();
}

void Image::Shuffle()
{
	system("cls");
	cout << "Image's segments shuffling mode." << endl;
	cout << "Enter segment size (Recommended values between 100 and 2500): ";
	cin >> segment;
	imgW.open(fullpath);
	imgW.seekg(0, 2);
	int size = imgW.tellg();
	int buffer = size % segment;
	int endpos = size - buffer;
	int a = 0;
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
	std::vector<char> fulldata((
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
	menu();
}

Image::~Image()
{

}

int main() {
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
