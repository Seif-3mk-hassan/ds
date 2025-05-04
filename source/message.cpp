#include "Message.h"
#include "nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

Message::Message() : messageID(""), senderID(""), receiverID(""), content("") {}

bool Message::isFavorite() {
    return false; // Implement this based on your requirements
}

string Message::getSenderId() const {
    return senderID;
}

json Message::toJson() const {
    json j;
    j["messageID"] = messageID;
    j["senderID"] = senderID;
    j["receiverID"] = receiverID;
    j["content"] = content;
    return j;
}
