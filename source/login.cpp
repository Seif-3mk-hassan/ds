//
// Created by user on 4/21/2025.
//

#include "login.h"
#include <iostream>
#include <string>
#include "user.h"
using namespace std;

void login ::registerr()
{
    User new_user;
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
         new_user = s.addUser(username, password);
    }
    //saveTofile(new_user);  //مش شغال عندي  json
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

User login::mainMenu()
{
    User u;
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
        u = is_logged_in();
    }
    else {
        cout << "Invalid choice!" << endl;
        return mainMenu();
    }

    return u;
}



