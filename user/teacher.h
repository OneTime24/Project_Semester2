#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"

class teacher : public User {
public:
    teacher(string u, string p);
    void menu();

private:
    void viewcourse();
    void createassignment();
    void viewassignment();
    void viewsubmission();

    void viewq();
    void ansq();
    

};

#endif