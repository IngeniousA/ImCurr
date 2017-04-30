#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#define MX 256
#define LMX 1500000
#define FIRST_SYM 33
#define HIDELIM 89
#define INCINP cout << "---------------------" << endl;\
			   cout << "---Incorrect input---" << endl;\
			   cout << "---------------------" << endl;\

#define INPVIOLATION cout << "Input string had an unacceptable symbol(s). Please, try again" << endl; cout << endl;

using namespace std;

void sw(int st);
void Credits();
char inputch[MX];
bool inp = true;

class Image
{
public:
	Image();
	void setp(char * path); //set path
	void Corrupt(); //hide a message
	void GetMSG(); //get a message
	void Ressurect(); //ressurect a corrupted picture
	void RIP(); //corrupt a picture
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
	char tmpA[MX];
	char tmpB[MX];
	char tmp[MX];
	//file streams
	fstream imgW;
	fstream imgN;
};

Image img;

void menu() {
	memset(inputch, 0, sizeof(inputch));
	short int ch = 0;
	cout << "Enter the full name of image to work with (1 to exit) \n>";
	cin >> inputch;
	if ((inputch[0] == '1') && (strlen(inputch) == 1)) {
		exit(0);
	}
	else {
		img.setp(inputch);
	}
	cout << "Please, choose an option:" << endl;
	cout << "1 - Hide a message in an image" << endl;
	cout << "2 - Get a message from an image" << endl;
	cout << "3 - Corrupt an image" << endl;
	cout << "4 - Ressurect an image" << endl;
	cout << "5 - Credits" << endl;
	cout << "6 - Exit" << endl;
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
			img.RIP();
			break;
		case 4:
			img.Ressurect();
			break;
		case 5:
			Credits();
			break;
		case 6:
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

void Success() {
	cout << endl;	
	cout << "-------SUCCESS-------" << endl;
}

void Failure() {
	cout << endl;
	cout << "-------FAILURE-------" << endl;
}

void Salutation() {
	setlocale(LC_ALL, "Russian");
	cout << "===========================" << endl;
	cout << "=====Welcome to ImCurr=====" << endl;
	cout << "===========================" << endl;
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
			cin.getline(msg, HIDELIM);
		}
	}
	else {
		Failure();
		cout << endl;
		INPVIOLATION;
		imgW.open(fullpath, ios::app);
		cout << "Message: ";
		while (strlen(msg) == 0) {
			cin.getline(msg, HIDELIM);
		}
		inp = true;
	}
 	if (msgchk(msg)) {
		num += strlen(msg);
		imgW << msg << num;
		Success();
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
	//cout << "Filename: " << fullpath << ", lng: " << imgW.tellg() << ", sym: " << getn << endl;
	if ((getn > FIRST_SYM) && (getn < (FIRST_SYM + HIDELIM))) {
		int delta = abs(getn - (FIRST_SYM - 1));
		imgW.seekg(-delta, imgW.cur);
		imgW.getline(msg, getn - FIRST_SYM + 1);
		Success();
		cout << "Hidden message: " << msg << endl;
		cout << endl;
	}
	else {
		Failure();
		cout << "---------------------" << endl;
		cout << "Unable to decrypt a message, probably the file doesn't exist \n or the name given is wrong." << endl;
		cout << "---------------------" << endl;
		cout << endl;
	}
	imgW.close();
	menu();
}

void Image::Ressurect()
{  

}

void Image::RIP() //WORK IN PROGRESS
{
	memset(tmpA, 0, sizeof(tmpA));
	memset(tmpB, 0, sizeof(tmpB));
	memset(tmp, 0, sizeof(tmp));
	system("cls");
	cout << "Image corruption mode" << endl;
	cout << "Enter segment scale (1<n<2000): ";
	cin >> segment;
	imgW.open(fullpath);
	imgW.seekg(0, 2);
	int size = imgW.tellg();
	int buffer = size % segment;
	int endpos = size - buffer;
	cout << "Enter destination file name: ";
	cin >> fullpathN;
	imgW.close();
	//imgW.open(fullpath, ios::binary);
	imgW.open(fullpath, ios::binary);
	imgW.seekg(0, imgW.beg);
	imgN.open(fullpathN, ios::trunc | ios::binary);
	cout << "size: " << size << ", buffer: " << buffer << ", endpos:" << endpos << endl;
	cout << "Pos1: " << imgW.tellg() << endl;
	while (imgW.tellg() <= endpos) {
		imgW.readsome(tmpA, segment);
		imgW.readsome(tmpB, segment);
		imgN.write(tmpB, segment);
		imgN.write(tmpA, segment);
		cout << "Pos1: " << imgW.tellg() << ", Pos2: " << imgN.tellp() << endl;
	}
	imgW.read(tmp, buffer);
	imgN.write(tmp, buffer);
	imgW.close();
	imgN.close();
}



Image::~Image()
{

}

int main() {
	Salutation();
	menu();
	return 0;
}

/*
	Code made by 'Ingenious', for free non-commercial use. 
	If you want to contact me, there are my credits:
	
	GitHub: IngeniousA
	VK: vk.com/1ngenious
	E-Mail: crashtranslator@yandex.ru
*/