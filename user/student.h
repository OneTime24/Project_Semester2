#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "../pleg/plageng.h"

class student : public User {
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