#include <iostream>
#include <string>
using namespace std;
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
       
    };
    