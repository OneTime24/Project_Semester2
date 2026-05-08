
#ifndef COURSE_H
#define COURSE_H

#include <iostream>
using namespace std;

class course{
    private:

    string courseid;
    string coursename;
    string teachername;

    public:

        course(string id="",string cn="",string tn="");

        string getid();
        string getname();
        string getteacher();

        void display();




};

#endif