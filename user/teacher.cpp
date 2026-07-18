#include "teacher.h"
#include "../announcement/announcement.h"

#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

teacher::teacher(string u, string p) : User(u,p,"teacher") {}           //constructor

void teacher::menu() {

    int ch;

    while(true){

        cout << "\n===========TEACHER MENU===========\n";

        cout << "\n-1. Create Course Announcement\n";
        cout << "0. View Global Announcement\n";
        cout << "1. View My Courses\n";
        cout << "2. Create Assignment\n";
        cout << "3. View Assignments\n";
        cout << "4. View Submissions\n";
        cout << "5. View Queries\n";
        cout << "6. Answer Queries\n";
        cout << "7. Log out\n";
        cout << "Enter choice: ";

        cin >> ch;

        if(ch == -1){

            string course, msg;

            cout << "Course ID: ";
            getline(cin >> ws, course);

            cout << "Message: ";
            getline(cin >> ws, msg);

            announcement::addlocal(username, course, msg);
        }

        else if(ch == 0){

            announcement::viewteach(username);
        }

        else if(ch == 1){

            viewcourse();
        }

        else if(ch == 2){

            createassignment();
        }

        else if(ch == 3){

            viewassignment();
        }

        else if(ch == 4){

            viewsubmission();
        }

        else if(ch == 5){

            viewq();
        }

        else if(ch == 6){

            ansq();
        }

        else if(ch == 7){

            cout << "Logging out...\n";
            break;
        }

        else{

            cout << "Invalid Option\n";
        }
    }
}

void teacher::viewcourse(){

    ifstream file("data/course.txt");

    string line;

    cout << "My Courses:\n";

    while(getline(file, line)){

        string id, name, teachern;

        stringstream ss(line);

        // ✅ FIXED PIPE PARSING
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, teachern, '|');

        if(teachern == username){

            cout << id << " " << name << endl;
        }
    }

    file.close();
}

void teacher::createassignment(){

    string title, courseid;

    bool valid = false;

    cout << "Enter Course ID: ";

    getline(cin >> ws, courseid);

    ifstream file("data/course.txt");

    string line;

    while(getline(file, line)){

        string id, name, tname;

        stringstream ss(line);

        // IXED PIPE PARSING
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, tname, '|');

        if(id == courseid && tname == username){

            valid = true;
            break;
        }
    }

    file.close();

    if(!valid){

        cout << "Invalid Course or not assigned to you\n";
        return;
    }

    cout << "Enter Assignment Details: ";

    getline(cin >> ws, title);

    ofstream out("data/assignments.txt", ios::app);

    out << courseid << "|" << title << endl;

    out.close();

    cout << "Assignment created Successfully!\n";
}

void teacher::viewassignment(){

    ifstream course("data/course.txt");
    ifstream assign("data/assignments.txt");

    vector<string> mycourses;           //to store courses dynamically

    string line;

    while(getline(course, line)){

        string cid, cname, tname;

        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, cname, '|');
        getline(ss, tname, '|');

        if(tname == username){

            mycourses.push_back(cid);       //add at the end of the array
        }
    }

    cout << "\n======= View Assignments =======\n";

    while(getline(assign, line)){

        string aid, title;

        stringstream ss(line);

        getline(ss, aid, '|');
        getline(ss, title, '|');

        for(int i=0; i<mycourses.size(); i++){

            if(aid == mycourses[i]){

                cout << aid << " | " << title << endl;
            }
        }
    }

    course.close();
    assign.close();
}

