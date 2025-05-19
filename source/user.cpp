#include "user.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

vector<User> User::users;

User::User(string id, string username, string password)
    : id(id), username(username), password(password) {}

string User::getId() const { return id; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }

void User::sendMessage(const string& content, Contact* contact) {
   
    Message msg{ id, contact->getId(), content };

   
    sentMessages.push(msg);

    
    contact->addMessage(msg);
}


void User::receiveMessage(const Message& msg) {
    if (contacts.find(msg.senderID) == contacts.end()) {
        addContact(msg.senderID);
    }
    contacts[msg.senderID].addMessage(msg);
    cout << "Message received from " << msg.senderID << ": " << msg.content << endl;
}



void User::undoMessage() {
    if (sentMessages.empty()) return;
    Message last = sentMessages.top(); sentMessages.pop();
    if (contacts.count(last.receiverID)) {
        vector<Message>& msgs = contacts[last.receiverID].getMessages();
        for (auto it = msgs.rbegin(); it != msgs.rend(); ++it) {
            if (it->content == last.content && it->senderID == last.senderID) {
                msgs.erase(next(it).base());
                break;
            }
        }
    }
}

void User::viewMessages() {
    // Show sent messages first
    stack<Message> temp = sentMessages;
    cout << "Sent messages:\n";
    while (!temp.empty()) {
        Message m = temp.top(); temp.pop();
        cout << "To " << m.receiverID << ": " << m.content << endl;
    }

    // Show received messages (from contacts)
    
}


void User::viewMessageByContact(const string& contactID) {
    if (contacts.count(contactID)) {
        cout << "Sent messages to " << contactID << ":\n";
        stack<Message> tempSent = sentMessages;
        while (!tempSent.empty()) {
            Message m = tempSent.top();
            tempSent.pop();
            if (m.receiverID == contactID) {
                cout << m.senderID << " -> " << m.receiverID << ": " << m.content << endl;
            }
        }

        cout << "Received messages from " << contactID << ":\n";
        for (const Message& m : contacts[contactID].getMessages()) {
            if (m.senderID == contactID) {
                cout << m.senderID << " -> " << m.receiverID << ": " << m.content << endl;
            }
        }
    }
    else {
        cout << "No messages with this contact.\n";
    }
}







void User::addMessageToFavorites(const Message& msg) {
    favorites.push(msg);
}

void User::removeOldestFavorite() {
    if (!favorites.empty()) favorites.pop();
}

void User::viewFavoriteMessages() {
    queue<Message> temp = favorites;
    while (!temp.empty()) {
        Message m = temp.front(); temp.pop();
        cout << m.senderID << " -> " << m.receiverID << ": " << m.content << endl;
    }
}

void User::addContact(const string& contactID) {
    if (contacts.find(contactID) == contacts.end()) {
        contacts[contactID] = Contact(contactID); // Properly initialize the contact
    }
}


bool User::removeContact(const string& id) {
    return contacts.erase(id) > 0;
}

Contact* User::findContact(const string& id) {
    if (contacts.count(id)) return &contacts[id];
    return nullptr;
}

void User::displayContactsByMessageCount() {
    vector<pair<string, int>> vec;
    for (auto& [id, c] : contacts) {
        vec.push_back({ id, c.getMessageCount() });  // Use getMessageCount() to get the number of messages
    }
    sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });
    for (auto& [id, count] : vec) {
        cout << "Contact ID: " << id << " | Messages: " << count << endl;
    }
}

void User::saveUser(ofstream& out) {
    out << id << ' ' << username << ' ' << password << '\n';
}

void User::saveContactData(ofstream& out) {
    for (const auto& pair : contacts) {
        const string& cid = pair.first;
        const vector<Message>& msgs = pair.second.getMessages();
        for (const Message& m : msgs) {
            out << m.senderID << " " << m.receiverID << " " << m.content << endl;
        }
    }
}


void User::loadContactData(ifstream& in) {
    string senderId, receiverId, msg;
    while (in >> senderId >> receiverId) {
        in.ignore();  // Skip space before message
        getline(in, msg);

        Message m{ senderId, receiverId, msg };

        // If the message is from this user
        if (senderId == this->id) {
            addContact(receiverId);  // Ensure the contact exists
            sentMessages.push(m);    // Add to sent messages
            contacts[receiverId].addMessage(m);  // Add to receiver's contact
        }
        else if (receiverId == this->id) {  // If the message is for this user
            addContact(senderId);   // Ensure the contact exists
            contacts[senderId].addMessage(m);  // Add to the sender's contact
        }
    }
}





