
#ifndef AUTH_H
#define AUTH_H


#include <iostream>
#include <fstream>
#include "../user/admin.h"
#include "../user/teacher.h"
#include "../user/student.h"
#include "../user/User.h"

using namespace std;

class auth{
    public:

    static void init();
    static User* login();
    static void adduser(string u, string p, string r);
};

#endif