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
private:
    static unordered_map<string,User> use_by_id; //id,class user
    static unordered_map<string,string>username_password; //username,id
    static unordered_map<string,User> user_username; //username,User
public:
    static int id_counter;
    // Constructor
    system_manager();

    static unordered_map<string, User>& get_user_by_id(); // Getter for use_by_id
    static unordered_map<string, User>& get_user_username(); // Getter for user_username

    static void set_use_by_id(const unordered_map<string, User>& new_use_by_id);
    static void set_user_username(const unordered_map<string, User>& new_user_username);

    static bool is_user_registered(string username);
    static User get_user_id_by_username(string username);

    enum login_status { SUCCESS, FAILED };

    static login_status is_login(string username, string password);

    static void addUser(string username, string password);

    static void saveUsersToFile(const std::string& filename);
    static void set_userID(vector<User>);
};
