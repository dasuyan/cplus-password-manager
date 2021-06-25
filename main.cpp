//
// Created by Hyperbook on 23.06.2021.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "menu.h"
using namespace std;
using namespace util;
using namespace ui;
int main() {

    bool isExit = false;
    int input;
    string filePath;
    cout << "Please provide the source file path: " << endl;
    getline (cin,filePath);

    login(filePath);
    reconstruct(filePath);

    while(!isExit)
    {
        cout <<"--------------------------------------" << endl
             << "\t1. Add password" << endl
             << "\t2. Delete a password" << endl
             << "\t3. Add category" << endl
             << "\t4. Delete a category" << endl
             << "\t5. Sort by name" << endl
             << "\t6. Sort by category" << endl
             << "\t7. View all passwords" << endl
             << "\t8. Filter by category" << endl
             << "\t9. Exit" << endl
             <<"--------------------------------------" << endl;
        while(!(cin>>input))
        {
            cin.clear();
            while(cin.get() != '\n')
                continue;
            cout << "Please try again\n" ;
        }

        switch((Choice)input)
        {
            case a:
                addPassword();
                break;
            case b:
                deletePassword();
                break;
            case c:
                addCategory();
                break;
            case d:
                deleteCategory();
                break;
            case e:
                sortByName();
                break;
            case f:
                sortByCategory();
                break;
            case g:
                showAllPasswords();
                break;
            case h:
                showFromCategory();
                break;
            case i:
                saveData(filePath);
                isExit = true;
                break;
            default:
                cout << "Please try again" << endl;
        }
    }
}
