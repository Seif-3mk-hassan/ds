// Message.h
#pragma once
#include <string>
using namespace std;

class Message {
public:

    string messageID;
    string senderID;
    string receiverID;
    string content;

    Message();  // Default constructor
    Message(const string& id,const string& sender, const string& receiver, const string& content);

    bool isFavorite();  // Stub for isFavorite
    string getSenderId() const;
    string getReceiverId() const;
    string getContent() const;
   
};
