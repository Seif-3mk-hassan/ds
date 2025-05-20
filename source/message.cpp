#include "Message.h"
#include "nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

Message::Message() : messageID(""), senderID(""), receiverID(""), content("") {}

Message::Message(const string& ID,const string& sender, const string& receiver, const string& content)
: messageID(ID),senderID(sender), receiverID(receiver), content(content) {}

bool Message::isFavorite() {
    return false;  // You can implement this logic as needed
}

string Message::getSenderId() const {
    return senderID;
}

string Message::getReceiverId() const {
    return receiverID;
}

string Message::getContent() const {
    return content;
}