void teacher::viewsubmission(){

    ifstream sub("data/submission.txt");
    ifstream course("data/course.txt");

    vector<string> mycourse;        //dynamic array to store courses

    string line;

    while(getline(course, line)){

        string cid, cname, tname;

        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, cname, '|');
        getline(ss, tname, '|');

        if(tname == username){

            mycourse.push_back(cid);        //add at the end of the array
        }
    }

    course.close();

    if(mycourse.empty()){

        cout << "No Courses are assigned\n";
        return;
    }

    vector<string> allLines;

    int count = 1;

    cout << "\n======= STUDENT SUBMISSIONS =======\n";

    while(getline(sub, line)){

        string student, courseid, assign, filepath, plag, marks, feedback;

        stringstream ss(line);

        getline(ss, student, '|');
        getline(ss, courseid, '|');
        getline(ss, assign, '|');
        getline(ss, filepath, '|');
        getline(ss, plag, '|');
        getline(ss, marks, '|');
        getline(ss, feedback, '|');

        for(int i=0; i<mycourse.size(); i++){       //loopinh through all courses

            if(courseid == mycourse[i]){    //if found

                cout << count << ". "
                     << student << " | "
                     << courseid << " | "
                     << plag << "% | Marks: "
                     << marks << endl;

                allLines.push_back(line);       //add the line at the end of the array

                count++;

                break;
            }
        }
    }

    sub.close();

    if(allLines.empty()){

        cout << "No submissions found!\n";
        return;
    }

    int choice;

    cout << "\nSelect Submission Number: ";
    cin >> choice;

    if(choice < 1 || choice > allLines.size()){

        cout << "Invalid choice!\n";
        return;
    }

    string selected = allLines[choice - 1];

    string student, courseid, assign, filepath, plag, marks, feedback;

    stringstream ss(selected);

    getline(ss, student, '|');
    getline(ss, courseid, '|');
    getline(ss, assign, '|');
    getline(ss, filepath, '|');
    getline(ss, plag, '|');
    getline(ss, marks, '|');
    getline(ss, feedback, '|');

    cout << "\nOpening File...\n";

    string command = "xdg-open \"" + filepath + "\"";       //opening  the file for linux

    system(command.c_str());        //returns const char pointer

    string newmarks;
    string newfeed;

    cout << "\nEnter Marks: ";
    getline(cin >> ws, newmarks);

    cout << "\nEnter Feedback: ";
    getline(cin >> ws, newfeed);

    ifstream fina("data/submission.txt");
    ofstream temp("data/temp.txt");

    while(getline(fina, line)){

        string s2,c2,a2,f2,p2,m2,fb2;

        stringstream sss(line);

        getline(sss, s2, '|');
        getline(sss, c2, '|');
        getline(sss, a2, '|');
        getline(sss, f2, '|');
        getline(sss, p2, '|');
        getline(sss, m2, '|');
        getline(sss, fb2, '|');

        if(
            s2 == student &&
            c2 == courseid &&
            a2 == assign &&
            f2 == filepath
        ){

            temp << s2 << "|"
                 << c2 << "|"
                 << a2 << "|"
                 << f2 << "|"
                 << p2 << "|"
                 << newmarks << "|"
                 << newfeed << endl;
        }

        else{

            temp << line << endl;
        }
    }

    fina.close();
    temp.close();

    remove("data/submission.txt");
    rename("data/temp.txt", "data/submission.txt");     //update the marks and rename it to previous onw also delete old one

    cout << "\nSubmission Checked Successfully!\n";
}

void teacher::viewq(){

    ifstream query("data/query.txt");
    ifstream course("data/course.txt");

    vector<string> mycourse;

    string line;

    while(getline(course, line)){

        string cid, cname, tname;

        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, cname, '|');
        getline(ss, tname, '|');

        if(tname == username){

            mycourse.push_back(cid);
        }
    }

    cout << "\n======= STUDENT QUERIES =======\n";

    while(getline(query, line)){

        string stden, cid, qs, ans;

        stringstream ss(line);

        getline(ss, stden, '|');
        getline(ss, cid, '|');
        getline(ss, qs, '|');
        getline(ss, ans, '|');

        for(int i=0; i<mycourse.size(); i++){

            if(cid == mycourse[i]){

                cout << "\nStudent: " << stden << endl;
                cout << "Course: " << cid << endl;
                cout << "Question: " << qs << endl;
                cout << "Answer: " << ans << endl;

                break;
            }
        }
    }

    query.close();
    course.close();
}

void teacher::ansq(){

    ifstream query("data/query.txt");
    ifstream course("data/course.txt");

    vector<string> mycourse;

    string line;

    while(getline(course, line)){

        string cid, cname, tname;

        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, cname, '|');
        getline(ss, tname, '|');

        if(tname == username){

            mycourse.push_back(cid);
        }
    }

    vector<string> allLines;

    int cnt = 1;

    cout << "\n======= PENDING QUERIES =======\n";

    while(getline(query, line)){

        string stden, cid2, qs, ans;

        stringstream ss(line);

        // FIXED MISSING STUDENT PARSING BUG
        getline(ss, stden, '|');

        getline(ss, cid2, '|');
        getline(ss, qs, '|');
        getline(ss, ans, '|');

        for(int i=0; i<mycourse.size(); i++){

            if(cid2 == mycourse[i] && ans == "pending"){

                cout << cnt << ". "
                     << stden << " | "
                     << cid2 << " | "
                     << qs << endl;

                allLines.push_back(line);

                cnt++;

                break;
            }
        }
    }

    query.close();

    if(allLines.empty()){

        cout << "\nNo pending queries\n";
        return;
    }

    int ch;

    cout << "\nSelect Query Number: ";
    cin >> ch;

    if(ch < 1 || ch > allLines.size()){

        cout << "Invalid Choice\n";
        return;
    }

    string teacherAnswer;

    cout << "Enter Answer: ";

    getline(cin >> ws, teacherAnswer);

    string slc = allLines[ch - 1];

    ifstream infile("data/query.txt");
    ofstream tmp("data/temp.txt");

    while(getline(infile, line)){

        if(line == slc){

            string student, courseid, question, oldAnswer;

            stringstream ss(line);

            getline(ss, student, '|');
            getline(ss, courseid, '|');
            getline(ss, question, '|');
            getline(ss, oldAnswer, '|');

            tmp << student << "|"
                << courseid << "|"
                << question << "|"
                << teacherAnswer << endl;
        }

        else{

            tmp << line << endl;
        }
    }

    infile.close();
    tmp.close();

    remove("data/query.txt");
    rename("data/temp.txt", "data/query.txt");

    cout << "\nQuery Answered Successfully!\n";
}