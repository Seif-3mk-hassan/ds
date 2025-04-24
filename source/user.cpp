#include "user.h"
#include "Contact.h"
using namespace std;


// Constructor
User::User(const string& id, const string& uname, const string& pwd)
    : ID(id), username(uname), password(pwd) {}

string User::getId() const { return ID; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }

bool User::addContact(const string& userId) {
    if (contacts.find(userId) == contacts.end()) {
        contacts[userId] = Contact(userId);
        return true;
    }
    return false;   
}

bool User::removeContact(const string& userId) {
    return contacts.erase(userId) > 0;
}

Contact* User::findContact(const string& userId) {
    auto it = contacts.find(userId);
    return it != contacts.end() ? &it->second : nullptr;
}

vector<Contact> User::getSortedContacts() const { 
    vector<Contact> sortedContacts;
    for (const auto& pair : contacts) {
        sortedContacts.push_back(pair.second);
    }
    sort(sortedContacts.begin(), sortedContacts.end());
    return sortedContacts;
}

void User::receiveMessage(const Message& message) {
    receivedMessages.push_back(message);
    auto contact = findContact(message.getSenderId());
    if (contact) {
        contact->addMessage(message);
    }
}

const vector<Message>& User::getReceivedMessages() const {
    return receivedMessages;
}

void User::sendMessage(string content, Contact reciever) {
    if(reciever.contactID == "null") return;
    Message msg;
    msg.senderID = getId();
    msg.content = content;
    msg.receiverID = reciever.contactID;
    sentMessages.push(msg);
}

void User::undoMessage() {
    if(sentMessages.empty()) return;
    sentMessages.pop();
}

void User::viewMessages() {
    stack<Message> temp = sentMessages;
    while(!temp.empty()) {
        cout << temp.top().content << endl;
        temp.pop();
    }
}

void User::viewMessageByContact(string key) {
    if (contacts.find(key) == contacts.end()) {
        cout << "Contact not found.\n";
        return;
    }
    for(int i = 0; i < receivedMessages.size(); i++) {
        if(receivedMessages[i].getSenderId() == contacts[key].contactID) 
        cout << receivedMessages[i].content;
    }
}

//==========dealing with favourites==========
void User::addMessageToFavorites(Message msg) {
    favoriteMessages.push(msg); 
}

void User::removeOldestFavorite() {
    if (!favoriteMessages.empty()) {
        favoriteMessages.pop();
    } 
    else {cout << "no favorite messages to remove\n";}//handling in another time
}

void User::viewFavoriteMessages() const {
    if (favoriteMessages.empty()) {
        cout << "No favorite messages.\n";//handling in another time
        return;
    }
queue<Message> copy = favoriteMessages; //  3 4 5
while (!copy.empty()) {
    cout << copy.front().content << "\n";
    copy.pop();}
}
//==============================


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