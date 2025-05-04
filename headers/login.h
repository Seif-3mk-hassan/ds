//
// Created by user on 4/21/2025.
//
#pragma once
#include "system_manger.h"
#include "user.h"

class login {

public:
     system_manager s;
     login(system_manager s){
          this->s=s;
     }
     void registerr();
     User is_logged_in();
     void mainMenu();
     void saveTofile(User);

};


