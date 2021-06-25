//
// Created by Hyperbook on 23.06.2021.
//
#pragma once
#ifndef PJCPROJECTV2_MENU_H
#define PJCPROJECTV2_MENU_H

using namespace std;

enum Choice{ a = 1, b, c, d, e, f, g, h, i};

struct Category {
    string name;
};

struct Password {
    string name;
    string password;
    Category category;
};

namespace util {
    void writeToFile(string strNew, int lineToReplace, const string &filePath);

    void saveData(const string &filePath);

    string vectorToString(vector<string> vec);

    string readLine(const string &filePath, int lineNr);

    void login(const string &filePath);

    void writeTimeStamp(const string &filePath);

    void readTimeStamp(const string &filePath);

    vector<string> split(string s, const string &delimiter);

    void reconstruct(const string &filePath);

    string encrypt(string s);

    string decrypt(string s);
}
namespace ui {
    void showAllPasswords();

    void showFromCategory();

    void showCategories();

    void addPassword();

    void deletePassword();

    void addCategory();

    void deleteCategory();

    void sortByName();

    void sortByCategory();
}
#endif //PJCPROJECTV2_MENU_H
