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

char sizes[256][256] = { 0 };
char names[256][256] = { 0 };

typedef std::vector<char> strV;

std::vector<char*> nms;
std::vector<int> lngs;

void core(const char sr[], const char des[], const char k[], char mode) {
    std::ifstream src;
    std::ofstream dst;
    strV key;
    key.resize(0);
    for (int i = 0; i < strlen(k); i++)
        key.push_back(k[i]);
    strV srcV;
    Blowfish bf(key);
    src.open(sr, std::ios::binary);
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

        if (mode == '1' || mode == '2') {
            dstV = bf.Encrypt(srcV);
		} else if (mode == '0') {
            dstV = bf.Decrypt(srcV);
		} if (mode != '2') {
            dst.open(des, std::ios::out | std::ios::binary);
		} else {
            dst.open(des, std::ios::app | std::ios::binary);
		}

        for (int i = 0; i < dstV.size(); i++) {
            dst.put(dstV[i]);
		}

        if (mode == '2') {
            lngs.push_back(dstV.size());
		}
    dst.close();
}

void sendInfo(const std::vector<int>& lengths, const std::vector<char*>& names) {
    std::ofstream data("coninfo.icsys", std::ios::binary | std::ios::trunc);
    data << lengths.size() << '\0';
    for (int i = 0; i < lengths.size(); i++)
        data << names[i] << '\0' << lengths[i] << '\0';
    data.close();
}

void unpack(char sr[], char des[], char size[], char k[], long skip) {
    strV key;
    key.resize(0);
    for (int i = 0; i < strlen(k); i++)
        key.push_back(k[i]);
    long sizel = atol(size);
    std::ifstream  src(sr, std::ios::binary);
    std::ofstream  dst(des, std::ios::binary | std::ios::trunc);
    src.seekg(-(sizel + skip), std::ios::end);
    strV text;
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

void inject(const char sr[], const char des[]) {
    std::string outN = std::string(des);
    std::string srcN = std::string(sr);
    outN += ":" + srcN + ".txt";
    std::ofstream out(outN.c_str(), std::ios::binary | std::ios::trunc);
    std::ifstream src(sr, std::ios::binary);
    out << src.rdbuf();
    out.close();
    src.close();
}

void eject(const char sr[], const char des[]) {
    std::string outN = std::string(des);
    std::string srcN = std::string(sr);
    srcN += ":" + outN + ".txt";
    std::ofstream out(outN.c_str(), std::ios::binary | std::ios::trunc);
    std::ifstream src(srcN.c_str(), std::ios::binary);
    out << src.rdbuf();
    out.close();
    src.close();
}

void end() {
    std::ofstream ready("ready.icsys", std::ios::binary | std::ios::trunc);
    ready << '\0';
    ready.close();
}

int main(int argc, char *argv[]) {
    unsigned long skip = 0;
    if (argv[argc - 1][0] == '1' || argv[argc - 1][0] == '0') {
        std::cout << "Processing...\n";
        core(argv[1], argv[2], argv[3], argv[argc - 1][0]);
    } else if (argv[argc - 1][0] == '2') {
        int num = atoi(argv[argc - 2]);
        std::cout << "Processing...\n";
        nms.resize(num);
        for (int i = 3; i < num + 3; i++)
        {
            core(argv[argc - i], argv[1], argv[2], '2');
            nms[i - 3] = argv[argc - i];
        }
        sendInfo(lngs, nms);
    } else if (argv[argc - 1][0] == '3') {
        char key[512] = { 0 };
        int num = atoi(argv[3]);
        strcpy(argv[1], argv[1]);
        strcpy(key, argv[2]);
        for (int i = 4; i < 4 + (num * 2) - 1; i += 2) {
            strcpy(names[i - 4], argv[i]);
            strcpy(sizes[i - 4], argv[i + 1]);
        }
        for (int i = 0; i < num * 2; i += 2) {
            unpack(argv[1], names[i], sizes[i], key, skip);
            skip += atol(sizes[i]);
            system("cls");
            std::cout << "Processing: " << std::fixed << std::setprecision(2) << ((double)i / 2) / double(num) * 100 << "%";
        }
    } else if (argv[argc - 1][0] == '4') {
        std::cout << "Processing...\n";
        inject(argv[1], argv[2]);
    } else if (argv[argc - 1][0] == '5') {
        std::cout << "Processing...\n";
        eject(argv[1], argv[2]);
    } else {
        std::cout << "Launched not by ImCurr, leaving...";
        return 0;
    }
    end();
    std::cout << "Done!\n";
    return 0;
}