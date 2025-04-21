#include "fileman.hpp"
#include <fstream>
#include <iostream>
using namespace std ;


void fileman::readFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << " Could not open file for reading: " << filename << endl;
        return;
    }

    json j;
    inFile >> j;

    users.clear();
    for (const auto& userJson : j["users"]) {
        User user;
        user.fromJson(userJson);
        users.push_back(user);
    }
}

void fileman::writeToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cout << " Could not open file for writing: " << filename << endl;
        return;
    }

    json j;
    for (const auto& user : users) {
        j["users"].push_back(user.toJson());
    }

    outFile << j.dump(4); 
}

vector<user>& fileman::getUsers() {
    return users;
}

void fileman::addUser(const user& user) {
    users.push_back(user);
}
