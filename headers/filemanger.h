//
// Created by user on 4/30/2025.
//

#ifndef FILEMANGER_H
#define FILEMANGER_H
#include "nlohmann/json.hpp"
#include <string>
using namespace std;



class filemanger {

      public:
            void addToJsonfile(nlohmann::json jsonObj, const string& jsonFile);

            nlohmann::json Readfromjson(const string & jsonfile);


};



#endif //FILEMANGER_H
