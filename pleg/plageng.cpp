
#include "../pleg/plageng.h"

float plageng::checkpleg(string file1,string file2){
    char* data1 = read_f(const_cast<char*>(file1.c_str()));
    char* data2 = read_f(const_cast<char*>(file2.c_str()));

    if(!data1 || !data2){
        if(!data1){
            free(data1);
        }
        if(!data2){
            free(data2);
        }
        return 0;
    }

    char p1[10000],p2[10000];

    clean_str(data1,p1);
    clean_str(data2,p2);

    float result=compare_txt(p1,p2);

    free(data1);
    free(data2);

    return result;
}