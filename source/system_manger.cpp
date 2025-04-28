#include "../headers/system_manger.h"
#include "json.hpp"
#include <sstream>
#include <iostream>

int system_manager::id_counter = 0;

system_manager::system_manager()
{
    //load_users_from_file(); // Load existing users when the system starts
}

void system_manager::addUser(string username, string password)
{
    User newUser(to_string(id_counter), username, password);
    user_username[username] = newUser;
    use_by_id[to_string(id_counter)] = newUser;
    id_counter++;
}

bool system_manager::is_user_registered(string username)
{
    // Check if the user is already registered or not
    return user_username.find(username) != user_username.end();
}

User system_manager::get_user_id_by_username(string username)
{
    auto it = username_id.find(username);
    if (it != username_id.end())
    {
        return use_by_id[it->second];
    }
    return User();
}

system_manager::login_status system_manager::is_login(string username, string password)
{
    auto it = user_username.find(username);
    if (it != user_username.end())
    {
        if (it->second.getPassword() == password)
        {
            return login_status::SUCCESS;
        }
        else
        {
            return login_status::FAILED;
        }
    }
    return login_status::FAILED;
}

unordered_map<string,User>& system_manager::get_user_by_id() {
    return use_by_id;
}
