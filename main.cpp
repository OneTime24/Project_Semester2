#include <iostream>
#include "auth/auth.h"
#include <cstdio>

using namespace std;

//  FOR PLAGIARISM ENGINE
FILE* fp_rep = NULL;

int main(){

    auth::init();

    while(true){

        User* u = auth::login();           

        if(!u){

            cout << "Login failed. Try again.\n";
            continue;
        }

        u->menu();

        delete u;
    }

    return 0;
}