#include "user.h"
#include "contact.h"
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
    if (contact == nullptr) {
        cout << "Error: Cannot send message. Contact does not exist or is hidden." << endl;
        return;
    }

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
    if (contacts.count(id)) {
        contacts[id].setHidden(true);  // mark as hidden
        return true;
    }
    return false;
}


Contact* User::findContact(const string& id) {
    auto it = contacts.find(id);
    if (it != contacts.end() && !it->second.isHidden()) {
        return &it->second;
    }
    return nullptr;
}


void User::displayContactsByMessageCount() {
    vector<pair<string, int>> vec;
    for (const auto& contact_pair : contacts) {
        const Contact& contact = contact_pair.second;
        if (!contact.isHidden()) {  // Only include visible contacts
            vec.push_back({ contact_pair.first, contact.getMessageCount() });
        }
    }
    sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    for (const auto& pair : vec) {
        cout << "Contact ID: " << pair.first << " | Messages: " << pair.second << endl;
    }
}

void User::saveUser(ofstream& out) {
    out << id << ' ' << username << ' ' << password << '\n';
}

void User::saveContactData(ofstream& out) {
    for (const auto& pair : contacts) {
        const string& cid = pair.first;
        const Contact& contact = pair.second;
        out << "CONTACT " << cid << " " << contact.isHidden() << '\n';
        const vector<Message>& msgs = contact.getMessages();
        for (const Message& m : msgs) {
            out << m.senderID << " " << m.receiverID << " " << m.content << '\n';
        }
    }
}


void User::loadContactData(ifstream& in) {
    string line;
    while (getline(in, line)) {
        if (line.rfind("CONTACT ", 0) == 0) {
            // Line starts with CONTACT: parse hidden status
            istringstream iss(line);
            string tag, contactId;
            bool hidden;
            iss >> tag >> contactId >> hidden;
            addContact(contactId);
            contacts[contactId].setHidden(hidden);
        }
        else {
            // It's a message line: parse and load message
            istringstream iss(line);
            string senderId, receiverId;
            iss >> senderId >> receiverId;
            string msg;
            getline(iss, msg); // the rest is the message content
            if (!msg.empty() && msg[0] == ' ') msg.erase(0, 1);


            Message m{ senderId, receiverId, msg };

            if (senderId == this->id) {
                addContact(receiverId);
                sentMessages.push(m);
                contacts[receiverId].addMessage(m);
            }
            else if (receiverId == this->id) {
                addContact(senderId);
                contacts[senderId].addMessage(m);
            }
        }
    }
}





