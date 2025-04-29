#pragma once
#include "../lib/json.hpp"
#include<iostream>
#include<fstream>
#include<unordered_map>
#include "user.h"
using namespace std;
using json = nlohmann::json;

class system_manager
{   
private:
    unordered_map<string,User> use_by_id; //id,class user
    unordered_map<string,string>username_id; //username,id
    unordered_map<string,User> user_username; //username,User
public:
    static int id_counter;
    // Constructor
    system_manager();

    unordered_map<string,User>& get_user_by_id(); // Getter for use_by_id
    unordered_map<string,User>& get_user_username(); // Getter for user_username

    void set_use_by_id(const unordered_map<string,User>& new_use_by_id);
    void set_user_username(const unordered_map<string,User>& new_user_username);
    
    bool is_user_registered(string username);
    User get_user_id_by_username(string username);
    enum login_status { SUCCESS, FAILED };
    login_status is_login(string username, string password);

    void addUser(string username, string password);

    void saveUsersToFile(const std::string& filename);
};