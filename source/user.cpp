#include "user.h"
#include "contact.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;
vector<User> User::users;

User::User(string id, string username, string password)
    : id(id), username(username), password(password) {}

string User::getId() const { return id; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }

void User::sendMessage(const string& content,Contact* contact) {
    if (contact == nullptr) {
        cout << "Error: Cannot send message. Contact does not exist or is hidden." << endl;
        return;
    }

    Message msg{to_string(sentMessages.size()),id, contact->getId(), content };
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
        cout << "To " << m.receiverID << ": " << m.content <<" Message ID "<<m.messageID<< endl;
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
                cout << m.senderID << " -> " << m.receiverID << ": " << m.content <<" Message ID "<<m.messageID<< endl;
            }
        }

        cout << "Received messages from " << contactID << ":\n";
        for (const Message& m : contacts[contactID].getMessages()) {
            if (m.senderID == contactID) {
                cout << m.senderID << " -> " << m.receiverID << ": " << m.content <<" Message ID "<<m.messageID<< endl;
            }
        }
    }
    else {
        cout << "No messages with this contact.\n";
    }
}







void User::addMessageToFavorites() {
    if (sentMessages.empty()) {
        cout << "No messages to add to favorites." << endl;
        return;
    }
    // Create a temporary stack to preserve the original sentMessages
    stack<Message> tempStack = sentMessages;

    // Track message IDs that are already in favorites
    unordered_set<string> favoriteMsgIds;

    // Build set of existing favorite message IDs
    queue<Message> tempFavorites = favorites;
    while (!tempFavorites.empty()) {
        favoriteMsgIds.insert(tempFavorites.front().messageID);
        tempFavorites.pop();
    }

    // Find the most recent unique message (not in favorites yet)
    bool added = false;
    Message messageToAdd;

    // First, find the top message that isn't in favorites
    while (!tempStack.empty() && !added) {
        Message currentMsg = tempStack.top();
        tempStack.pop();

        // Check if this message is already in favorites
        if (favoriteMsgIds.find(currentMsg.messageID) == favoriteMsgIds.end()) {
            // Not in favorites yet, add it
            messageToAdd = currentMsg;
            favorites.push(messageToAdd);
            cout << "Added message to favorites: \"" << messageToAdd.content << "\"" << endl;
            added = true;
        }
    }

    if (!added) {
        cout << "No new unique messages to add to favorites." << endl;
    }
}

void User::removeOldestFavorite() {
    if (!favorites.empty()) favorites.pop();
}

void User::viewFavoriteMessages() {
    if (favorites.empty()) {
        cout << "No favorite messages.\n";
        return;
    }
    queue<Message> temp = favorites;  // copy queue to not modify original
    cout << "Favorite messages:\n";
    while (!temp.empty()) {
        Message m = temp.front();
        temp.pop();
        cout << m.senderID << " -> " << m.receiverID << ": " << m.content <<" message ID "<<m.messageID<< endl;
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



            Message msg(to_string(sentMessages.size()),senderID, receiverID, content);
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
    while (!favorites.empty()) {
        favorites.pop();
    }
}

// void User::saveFavorites(const string& filename)
// {
//     cout<<"inside savefavourite";
//     ofstream in(filename);
//     queue<Message> tmp = favorites;
//     while (!tmp.empty())
//     {
//         in<< tmp.front().senderID <<' '<<tmp.front().receiverID<<' '<<tmp.front().content<<' '<<tmp.front().messageID;
//         tmp.pop();
//     }
//     in.close();
//     cout<< favorites.size()<<endl;
// }
void User::saveFavorites(const string& filename) const {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Failed to open file to save favorites.\n";
        return;
    }

    queue<Message> temp = favorites;
    while (!temp.empty()) {
        const Message& m = temp.front();
        out << m.messageID << "|" << m.senderID << "|" << m.receiverID << "|" << m.content << "\n";
        temp.pop();
    }

    out.close();
}

// void User::loadFavourites(const string& filename)
// {
//     fstream out(filename);
//     string line;
//     while (getline(out, line))
//     {
//         istringstream ss(line);
//         string messageID, senderID, receiverID, content;
//
//         getline(ss, messageID, ' ');
//         getline(ss, senderID, ' ');
//         getline(ss, receiverID, ' ');
//         getline(ss, content);
//
//         Message favm (messageID,senderID,receiverID,content);
//         favorites.push(favm);
//
//     }
//     cout<<"favorites loaded successfully!";
//  out.close();
// }
void User::loadFavorites(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "No favorites file found for this user.\n";
        return;
    }

    favorites = queue<Message>(); // Clear current favorites

    string line;
    while (getline(in, line)) {
        istringstream ss(line);
        string messageID, senderID, receiverID, content;

        getline(ss, messageID, '|');
        getline(ss, senderID, '|');
        getline(ss, receiverID, '|');
        getline(ss, content);

        Message msg(messageID, senderID, receiverID, content);
        msg.messageID = messageID;
        favorites.push(msg);
    }

    in.close();
}









