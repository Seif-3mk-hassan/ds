#include "User.h"
using namespace std ;


// Constructor
// user::User(const string& id, const string& uname, const string& pwd)
//     : ID(id), username(uname), password(pwd) {}

// string user::getId() const { return ID; }
// string user::getUsername() const { return username; }
// string user::getPassword() const { return password; }

// bool user::addContact(const string& userId, const string& username) {
//     if (contacts.find(userId) == contacts.end()) {
//         contacts[userId] = Contact(userId, username);
//         return true;
//     }
//     return false;   
// }

// bool user::removeContact(const string& userId) {
//     return contacts.erase(userId) > 0;
// }

// Contact* user::findContact(const string& userId) {
//     auto it = contacts.find(userId);
//     return it != contacts.end() ? &it->second : nullptr;
// }

// vector<Contact> user::getSortedContacts() const {
//     vector<Contact> sortedContacts;
//     for (const auto& pair : contacts) {
//         sortedContacts.push_back(pair.second);
//     }
//     sort(sortedContacts.begin(), sortedContacts.end());
//     return sortedContacts;
// }

// void user::receiveMessage(const Message& message) {
//     receivedMessages.push_back(message);
//     auto contact = findContact(message.getSenderId());
//     if (contact) {
//         contact->addMessage(message);
//     }
// }

// const vector<Message>& user::getReceivedMessages() const {
//     return receivedMessages;
// }

// // ===========================
// // JSON FUNCTIONS
// // ===========================
// json user::toJson() const {
//     json j;
//     j["ID"] = ID;
//     j["username"] = username;
//     j["password"] = password;

//     for (const auto& [id, contact] : contacts) {
//         j["contacts"][id] = contact.toJson();
//     }

//     for (const auto& msg : receivedMessages) {
//         j["receivedMessages"].push_back(msg.toJson());
//     }

//     return j;
// }

// void user::fromJson(const json& j) {
//     ID = j.at("ID").get<string>();
//     username = j.at("username").get<string>();
//     password = j.at("password").get<string>();

//     contacts.clear();
//     for (auto& [id, contactJson] : j.at("contacts").items()) {
//         Contact c;
//         c.fromJson(contactJson);
//         contacts[id] = c;
//     }

//     receivedMessages.clear();
//     for (const auto& msgJson : j.at("receivedMessages")) {
//         Message msg;
//         msg.fromJson(msgJson);
//         receivedMessages.push_back(msg);
//     }
// }

// // ===========================
// // FILE OPERATIONS
// // ===========================

// void user::saveUserToFile(const User& user, const string& filename) {
//     ofstream outFile(filename);
//     if (outFile) {
//         outFile << user.toJson().dump(4);
//     }
// }

// User user::loadUserFromFile(const string& filename) {
//     ifstream inFile(filename);
//     if (!inFile) throw runtime_error("Can't open file.");

//     json j;
//     inFile >> j;

//     User user;
//     user.fromJson(j);
//     return user;
// }