#include "Contact.h"
#include <iostream>
#include <vector>
#include <string>
#include "Message.h"
//#include <nlohmann/json.hpp>  

using namespace std;
//using json = nlohmann::json;


Contact::Contact() : contactID(""), messages() {}

Contact::Contact(string contactID) : contactID(contactID) {

}

std::string Contact::getId() const {
    return contactID;
}

int Contact::getMessageCount() const {
    return messages.size();
}

std::vector<Message>& Contact::getMessages() {  // Return a reference to the messages vector
    return messages;
}

void Contact::addMessage(const Message& message) {
    messages.push_back(message);
}
const vector<Message>& Contact::getMessages() const {
    return messages;
}
bool Contact::isHidden() const { return hidden; }
void Contact::setHidden(bool h) { hidden = h; }