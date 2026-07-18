#include "student.h"
#include "../announcement/announcement.h"


namespace fs = std::filesystem;

string pickfile(){

    string result;

    FILE* pipe = popen(
        "zenity --file-selection --title='Select Assignment File'",     //using zenity fedora package
        "r"
    );

    if(!pipe){
        return "";
    }

    char buffer[256];   //temp waiting area

    while(fgets(buffer, sizeof(buffer), pipe) != NULL){
        result += buffer;
    }

    pclose(pipe);

    // remove newline
    if(!result.empty() && result[result.length()-1] == '\n'){
        result.erase(result.length()-1);        //new line rmoved
    }

    return result;
}

void student::showfiles(){
    cout << "\n===== AVAILABLE FILES =====\n";

    int index = 1;
    for (auto &file : fs::directory_iterator("submission")) {
        cout << index << ". " << file.path().filename().string() << endl;
        index++;
    }
}


student::student(string u, string p) : User(u,p,"student") {}

void student::menu() {
    // cout << "\n========= STUDENT MENU =========\n";
    int ch;

    while(true){

        cout << "\n===========STUDENT MENU===========\n";
        cout << "0. View Announcement\n";
        cout << "1. View Available Courses\n";
        cout << "2. Enroll in Course\n";
        cout << "3. View My Courses\n";
        cout << "4. View Assignments\n";
        cout << "5. Submit Assignment\n";
        cout << "6. View Marks and Feedback\n";
        cout << "7. Ask Query: \n";
        cout << "8. View Answer: \n";
        cout <<" 9. Log out: \n";
        cin >> ch;

        if(ch==0){
            announcement::viewstd(username);
        }
        else 
        if(ch==1){
            viewcourse();
        }else if(ch==2){
            enrollcourse();
        }else if(ch==3){
            viewmycourse();
        }else if(ch==4){
            viewassign();
        }
        else if(ch==5){
            submitassign();
            
        }else if(ch==6){
            viewresult();
        }else if(ch==7){
            askquery();
        }else if(ch==8){
            viewans();
        }else if(ch==9){
            cout<<"Logging out...\n";
            break;
        }else
        {
            cout<<"Invalid CHoice:: ";
            continue;
        }

    }



}

void student::viewcourse(){

    ifstream file("data/course.txt");

    string line;

    cout << "\n===== AVAILABLE COURSES =====\n";

    while(getline(file, line)){

        string id, name, teacher;

        stringstream ss(line);

        // PIPE FORMAT PARSING

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, teacher, '|');

        cout << id << " | " << name << " | " << teacher << endl;
    }

    file.close();
}
void student::viewmycourse(){

    ifstream file("data/enrollments.txt");

    string line;

    cout << "====== MY COURSES ======\n";

    while(getline(file, line)){

        string user, course;

        stringstream ss(line);


        getline(ss, user, '|');
        getline(ss, course, '|');

        if(user == username){

            cout << course << endl;
        }
    }

    file.close();
}

void student::enrollcourse(){

    string courseid;

    cout<<"Enter Coures ID: ";
    getline(cin>>ws,courseid);

    ifstream file("data/enrollments.txt");

    string line;
    bool already = false;

    // fIX:
    //  USING PIPE PARSING

    while(getline(file, line)){

        string usr, course;

        stringstream ss(line);

        getline(ss, usr, '|');
        getline(ss, course, '|');

        if(usr == username && course == courseid){

            already = true;
            break;
        }
    }

    file.close();

    if(already){

        cout << "Already enrolled\n";
        return;
    }

    ofstream out("data/enrollments.txt",ios::app);


    out << username << "|" << courseid << endl;

    cout<<"Course Enrolled Successfully\n";
}



