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
    favorites.push_back(msg);
    
}

void User::removeOldestFavorite() {
    if (!favorites.empty()) favorites.erase(favorites.begin());

}

void User::viewFavoriteMessages() {
    for (const Message& m : favorites) {
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

    


void User::loadContactData(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Contacts file not found.\n";
        return;
    }

    contacts.clear();
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        string contactID = line;
        Contact contact(contactID);

        while (getline(in, line) && line != "--END--") {
            istringstream ss(line);
            string messageID, senderID, receiverID, content;

            getline(ss, messageID, '|');
            getline(ss, senderID, '|');
            getline(ss, receiverID, '|');
            getline(ss, content);

            Message msg(senderID, receiverID, content);
            msg.messageID = messageID;
            contact.addMessage(msg);

            // This is the fix:
            if (senderID == id) {
                sentMessages.push(msg); // Rebuild sentMessages stack
            }
        }

        contacts[contactID] = contact;
    }
}

void User::saveContactData(const string& filename) const {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Failed to open file for saving contacts.\n";
        return;
    }

    for (const auto& pair : contacts) {
        const Contact& contact = pair.second;
        out << contact.getId() << "\n";
        for (const Message& msg : contact.getMessages()) {
            out << msg.messageID << "|" << msg.getSenderId() << "|" << msg.getReceiverId() << "|" << msg.getContent() << "\n";
        }
        out << "--END--\n";
    }

    out.close();
}

void User::clearAllData() {
    contacts.clear();

    // Clear sentMessages stack
    while (!sentMessages.empty()) sentMessages.pop();

    // Clear favorites vector
    favorites.clear();
}








