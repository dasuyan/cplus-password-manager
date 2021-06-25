//
// Created by Hyperbook on 23.06.2021.
//
#include <iterator>
#include <iomanip>
#include <ctime>
#include<iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "menu.h"
using namespace std;

vector<Category> vecCat;
vector<string> vecCatS;
vector<Password> vecPass;
vector<string> vecPassS;

string util::encrypt(string s) {
    for(int i = 0; s[i] != '\0'; i++)
        s[i] = s[i] + 2;
    return s;
}
string util::decrypt(string s) {
    for(int i = 0; s[i] != '\0'; i++)
        s[i] = s[i] - 2;
    return s;
}

void util::writeToFile(string strNew, int lineToReplace, const string& filePath) {

    vector<string> lines;

    ifstream is(filePath);

    string line;
    while (getline(is, line))
        lines.push_back(line);

    is.close();

    lines[lineToReplace] = std::move(strNew);

    ofstream os(filePath);

    for(const auto& l : lines)
        os << l << '\n';

    os.close();
}
void util::saveData(const string& filePath) {

      /*Category c1 = {"office"};
      Category c2 = {"entertainment"};
      Category c3 = {"finance"};

      vecCat.push_back(c1);
      vecCat.push_back(c2);
      vecCat.push_back(c3);*/

    for (auto & i : vecCat) {
        string record(i.name);
        vecCatS.push_back(record);
    }

    writeToFile(encrypt(vectorToString(vecCatS)), 3, filePath);

    /*Password p1 = {"Gmail", "123", c1};
    Password p2 = {"Netflix", "film", c2};
    Password p3 = {"Credit Agricole", "uwuowo1", c3};

    vecPass.push_back(p1);
    vecPass.push_back(p2);
    vecPass.push_back(p3);*/

    for (auto & i : vecPass) {
        string record(i.name);
        record.append(":");
        record.append(i.password);
        record.append(":");
        record.append(i.category.name);

        vecPassS.push_back(record);
    }

    writeToFile(encrypt(vectorToString(vecPassS)), 2, filePath);
}

string util::vectorToString(vector<string> vec) {
    ostringstream vts;

    if (!vec.empty())
    {
        copy(vec.begin(), vec.end()-1,
                  ostream_iterator<string>(vts, ", "));
        vts << vec.back();
    }
    return vts.str();
}
string util::readLine(const string& filePath, int lineNr){
    string line;
    ifstream file(filePath);
    for(int i = 0; i < lineNr; ++i)
        getline(file, line);
    return line;
}
vector<string> util::split(string s, const string& delimiter) {
    vector<string> result;
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        //cout << token << endl;
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    return result;
}

void util::login(const string& filePath) {
    string readMP = decrypt(readLine(filePath, 1));
    string input;
    bool incorrect = true;

    while (incorrect) {
        cout << "Enter the main password: " << endl;
        cin >> input;
        if (readMP == input) {
            cout << "Correct password" << endl << endl;
            readTimeStamp(filePath);
            writeTimeStamp(filePath);
            incorrect = false;
        } else {
            cout << "Incorrect password, try again" << endl;
        }
    }
}
void util::writeTimeStamp(const string& filePath) {
    auto t = std::time(nullptr);
    auto tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y %H:%M:%S");
    auto timeStamp = oss.str();

    writeToFile(encrypt(timeStamp), 1, filePath);

}
void util::readTimeStamp(const string& filePath) {
    cout << "This file was last accessed on: "<< decrypt(readLine(filePath, 2)) << endl;
}
void util::reconstruct(const string& filePath) {
    string line = decrypt(readLine(filePath, 4));
    vector<string> reC = split(line, ", ");

    for (auto & i : reC) {
        Category temp = {i};
        vecCat.push_back(temp);
    }

    line = decrypt(readLine(filePath, 3));
    vector<string> reP = split(line, ", ");
    Category remakeC;

    for (auto & i : reP) {
        vector<string> rePI = split(i, ":");

        for (auto & j : vecCat) {
            if (j.name == rePI[2])
                remakeC = j;
        }
            Password temp = {rePI[0], rePI[1], remakeC};
            vecPass.push_back(temp);
    }

}

void ui::showAllPasswords() {
    int count = 0;
                             cout << "  " << "Name:" << "  " << "Password:" << "  " << "Category:" << "  " << endl;
    for (auto&& x : vecPass) cout << " | " << ++count << "." << " | " << x.name << " | " << x.password << " | "  << x.category.name << " | " << endl;
    cout << endl;
}
void ui::showCategories() {
    int count = 0;
    cout << "Categories: " << endl;
    for (auto&& x : vecCat) cout << ++count << ". " << x.name << endl;
    cout << endl;
}
void ui::showFromCategory() {
    cout << "Please choose a category:\n";

    int count = 0;
    int choice;
    Category chosen;

    for (auto&& x : vecCat) cout << ++count << ". " << x.name << endl;
    cin >> choice;

    if (choice > 0 && choice <= vecCat.size()) {
        chosen = vecCat[choice - 1];
        count = 0;

        cout << "  " << "Name:" << "  " << "Password:" << "  " << "Category:" << "  " << endl;
        for (auto & vecPas : vecPass) {
            if (vecPas.category.name == chosen.name)
                cout << " | " << ++count << "." << " | " << vecPas.name << " | " << vecPas.password << " | "  << vecPas.category.name << " | " << endl;
        }
    } else cout << "Category does not exist" << endl;

    cout << endl;
}

void ui::addPassword() {
    Password temp;
    cout << "Please enter the password name:\n";
    cin.get();
    getline(cin, temp.name);
    cout << "Enter the password:\n";
    getline(cin, temp.password);

    cout << "Choose a category:\n";
    int count = 0;
    int choice;
    bool correct = false;
    for (auto&& x : vecCat) cout << ++count << ". " << x.name << endl;
    cin >> choice;
    if (choice > 0 && choice <= vecCat.size()) {
        correct = true;
        temp.category = vecCat[choice - 1];
    } else cout << "Category does not exist" << endl;

    if (correct) vecPass.push_back(temp);
};
void ui::deletePassword() {
    cout << "Choose a password to delete: " << endl;
    showAllPasswords();
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= vecPass.size())
    vecPass.erase(vecPass.begin() + choice - 1);
    else
        cout << "Password does not exist" << endl;
}

void ui::addCategory() {
    Category temp;
    cout << "Please enter the category name:\n";
    cin.get();
    getline(cin, temp.name);
    vecCat.push_back(temp);
}
void ui::deleteCategory() {
    cout << "Choose a category to remove, along with all its passwords:" << endl;
    showCategories();
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= vecCat.size()) {
        for (int i = 0; i < vecPass.size(); ++i) {
            if (vecPass[i].category.name == vecCat[choice - 1].name) {
                vecPass.erase(vecPass.begin() + i);
                i--;
            }
        }
        vecCat.erase(vecCat.begin() + choice - 1);
    }
    else
        cout << "Category does not exist" << endl;
}

bool sortN(const Password &lhs, const Password &rhs) { return lhs.name < rhs.name; }
void ui::sortByName() {
    sort(vecPass.begin(), vecPass.end(), sortN);
    showAllPasswords();
}

bool sortC(const Password &lhs, const Password &rhs) { return lhs.category.name < rhs.category.name; }
void ui::sortByCategory() {
    sort(vecPass.begin(), vecPass.end(), sortC);
    showAllPasswords();
}


