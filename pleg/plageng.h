
#ifndef PLAGENG_H
#define PLAGENG_H


#include <iostream>

using namespace std;

extern "C"{

    #include "plagiarism.h"

}

class plageng{

    public:
    static float checkpleg(string file1,string file2);


};





#endif