void student::viewassign(){

    ifstream enroll("data/enrollments.txt");
    ifstream assign("data/assignments.txt");

    string line;

    vector<string> mycourse;


    while(getline(enroll, line)){

        string user, courseid;

        stringstream ss(line);

        getline(ss, user, '|');
        getline(ss, courseid, '|');

        if(user == username){

            mycourse.push_back(courseid);
        }
    }

    if(mycourse.empty()){

        cout << "No enrolled courses\n";
        return;
    }

    cout << "\n======= AVAILABLE ASSIGNMENTS =======\n";

    bool found = false;


    while(getline(assign, line)){

        string cid, title;

        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, title, '|');

        for(int i=0; i<mycourse.size(); i++){

            if(cid == mycourse[i]){

                cout << cid << " | " << title << endl;

                found = true;

                break;
            }
        }
    }

    if(!found){

        cout << "No assignments available\n";
    }

    enroll.close();
    assign.close();
}

// void student::submitassign(){
//     string courseid, assign, file;

//     cout<<"ENter Course ID: ";
//     getline(cin>>ws, courseid);
//     cout<<"ENter Assignment Name: ";
//     getline(cin>>ws, assign);
//     cout<<"ENter File Name: ";
//     getline(cin>>ws, file);
    
//     ifstream filein("data/submission.txt");

//     string usrname,cid,aname,fname;
//     float maxplag=0;
//     float oldplag;

//     while(filein >> usrname >> cid >> aname >> fname >> oldplag){
//         if(cid==courseid && aname==assign){
//             float score=plageng::checkpleg(file,fname);
//             if(score>maxplag){
//                 maxplag=score;
//             }
//         }
//     }



//     ofstream out("data/submission.txt",ios::app);


//     out << username << " " << courseid << " " << assign << " " << file << maxplag<< endl;

//     cout<<"Submitted Sucessfully: ";
//     cout << "\nPlagiarism Score: " << maxplag << "%\n";


    
    
    
// }


//correct version
void student::submitassign(){

    string courseid, assign;

    cout << "Enter Course ID: ";
    getline(cin >> ws, courseid);

    cout << "Enter Assignment Name: ";
    getline(cin >> ws, assign);


    cout << "Opening File Picker...\n";
    string fp = pickfile();     //using system file picker to select file

    if(fp == ""){
        cout << "No file selected!\n";
        return;
    }


cout << "Selected File: " << fp << endl;

    // checking if file exists
    ifstream check(fp);

    if(!check){
        cout << "File does not exist!\n";
        return;
    }

    check.close();

    string extension = fs::path(fp).extension().string();
     for (char &c : assign) {
        if (c == ' ') 
        c = '_';
    }

    string newfile = username + "_" + assign + "_" + courseid + extension;
    string newpath = "submission/" + newfile;

        // copy file into LMS system folder

        //exception handling
    try {
        fs::copy(fp, newpath, fs::copy_options::overwrite_existing);
    }
    catch (...) {
        cout << "Error copying file into submissions folder!\n";
        return;
    }

    // plagiarism checking
    ifstream filein("data/submission.txt");

    string line;

    float maxplag = 0;

    while(getline(filein, line)){

        string usr, cid, aname, oldpath, plag;

        stringstream ss(line);

        getline(ss, usr, '|');
        getline(ss, cid, '|');
        getline(ss, aname, '|');
        getline(ss, oldpath, '|');
        getline(ss, plag, '|');

        // same course + same assignment
        if(cid == courseid && aname == assign){

            float score = plageng::checkpleg(fp, oldpath);

            if(score > maxplag){
                maxplag = score;
            }
        }
    }

    filein.close();

    // save submission
    ofstream out("data/submission.txt", ios::app);

// STORE LMS FILE PATH NOT ORIGINAL PATH

    out << username << "|"
        << courseid << "|"
        << assign << "|"
        << newpath << "|"
        << maxplag << "||" << endl;

    out.close();

    cout << "\nAssignment Submitted Successfully!\n";
    cout << "Stored File: " << newfile << endl;
    cout << "Plagiarism Score: " << maxplag << "%\n";

}

