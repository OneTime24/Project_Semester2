
#include "course.h"

course::course(string id, string name, string teacher) : courseid(id), coursename(name), teachername(teacher) {}

string course::getid() {
    return courseid;
}

string course::getname() {
    return coursename;
}

string course::getteacher() {
    return teachername;
}

void course::display() {
    cout << "Course ID: " << courseid << endl;
    cout << "Course Name: " << coursename << endl;
    cout << "Teacher: " << teachername << endl;
}