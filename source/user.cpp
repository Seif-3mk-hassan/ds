#include "user.h"
#include "Contact.h"
#include "filemanger.h"
using namespace std;


// Constructor
User::User(const string& id, const string& uname, const string& pwd)
: ID(id), username(uname), password(pwd) {}

string User::getId() const { return ID; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }



void User::set_id(string id)
{
    ID = id;
}

void User::set_username(string username)
{
    this->username = username;
}

void User::Userset_password(string password)
{
    this->password = password;
}


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


void User::readfromjson(string userid)
{
    json j = filemanger::Readfromjson("User.json");
    for (auto i : j["users"])
    {
        if(i["ID"] == userid)
        {
            username = i["username"];
            password = i["password"];
        }
    }
}
//==============================


