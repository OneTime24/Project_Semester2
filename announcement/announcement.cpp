

#include "../announcement/announcement.h"


void announcement::addglobal(string sender, string message){
    
    ofstream out("data/announ.txt",ios::app);

    out << "GLOBAL|" << sender << "|ALL|" << message << endl;

    cout<<"\n Global Announcement Posted: \n";

}

void announcement::addlocal(string sender, string courseid, string message){
    
    ofstream out("data/announ.txt",ios::app);

    out << "COURSE|" << sender << "|" << courseid << "|" << message << endl;

    cout<<"\nCourse ANnoucnement Posted: \n";

}

void announcement::viewstd(string username){

    ifstream file("data/announ.txt");

    string line;

    cout << "\n======= ANNOUNCEMENTS =======\n";

    while(getline(file, line)){

        string type, sender, cid, msg;
        stringstream ss(line);

        getline(ss, type, '|');
        getline(ss, sender, '|');
        getline(ss, cid, '|');
        getline(ss, msg, '|');

        if(type == "GLOBAL"){
            cout << "::GLOBAL:: " << msg << endl;
        }

        else if(type == "COURSE"){

            ifstream enrol("data/enrollments.txt");

            string usr, course;
            bool found = false;

            // ✅ FIX: proper parsing (was broken before)
            while(enrol >> usr >> course){
                if(usr == username && course == cid){
                    found = true;
                    break;
                }
            }

            if(found){
                cout << "[" << cid << "] " << msg << endl;
            }
        }
    }
}


void announcement::viewteach(string teacher){

        ifstream file("data/announ.txt");

        cout<<"\n========== Announcements ==========\n";


        string line;

        while(getline(file,line)){
        string type, sender, courseid, msg;

        stringstream ss(line);

        getline(ss, type, '|');
        getline(ss, sender, '|');
        getline(ss, courseid, '|');
        getline(ss, msg, '|');

        if(type == "GLOBAL"){
            cout << ":: GLOBAL ::" << msg << endl;
        }

        if(type == "COURSE" && sender == teacher){
            cout << "[" << courseid << "] " << msg << endl;
        }


        
        }

        file.close();
}