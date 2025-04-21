#pragma once
#include <vector>
#include <string>
#include "user.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class fileman {
private:
    vector<User> users;

public:
    fileman() = default;

    void readFromFile(const string& filename);
    void writeToFile(const string& filename) const;

    vector<User>& getUsers();             
    void addUser(const User& user);    
};    
