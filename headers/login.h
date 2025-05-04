//
// Created by user on 4/21/2025.
//
#pragma once
#include "system_manger.h"
#include "user.h"

class login : public system_manager {

public:
    static void registerr();
    static User is_logged_in();
    static void mainMenu();
    static void saveTofile(User);

};


