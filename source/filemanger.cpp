//
// Created by user on 4/30/2025.
//

#include "filemanger.h"
#include <fstream>
#include<iostream>
// void filemanger::addToJsonfile(nlohmann::json jsonObj, const string& jsonFile)
// {
//   ofstream file(jsonFile);
//   file<<jsonObj;
// }

// nlohmann::json filemanger::Readfromjson(const string & jsonfile)
// {
//     ifstream file(jsonfile);
//     nlohmann::json jsonObj = nlohmann::json::parse(file);
//     return jsonObj;
// }

// ... existing code ...
// nlohmann::json filemanger::Readfromjson(const string & jsonfile)
// {
//   try {
//     ifstream file(jsonfile);
//     if (!file.is_open()) {
//       // If file doesn't exist, return empty JSON object
//       return nlohmann::json::object();
//     }
//     // Read the entire file into a string
//     string content((istreambuf_iterator<char>(file)),
//                    istreambuf_iterator<char>());
//     if (content.empty()) {
//       // If file is empty, return empty JSON object
//       return nlohmann::json::object();
//     }
//     return nlohmann::json::parse(content);
//   } catch (const nlohmann::json::parse_error& e) {
//     // Handle JSON parsing errors
//     cout << "JSON parsing error: " << e.what() << endl;
//     return nlohmann::json::object();
//   } catch (const exception& e) {
//     // Handle other errors
//     cout << "Error reading JSON file: " << e.what() << endl;
//     return nlohmann::json::object();
//   }
// }
// ... existing code ...
