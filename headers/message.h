#include <iostream>
#include <string>
using namespace std;
    class Message {
        string messageID;
        string senderID;
        string receiverID;
        string content;
        //timestamp time;
        public:
        Message();
        bool isFavorite();
    };
    