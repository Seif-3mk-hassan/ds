//
// Created by user on 4/25/2025.
//

#ifndef SYSTEM_MANGER_H
#define SYSTEM_MANGER_H
#pragma once
#include "nlohmann/json.hpp"
#include<iostream>
#include<fstream>
#include<unordered_map>
#include "user.h"

using namespace std;
using json = nlohmann::json;

class system_manager
{
    unordered_map<string,string> use_by_id; //id,class user
    unordered_map<string,string> user_username; //id,username  will be used to check if the user is already registered or not
public:
    // Constructor
    system_manager();


    unordered_map<string,string>& get_user_by_id(); // Getter for use_by_id
    unordered_map<string,string>& get_user_username(); // Getter for user_username

    void set_use_by_id(const unordered_map<string,string>& new_use_by_id);
    void set_user_username(const unordered_map<string,string>& new_user_username);

    User get_user_info();
    void register_user(string username, string password);
    bool is_user_registered(string username);
    string get_user_id_by_username(string username, string password);
    enum login_status { SUCCESS, FAILED };
    login_status is_login(string username, string password);
    void mainMenu();

};
#endif //SYSTEM_MANGER_H
