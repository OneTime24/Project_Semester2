

#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
using namespace std;

class User{
    protected:
    string username;
    string password;
    string role;

    public:
    User(string u="",string p="",string r="");

    string getusername();
    string getrole();

    virtual void menu()=0;

};

#endif