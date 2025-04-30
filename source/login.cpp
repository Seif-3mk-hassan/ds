//
// Created by user on 4/21/2025.
//

#include "login.h"
#include <iostream>
#include <user.cpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <folly/dynamic.h>
using json = nlohmann::json;
using namespace std;

bool login ::registerr()
{
    cout << "Welcome to the registration system!" << endl;
    User u1;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ofstream file;
    file.open("login.json");
    file << username << endl << password;
    file.close();
    cout << "User registered successfully!" << endl;
    return true;
}

bool login::is_logged_in()
{
    cout << "Welcome to the login system!" << endl;
    string username, password ,name,pass;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream read("login.txt");
    if (read) {
        getline(read, name);
        getline(read, pass);
        if (name == username && pass == password) {
            cout << "Logged in successfully!" << endl;
            return true;
        }
        else if (name != username) {
            cout << "User not found!" << endl;
            return false;
        }
    }
    else if (username == username && pass != password) {
        cout << "incorrect password!" << endl;
        return false;
    }
}

void login::mainMenu()
{
    cout << "MAIN MENU" << endl;
    cout << "enter your choice" << endl;
    cout << " 1 : register" << endl;
    cout << " 2 : login" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        registerr();
    }
    else if (choice == 2) {
        if (is_logged_in()) {
            cout << "Welcome to the system!" << endl;
        }
        else {
            cout << "Login failed!" << endl;
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}