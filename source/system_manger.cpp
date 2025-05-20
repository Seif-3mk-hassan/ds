#include "../headers/system_manger.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "filemanger.h"
#include "user.h"


int system_manager::id_counter = 0;

// system_manager::system_manager()
// {
//     //load_users_from_file(); // Load existing users when the system starts
//     json users = filemanger::Readfromjson("Users.json");
//     for (auto j:users["users"])
//     {
//         User newUser(j["ID"],j["username"],j["password"]);
//         User::users.push_back(newUser);
//     }
//
// }

User system_manager::addUser(string username, string password)
{
    User newUser(to_string(id_counter), username, password);
    user_username[username] = newUser;
    use_by_id[to_string(id_counter)] = newUser;
    id_counter++;
    return newUser;
}

bool system_manager::is_user_registered(string username)
{
    // Check if the user is already registered or not
    return user_username.find(username) != user_username.end();
}

User system_manager::get_user_id_by_username(string username)
{
    auto it = user_username.find(username);
    if (it != user_username.end())
    {
        return user_username[it->first];
    }
    return User();// EMPTY USER
}

string system_manager::is_login(string username, string password)
{
    auto it = user_username.find(username);
    if (it != user_username.end())
    {
        if (it->second.getPassword() == password)
        {
            return "SUCCESS";
        }
        else
        {
            return "FAILED";
        }
    }
    return "FAILED";
}

unordered_map<string,User>& system_manager::get_user_by_id() {
    return use_by_id;
}

void system_manager::set_userID(vector<User> usersvector)
{
    for (int i =0;i< usersvector.size();i++)
    {
        use_by_id[usersvector[i].getId()] = usersvector[i];
        user_username[usersvector[i].getUsername()] = usersvector[i];
        //username_password[usersvector[i].getUsername()] = usersvector[i].getPassword();
    }

}


// void system_manager::saveUsersToFile(const std::string& filename) {
//     // Create a JSON object to store all users
//     nlohmann::json j;
//     // Iterate through all users and convert each to JSON
//     for (const auto& pair : use_by_id) {
//         j[pair.first] = pair.second.toJson(); // Store user JSON with ID as key
//     }
//     // Open output file and write formatted JSON with 4 space indentation
//     std::ofstream file(filename);
//     file << j.dump(4);
// }
