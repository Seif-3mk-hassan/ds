#include"system_manger.h"
#include "nlohmann/json.hpp"
#include <sstream>
#include <iostream>

system_manager::system_manager()
{
    //load_users_from_file(); // Load existing users when the system starts
}

bool system_manager::is_user_registered(string username)
{
    // Check if the user is already registered or not

    return user_username.find(username) != user_username.end();
}

string system_manager::get_user_id_by_username(string username, string password)
{
    // Check if the user is already registered or not
    auto it = user_username.find(username);
    if (it != user_username.end())
    {
        return it->second; // Return the user ID associated with the username
    }
    return ""; // Return an empty string if the user is not found
}

system_manager::login_status system_manager::is_login(string username, string password)
{
    // Check if the user is already registered or not
    auto it = user_username.find(username);
    if (it != user_username.end())
    {
        // Check if the password matches
        if (it->second == password)
        {
            return login_status::SUCCESS; // Login successful
        }
        else
        {
            return login_status::FAILED; // Incorrect password
        }
    }
    return login_status::FAILED; // User not found
}

unordered_map<string,string>& system_manager::get_user_by_id() {
    return use_by_id;
}

bool system_manger::regiter_user(string username, string password)
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