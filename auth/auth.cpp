#include "auth.h"

void auth::init(){

    ifstream file("data/users.txt");

    // ✅ FIX:
    // Create default admin ONLY if file does not exist

    if(!file.is_open()){

        ofstream out("data/users.txt");

        if(!out){

            cout << "ERROR: Cannot create users.txt\n";
            return;
        }

        out << "admin admin123 admin\n";

        out.close();
    }
}

User* auth::login(){

    string u, p;

    cout << "\nEnter Username: \n";
    getline(cin >> ws, u);

    cout << "Enter Password: \n";
    getline(cin >> ws, p);

    ifstream file("data/users.txt");

    // ✅ FIX:
    // REMOVED THIS WRONG LINE:
    // cout << "Default admin created\n";

    string fu, fp, fr;

    while(file >> fu >> fp >> fr){

        if(fu == u && fp == p){

            if(fr == "admin"){

                return new admin(fu, fp);
            }

            else if(fr == "teacher"){

                return new teacher(fu, fp);
            }

            else if(fr == "student"){

                return new student(fu, fp);
            }
        }
    }

    cout << "Invalid Login\n";

    return NULL;
}

// add new user

void auth::adduser(string u, string p, string r){

    ofstream out("data/users.txt", ios::app);

    // ✅ FIX:
    // CONSISTENT SPACE FORMAT

    out << u << " "
        << p << " "
        << r << endl;

    out.close();

    cout << "User Added\n";
}