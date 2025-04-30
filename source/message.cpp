#include "Message.h"
#include <string>
Message::Message(){
     messageID = "";
     senderID 	= "";
     receiverID = "";
     content = "";
}

Message::Message(string& id, string& sender, string& text)
          : messageID(id), senderID(sender), content(text) {}
// Getters
string Message::getSenderId() const { return senderID; }


