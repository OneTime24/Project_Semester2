
#include "User.h"

User::User(string u,string p,string r):username(u),password(p),role(r){}


string User::getusername(){
    return username;
}

string User::getrole(){
    return role;
}
