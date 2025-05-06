#include <iostream>
#include<cmath>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<stack>
#include<deque>
#include<string>
#include "headers/user.h"
#include "headers/system_manger.h"
#include "login.h"
//#include<vector>
//#include<D:/ggggg/vcpkg/packages/nlohmann-json_x64-windows/include/nlohmann/json.hpp>
using namespace std;

#define ll long long
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ld long double
#define vi vector<ll>


//using json = nlohmann::json;

struct Node {
    string id;
    string name;
    string pass;
    vector<string> friends;
    stack<string> messages;
};
int main() {
    vector<User>& users = User::users;
    User* currentUser = nullptr;
    int mainChoice;

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            string uname, pwd;
            cout << "Enter username: "; cin >> uname;
            cout << "Enter password: "; cin >> pwd;

            string id = "U" + to_string(users.size() + 1);
            User newUser(id, uname, pwd);
            users.push_back(newUser);

            cout << "Registration successful.\n";

        }
        else if (mainChoice == 2) {
            string uname, pwd;
            cout << "Enter username: "; cin >> uname;
            cout << "Enter password: "; cin >> pwd;

            bool found = false;
            for (auto& u : users) {
                if (u.getUsername() == uname && u.getPassword() == pwd) {
                    currentUser = &u;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Invalid login.\n";
                continue;
            }

            cout << "Login successful.\n";

            int choice;
            do {
                cout << "\nUser Menu:\n";
                cout << "1. Send Message\n";
                cout << "2. Undo Last Message\n";
                cout << "3. View Sent Messages\n";
                cout << "4. View Messages From Contact\n";
                cout << "5. Add to Favorites\n";
                cout << "6. Remove Oldest Favorite\n";
                cout << "7. View Favorites\n";
                cout << "8. Display Contacts by Message Count\n";
                cout << "9. Remove Contact\n";
                cout << "10. Search for Contact\n";
                cout << "11. Logout\n";
                cout << "Choice: ";
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    string receiverId, content;
                    cout << "Enter receiver ID: ";
                    getline(cin, receiverId);
                    cout << "Enter message: ";
                    getline(cin, content);

                    currentUser->addContact(receiverId);  // Rule: only add if messaged
                    Contact* contact = currentUser->findContact(receiverId);
                    currentUser->sendMessage(content, contact);

                    // Deliver to receiver if exists
                    for (User& other : users) {
                        if (other.getId() == receiverId) {
                            Message msg;
                            msg.senderID = currentUser->getId();
                            msg.content = content;
                            msg.receiverID = receiverId;
                            other.receiveMessage(msg);
                            break;
                        }
                    }

                    cout << "Message sent.\n";

                }
                else if (choice == 2) {
                    currentUser->undoMessage();
                    cout << "Last message undone.\n";

                }
                else if (choice == 3) {
                    currentUser->viewMessages();

                }
                else if (choice == 4) {
                    string contactId;
                    cout << "Enter contact ID: ";
                    getline(cin, contactId);
                    currentUser->viewMessageByContact(contactId);

                }
                else if (choice == 5) {
                    if (!currentUser->sentMessages.empty()) {
                        Message msg = currentUser->sentMessages.top();
                        currentUser->addMessageToFavorites(msg);
                        cout << "Message added to favorites.\n";
                    }
                    else {
                        cout << "No message to add.\n";
                    }

                }
                else if (choice == 6) {
                    currentUser->removeOldestFavorite();

                }
                else if (choice == 7) {
                    currentUser->viewFavoriteMessages();

                }
                else if (choice == 8) {
                    currentUser->displayContactsByMessageCount();

                }
                else if (choice == 9) {
                    string id;
                    cout << "Enter contact ID to remove: ";
                    getline(cin, id);
                    if (currentUser->removeContact(id)) {
                        cout << "Contact removed.\n";
                    }
                    else {
                        cout << "Contact not found.\n";
                    }

                }
                else if (choice == 10) {
                    string id;
                    cout << "Enter contact ID to search: ";
                    getline(cin, id);
                    Contact* c = currentUser->findContact(id);
                    if (c) {
                        cout << "Contact found: " << c->contactID << endl;
                    }
                    else {
                        cout << "NOT FOUND\n";
                    }

                }
            } while (choice != 11);

            currentUser = nullptr;
            cout << "Logged out.\n";

        }
        else if (mainChoice == 3) {
            break;
        }
    }

    return 0;
}

