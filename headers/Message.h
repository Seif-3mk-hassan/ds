#pragma once
#include <iostream>
#include <string>
#include "nlohmann//json.hpp"
using namespace std;
using json = nlohmann::json;

class Message {
    public:
    string messageID;
    string senderID;
    string receiverID;
    string content;
    //timestamp time;
    Message();
    bool isFavorite();
    string getSenderId() const;
    json toJson() const;
};
    