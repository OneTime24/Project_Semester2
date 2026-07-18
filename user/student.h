#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "../pleg/plageng.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <memory>
#include <array>

class student : public User {           //inheritence
public:
    student(string u, string p);
    void menu();

private:

    void viewcourse();
    void enrollcourse();
    void viewmycourse();
    void viewassign();
    void submitassign();
    void showfiles();
    void viewresult();
    void askquery();
    void viewans();


};



#endif