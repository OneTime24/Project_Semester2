#include "admin.h"
#include "../auth/auth.h"
#include "../announcement/announcement.h"

#include <sstream>   // ✅ REQUIRED FOR stringstream
#include <cstdio>

admin::admin(string u, string p) : User(u,p,"admin") {}

void admin::menu() {

    while(true){

        cout<<"\n0. Add Global Announcement\n";
        cout << "1. Add User\n";
        cout << "2. View Users\n";
        cout << "3. Delete User\n";
        cout << "4. Add Course\n";
        cout << "5. View Courses\n";
        cout << "6. Assign Teacher to Course\n";
        cout << "7. Logout\n";

        int ch;
        cin >> ch;

        if(ch==0){

            string msg;

            cout << "Enter global message: ";

            getline(cin >> ws, msg);

            announcement::addglobal("admin", msg);
        }

        else if (ch == 1)
            adduser();

        else if (ch == 2)
            viewuser();

        else if(ch==3)
            deluser();

        else if (ch == 4)
            addcourse();

        else if (ch == 5)
            viewcourse();

        else if (ch==6)
            assignteacher();

        else if(ch==7){

            cout<<"Logging Out...\n";
            break;
        }

        else{

            cout<<"Invalid Selection\n";
        }
    }
}

void admin::adduser(){

    string u,p,r;

    cout<<"Enter Username: ";
    getline(cin>>ws,u);

    cout<<"Enter Password: ";
    getline(cin>>ws,p);

    cout<<"Enter Role: ";
    getline(cin>>ws,r);

    auth::adduser(u,p,r);

    cout<<"User Added Successfully\n";
}

void admin::viewuser(){

    ifstream file("data/users.txt");

    if (!file){

        cout<<"Cannot Open Users File\n";
        return;
    }

    string u,p,r;

    cout << "\n===== USERS LIST =====\n";

    while (file >> u >> p >> r){

        cout << "Username: " << u
             << " | Password: " << p
             << " | Role: " << r << endl;
    }

    file.close();
}

void admin::deluser(){

    string target;

    cout<<"Enter Username to delete: ";

    getline(cin>>ws,target);

    ifstream file("data/users.txt");
    ofstream temp("data/temp.txt");

    string u,p,r;

    bool found=false;

    while(file >> u >> p >> r){

        if(u != target){

            temp << u << " "
                 << p << " "
                 << r << endl;
        }

        else{

            found = true;
        }
    }

    file.close();
    temp.close();

    remove("data/users.txt");
    rename("data/temp.txt","data/users.txt");

    if(found)
        cout<<"User Deleted Successfully\n";

    else
        cout<<"User Not Found\n";
}

void admin::addcourse(){

    string id, name, teacher;

    cout << "Enter course ID: ";
    getline(cin >> ws, id);

    cout << "Enter course name: ";
    getline(cin >> ws, name);

    cout << "Enter course Teacher: ";
    getline(cin >> ws, teacher);

    ofstream out("data/course.txt", ios::app);

    // ✅ CONSISTENT FORMAT
    out << id << "|" << name << "|" << teacher << endl;

    out.close();

    cout << "Course added successfully\n";
}

void admin::viewcourse(){

    ifstream file("data/course.txt");

    if(!file){

        cout << "Cannot open course file\n";
        return;
    }

    cout << "\n===== COURSES =====\n";

    string line;

    while(getline(file, line)){

        string id, name, teacher;

        stringstream ss(line);

        // ✅ FIXED PIPE PARSING
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, teacher, '|');

        cout << id
             << " | "
             << name
             << " | "
             << teacher << endl;
    }

    file.close();
}

void admin::assignteacher(){

    string courseid;
    string newteacher;

    cout << "Enter Course ID: ";
    getline(cin >> ws, courseid);

    cout << "Enter Teacher Username: ";
    getline(cin >> ws, newteacher);

    ifstream file("data/course.txt");
    ofstream temp("data/temp.txt");

    string line;

    bool found = false;

    while(getline(file, line)){

        string id, name, teacher;

        stringstream ss(line);

        // ✅ FIXED PIPE PARSING
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, teacher, '|');

        if(id == courseid){

            temp << id
                 << "|"
                 << name
                 << "|"
                 << newteacher
                 << endl;

            found = true;
        }

        else{

            temp << id
                 << "|"
                 << name
                 << "|"
                 << teacher
                 << endl;
        }
    }

    file.close();
    temp.close();

    remove("data/course.txt");
    rename("data/temp.txt", "data/course.txt");

    if(found)
        cout << "Teacher Assigned Successfully\n";

    else
        cout << "Course Not Found\n";
}