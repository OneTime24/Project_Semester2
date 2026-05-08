#include "plagiarism.h"

// To open the file
int check_f(char *fn) {
    FILE *f = fopen(fn, "r");           //open the passedfile
    if (!f){        //if failed to open the file
    return 0;
    }
    fseek(f, 0, SEEK_END);              // move the cursor to the end of file or string
    long sz = ftell(f);         //tells us the location of the cursor or inshort size of the string or file
    fclose(f);
    if (sz>0){
    return 1;           //return 1 if succesfull read
    }       
    return 0;
}

// convert pdf or docx
void to_txt(char *s,char *d) {
    //xpdf || docxtxt
    char cmd[512];
    int ret = -1;       

    // simple check for extension
    if (strstr(s, ".pdf")) {
        // command to run pdftotext
        #ifdef _WIN32           //If OS is windows
            sprintf(cmd, "pdftotext \"%s\" \"%s\" > NUL 2>&1", s, d);           //write this into cmd/console
        #else
                                        //If OS is linux
            sprintf(cmd, "pdftotext \"%s\" \"%s\" > /dev/null 2>&1", s, d);         //write this into cmd/console
        #endif      

        ret = system(cmd);          //run the cmd/console command into system, it will return 0 if succesfull operation
        
        if (ret != 0 || !check_f(d)) {
            printf("Error: PDF convert fail for %s\nPlease Install pdf2txt tool manually and add it to system environmental path\n", s);
        }
    }
    else if (strstr(s, ".docx")) {      // similarly if file type is docx
        #ifdef _WIN32               // if windows
            sprintf(cmd, "docx2txt \"%s\" \"%s\" > NUL 2>&1", s, d);            //write this in cmd 
        #else
            sprintf(cmd, "docx2txt < \"%s\" > \"%s\" 2> /dev/null", s, d);          //if linux write this
        #endif

        ret = system(cmd);      //pass the cmd string to cmd    
        
        if (ret != 0 || !check_f(d)) {              //checking if conversion was succesfull or not
             printf("Error: DOCX convert fail for %s\nPlease Install docx2txt tool manually and add it to system environmental path", s);
        }
    }
}


char* read_f(char *fname) {         // main read function
    char tmp[] = "temp_conv.txt";           // a temp variable to store the converted txt
    char *target = fname;
    int conv = 0;       
    
  
    if (strstr(fname, ".pdf") || strstr(fname, ".docx")) {                // check if we need conversion
        remove(tmp);                        // delete old temp
        to_txt(fname, tmp);         //passing the fname and tmp to convert to txt
        
        if (check_f(tmp)) {         //checking if the conversion was successful or not
            target = tmp;               //now target points to converted text
            conv = 1;       //a flag
        } else {
            return NULL; 
        }
    }

    
    FILE *fp = fopen(target, "r");          //a pointer that points to target which points to converted tezt

    if (!fp) {
        printf("Cannot open %s\n", target);         //to check if file opened or not
        return NULL;
    }
      
    fseek(fp, 0, SEEK_END);         //move the cursor to the end of file
    long l = ftell(fp);                     //ftell tells the locaiton of the cursor, since char so acutally size
    rewind(fp);             //move back cursor to the start
    

    char *buf = (char*)malloc(l + 10);          // Simple malloc function just to be safe for memory lackage
    fread(buf, 1, l, fp);
    buf[l] = '\0';
    
    fclose(fp);
    
    if (conv) {
        remove(tmp);            //remove the tmp file
    }
    
    return buf;         // return the converted file
}