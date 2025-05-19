#pragma once
#include <string>
#include <vector>
#include "Message.h"

class Contact {
private:
    std::string contactID;
    std::vector<Message> messages;

public:
    Contact();  // Default constructor
    Contact(std::string contactID);  // Parameterized constructor
    std::string getId() const;  // Getter for contactID
    int getMessageCount() const;  // Return the number of messages
    vector<Message>& getMessages();                 // for modifying access
    const vector<Message>& getMessages() const;     // for read-only access
    
    void addMessage(const Message& message);  // Add a message to the contact
};
