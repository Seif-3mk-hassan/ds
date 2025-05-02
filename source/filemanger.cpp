//
// Created by user on 4/30/2025.
//

#include "filemanger.h"
#include <fstream>
void filemanger::addToJsonfile(nlohmann::json jsonObj, const string& jsonFile)
{
  ofstream file(jsonFile);
  file<<jsonObj;
}

nlohmann::json filemanger::Readfromjson(const string & jsonfile)
{
    ifstream file(jsonfile);
    nlohmann::json jsonObj = nlohmann::json::parse(file);
    return jsonObj;
}
