

#ifndef ANNOUNCEMENT_H
#define ANNOUNCEMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class announcement{
    public:
        static void addglobal(string sender, string msg);
        static void addlocal(string sender,string courseid, string msg);

        static void viewstd(string username);

        static void viewteach(string teacher);
};


#endif