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
#include "nlohmann/json.hpp"
#include "filemanger.h"
#include "contact.h"
#include "Message.h"
#include <vector>
//#include<D:/ggggg/vcpkg/packages/nlohmann-json_x64-windows/include/nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
#define ll long long
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ld long double
#define vi vector<ll>

string userfilepath ="C:/Users/user/CLionProjects/ds/users.json";
string contactsfilepath = "C:/Users/user/CLionProjects/ds/contact.json";



struct Node {
    string id;
    string name;
    string pass;
    vector<string> friends;
    stack<string> messages;
};
int main() {
    ifstream file(userfilepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open "<<userfilepath<<"\n";
        return 1;
    }

    json j;
    file >> j;


    vector<User>& users = User::users;

    for (json u : j["users"])
    {
        if (u.contains("ID") && u["ID"].is_string() &&
         u.contains("username") && u["username"].is_string() &&
         u.contains("password") && u["password"].is_string()) {

            User user(u["ID"], u["username"], u["password"]);
            users.push_back(user);
         } else {
             cerr << "Invalid user entry skipped in JSON.\n";
         }
    }
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
            bool registered = false;
            for (auto u : users)
            {
                if (u.getUsername() == uname)
                {
                    cout<< "user already registered.";
                    registered = true ;
                    break;
                }
            }

            if (!registered)
            {
                string id = "U" + to_string(users.size() + 1);
                User newUser(id, uname, pwd);
                users.push_back(newUser);

                json usersarr;

                ifstream fileread(userfilepath);

                if (!fileread.is_open())
                {
                    std::cerr << "Failed to open "<<userfilepath<<"\n";
                    return 1;
                }

                fileread >> usersarr;

                json tempuser = {
                    {"ID", id},
                    {"username", uname},
                    {"password", pwd}
                };
                usersarr["users"].push_back(tempuser);

                ofstream filewrite(userfilepath);
                if (!fileread.is_open())
                {
                    std::cerr << "Failed to open "<<userfilepath<<"\n";
                    return 1;
                }
                filewrite<<usersarr.dump(4);

                cout << "Registration successful.\n";
            }


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
                cout << "User not found.\n";
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

                    currentUser->addContact(receiverId);  // Rule: only add if messag
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

                    // add sender to receiver contact list
                    // json contactsArr;
                    // ifstream fileread(contactsfilepath);
                    // string senderID = currentUser->getId();
                    // fileread>>contactsArr;
                    // json newcontact ={{"id", senderID } ,{"chat",json::array()}};
                    // bool present =false;
                    // for (auto& user : contactsArr["user"]) {
                    //     if (user["id"] == receiverId) {
                    //         // check if sender has send before
                    //         for (auto& c: user["contacts"])
                    //         {
                    //             if (user["id"] == senderID)
                    //             {
                    //                 present = true;
                    //                 break;
                    //             }
                    //         }//if sent before add message to chats else add new contact
                    //         if (present)
                    //         {
                    //             for (auto& c: user["contacts"])
                    //             {
                    //                 if (user["id"] == senderID)
                    //                 {
                    //                     user["chat"].push_back(content);
                    //                 }
                    //             }
                    //             break;
                    //         }
                    //         user["contacts"].push_back(newcontact);
                    //         for (auto& c: user["contacts"])
                    //         {
                    //             if (user["id"] == senderID)
                    //             {
                    //                 user["chat"].push_back(content);
                    //             }
                    //         }
                    //         break;
                    //
                    //     }
                    // }
                    // ofstream filewrite(contactsfilepath);
                    // filewrite<<contactsArr.dump(4);
                    // fileread.close();
                    // filewrite.close();

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
        vector <Contact> sortedcontacts = currentUser->getSortedContacts();

        json contactList = json::array();
        for (const auto& contact : sortedcontacts) {
            contactList.push_back(contact.to_json());
        }

        json finalJson;
        finalJson["contact list"] = contactList;

        // Write to file
        ofstream outFile("contact.json");
        outFile << finalJson.dump(4); // Pretty print with 4-space indentation
        outFile.close();

    }

    // json contactobj;
    // json contactarray = {{"contact list"}, json::array()};
    // for (int i =0; i<currentUser->getSortedContacts().size(); i++)
    // {
    //     contactobj={{"contact ID", sortedcontacts[i].contactID},
    //             {"messages", json::array()}};
    //     json messageobj;
    //     for (int j =0; j < sortedcontacts[i].messages.size();j++)
    //     {
    //         messageobj= {
    //             {"senderid", sortedcontacts[i].messages[j].senderID},
    //                 {"receiverid", sortedcontacts[i].messages[j].receiverID},
    //                 {"content", sortedcontacts[i].messages[j].content}};
    //         contactobj["messages"][j].push_back(messageobj);
    //     }
    //     contactarray["contact list"].push_back(contactobj);
    //
    // }
    // ofstream fileContact(contactsfilepath);
    // fileContact << contactarray;
    // fileContact.close();


    return 0;
}

