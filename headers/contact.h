#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
using namespace std;
class Contact {
    public:
    Contact();
    Contact(const string& id, string& username);
    public:
    string contactID;
    Message messages;
    int messageCount;
    void addMessage(Message);
    int getMessageCount();
};