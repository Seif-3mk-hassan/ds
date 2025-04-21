#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
using namespace std;
class Contact {
    public:
    Contact();
    private:
    string contactID;
    Message messages;
    int messageCount;
    void addMessage();
};