void student::viewresult() {
    ifstream file("data/submission.txt");
    if (!file) {
        cout << "Cannot open file\n";
        return;
    }

    cout << "\n======= MY RESULTS =======\n";

    vector<string> seenAssignments;
    string line;

    while (getline(file, line)) {
        // Parse current line
        string studentID, courseID, assignment, filePath, plagiarism, marks, feedback;
        stringstream ss(line);
        getline(ss, studentID,  '|');
        getline(ss, courseID,   '|');
        getline(ss, assignment, '|');
        getline(ss, filePath,   '|');
        getline(ss, plagiarism, '|');
        getline(ss, marks,      '|');
        getline(ss, feedback,   '|');

        // Skip ungraded lines (marks field is empty)
        if (marks.empty()) continue;

        // Skip if we already processed this assignment
        bool alreadySeen = false;
        for (string& a : seenAssignments) {
            if (a == assignment) {
                alreadySeen = true;
                break;
            }
        }
        if (alreadySeen) continue;
        seenAssignments.push_back(assignment);

        // Go through the whole file to collect stats for this assignment
        float myMarks     = -1;
        string myFeedback = "";
        float highest     = -1;
        float lowest      = 9999;
        float total       = 0;
        int   count       = 0;

        file.clear();
        file.seekg(0);

        while (getline(file, line)) {
            string sID, cID, asgn, fp, plag, mrk, fb;
            stringstream ss2(line);
            getline(ss2, sID,  '|');
            getline(ss2, cID,  '|');
            getline(ss2, asgn, '|');
            getline(ss2, fp,   '|');
            getline(ss2, plag, '|');
            getline(ss2, mrk,  '|');
            getline(ss2, fb,   '|');

            // Skip ungraded or wrong assignment
            if (asgn != assignment || mrk.empty()) continue;

            float markVal = stof(mrk);
            total += markVal;
            count++;

            if (markVal > highest) highest = markVal;
            if (markVal < lowest)  lowest  = markVal;

            if (sID == username) {
                myMarks    = markVal;
                myFeedback = fb;
            }
        }

        // Print this student's result
        cout << "\n=================================\n";
        cout << "ASSIGNMENT: " << assignment << "\n";
        cout << "=================================\n";

        if (myMarks != -1) {
            cout << "\n--- YOUR RESULT ---\n";
            cout << "Marks:    " << myMarks    << "\n";
            cout << "Feedback: " << myFeedback << "\n";
        } else {
            cout << "\nNo submission found for you\n";
        }

        // Print class statistics
        if (count > 0) {
            cout << "\n--- CLASS STATISTICS ---\n";
            cout << "Highest Marks: " << highest         << "\n";
            cout << "Lowest Marks:  " << lowest          << "\n";
            cout << "Average Marks: " << (total / count) << "\n";
        }

        cout << "=================================\n";

        file.clear();
        file.seekg(0);
    }

    file.close();
}

void student::askquery(){

    string cid,question;
    cout<<"Enter Course ID: \n";
    getline(cin>>ws,cid);

    cout<<"Ask your Question: \n";
    getline(cin>>ws,question);


    ofstream out("data/query.txt",ios::app);

    out<<username<<"|"<<cid<<"|"<<question<<"|"<<"pending"<<endl;

    out.close();

    cout << "\nQuery Submitted Successfully!\n";


}


void student::viewans(){

    ifstream file("data/query.txt");

    string line;

    cout<<"==== My Queries ===="<<endl;

    while(getline(file,line)){
        string std,courseid, question, answer;

        stringstream ss(line);
        getline(ss, std, '|');
        getline(ss, courseid, '|');
        getline(ss, question, '|');
        getline(ss, answer, '|');

        if(std==username){

            cout << "\nCourse: " << courseid << endl;

            cout << "Question: " << question << endl;

            cout << "Answer: " << answer << endl;

        }
    }

    file.close();
    
}



