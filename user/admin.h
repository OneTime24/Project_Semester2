#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class admin : public User {
public:
    admin(string u, string p);
    void menu();

    private:
    void adduser();
    void viewuser();
    void deluser();
    void addcourse();
    void viewcourse();
    void assignteacher();

};

#endif