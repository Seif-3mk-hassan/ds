#pragma once
#include <string>
#include <vector>
#include "Message.h"
#include <sstream>

class Contact {
private:
    std::string contactID;
    std::vector<Message> messages;
    bool hidden = false;
public:
    Contact();
    Contact(std::string contactID);
    std::string getId() const;
    int getMessageCount() const;
    vector<Message>& getMessages();
    const vector<Message>& getMessages() const;

    void addMessage(const Message& message);

    bool isHidden() const;
    void setHidden(bool h);  // Add a message to the contact
};
