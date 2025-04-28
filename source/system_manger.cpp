#include"headers/system_manger.h"
#include "json.hpp"
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
