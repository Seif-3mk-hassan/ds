//
// Created by user on 4/21/2025.
//

#include "login.h"
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include "user.h"
using namespace std;

void login ::registerr()
{
    //cout << "Welcome to the registration system!" << endl;
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    if(s.is_user_registered(username)){
        cout << "Username already exists!" << endl;
        cout<< "1 return to mainmenu"<<'\n';
        cout<<"2 login"<<endl;
        int choice ;
        cin>>choice;
        if (choice == 1)
        {
            login::mainMenu();
        }else if (choice == 2)
        {
            login::is_logged_in();
        }
    }
    else{
        cout << "Enter password: ";
        cin >> password;
        cout << "User registered successfully!" << endl;
        s.addUser(username, password);
    }
}

User login::is_logged_in()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if(s.is_login(username,password)=="SUCCESS"){
        cout << "Logged in successfully!" << endl;
        return s.get_user_id_by_username(username);
    }
    else{
        cout << "Login failed!" << endl;
        login::is_logged_in();
    }
    return User();
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
        User user = is_logged_in();
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}

void login::saveTofile(User U)
{
    json jsonUser;
    for (auto j : User::usersArrJson["users"]["ID"])
    {
        if(j == U.getId())
        {
            cout << "user already exists\n";
            return;
        }
    }
    jsonUser["ID"] = U.getId();
    jsonUser["username"] = U.getUsername();
    jsonUser["password"] = U.getPassword();
    User::usersArrJson["users"].push_back(jsonUser);
    U.addToJsonfile(User::usersArrJson,"User.json");
}
