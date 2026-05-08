#include "plagiarism.h"

// clean text: lowercase and remove weird chars
void clean_str(char *s, char *d) {
    int i=0,j=0;
    while (s[i]!='\0') {
        char c=s[i];
        if (c>='A'&&c<='Z'){ 
            c = c + 32; // manual tolower
        }
        if((c >='a'&&c<= 'z') ||(c>='0'&&c<= '9') || c == ' '){
            d[j++] = c;         // store as it is 
        }else{ 
            d[j++] = ' ';       // if special characters, store ' '  instead of them
        }
        i++;            // move to the next character!
    }
    d[j] = '\0';            // add null character at the end.
    
    // fix spaces
    char temp[5000]; // temp buffer ! 
    int x=0, y=0;
    int sp=0;       //flag   
    // copying to temp first to handle spaces
    strcpy(temp, d);            //d preprocessed! Capitalized small, extra symbols ' '
    
    while (temp[x]!='\0') {             // loop till the end of the string
        if (temp[x]!=' ') {                     // while not space
            d[y++] = temp[x];   //store value of temp[x] into d[y++] position
            sp = 0;                 //flag
        } else {
            if (sp == 0) {                  // if space
                d[y++] = ' ';   // store a single space at the index
                sp = 1;         // change value of flag to 1 so that if there is anotehr space, it will ignore it
            }
        }
        x++;    // next charecter
    }
    if (y>0 && d[y-1] == ' ')       // if space at the end of file
    {
        y--;            
    }
    d[y] = '\0';                        //replace it by NULL
}

// text compare logic
float compare_txt(char *t1, char *t2) {
    // duplicating strings so strtok doesn't mess up original

//     char *c1 = malloc(strlen(t1) + 1);
    // strcpy(c1, t1);

//another method!!!!
    char *c1 = strdup(t1);          // strdup () ==>address     
    char *c2 = strdup(t2);
                                                //  Tokenization! Hello\0world\0blah\0blah
                                                        // Hello
                                                        // world
                                                        //blah

    char *toks1[1000];          // a pointer to each token
    int cnt1 = 0;   //flag
                
    char *p = strtok(c1, " ");          // space = \0||NULL

    while (p != NULL && cnt1 < 1000) {
        toks1[cnt1++] = p;      // each pointer points to a token
        p = strtok(NULL, " ");          // token the next word
    }
    
    char *toks2[1000];          // similarly tokenizing file 2
    int cnt2 = 0;
    
    p = strtok(c2, " ");
    while (p != NULL && cnt2 < 1000) {
        toks2[cnt2++] = p;
        p = strtok(NULL, " ");
    }
    

    // 3-gram logic
    
    int n=3;        // 3 sequence of words wil be compared      

    float ans=0;        // a variable to store the percentage
    
    if (cnt1>=n && cnt2>=n) {               //cnt is basically number of tokens
        int g1 = cnt1-n+1;          // 20 -3 +1 = 18        shows total number of 3 word sequence

        int g2 = cnt2-n+1;             //22 -3 +1=20    

        int match = 0;

        int used[1000] = {0}; // to mark matches
        
        for (int i=0; i<g1; i++) {
            // build phrase 1 (3 words)
            char ph1[100]; 

            sprintf(ph1, "%s %s %s", toks1[i], toks1[i+1], toks1[i+2]);
            
            for (int j=0; j<g2; j++) {
               if (used[j])                
                    continue;
                char ph2[100];          //build phrase 2 (3 words)
                sprintf(ph2, "%s %s %s", toks2[j], toks2[j+1], toks2[j+2]);
                            
                if (strcmp(ph1, ph2) == 0) {            //strcmp ph1 == ph2 return 0, strcmp ==>int: 0 equal, ph1<ph2 ==>negative   : ph1>ph2  ==>positive
                    match++;        //found a match
                  
                    if(fp_rep) 
                        fprintf(fp_rep, "  Found: \"%s\"\n", ph1);      //writing every match in report
                    break;
                }
            }
        }
        
            // DICE SIMILARITY FORMULA (V.IMP)
        ans = (2.0 * match) / (g1 + g2) * 100.0;
    }
    
    free(c1);       // free c1 and c2
    free(c2);
    return ans;
}

// remove comments
void rem_cmt(char *s, char *d) {
    int i = 0, k = 0;
    while (s[i]) {              // continue till a null character

        if (s[i]=='/' && s[i+1] =='/') { // line comment 
            while(s[i]!='\n'&&s[i]!='\0')       // skip the entire line
                i++;
        }
        else if (s[i] == '/' && s[i+1] == '*') { // block comment
            i += 2;
            while (!(s[i] == '*' && s[i+1] == '/') && s[i])         // skip the entire line
                i++;
            if (s[i]) 
                i += 2;
        }
        else if (s[i] == '#') { // include header
            while (s[i] != '\n' && s[i] != '\0')    //skip the entire line
                i++;
        }
        else {
            d[k++] = s[i++];            //otherwise write everything as it is
        }
    }
    d[k] = '\0';        //put null character to show string ended
}



int is_key(char *w) {               //to check if the word is a reaserved word or not
    if (strcmp(w, "int") == 0 || strcmp(w, "float") == 0 || strcmp(w, "double") == 0 || 
        strcmp(w, "char") == 0 || strcmp(w, "void") == 0 || strcmp(w, "if") == 0 || 
        strcmp(w, "else") == 0 || strcmp(w, "while") == 0 || strcmp(w, "for") == 0 || 
        strcmp(w, "return") == 0) {
                // printf("Researved word:: ");
        return 1;       //if researved word return 1:
    }
    return 0;       //otherwise return 0
}

void rem_key(char *s, char *d) {        // a function to remove keywords
    int i=0, j=0;
    char temp[100];         // a temp varuable to store the word
    int t = 0;
    
    while (s[i] != '\0') {
        if (isalpha(s[i])) {            // if alphabhet, store it in temp
            temp[t++] = s[i];       
        } else {
            temp[t] = '\0';
            if (t > 0 && !is_key(temp)) {
                // copy word if not keyword
                for (int x = 0; x < t; x++) 
                    d[j++] = temp[x];
            }
            t = 0;
            d[j++] = s[i];
        }
        i++;
    }
    d[j] = '\0';
}

// code similarity
void code_sim(char *s1, char *s2) {
    char *c1 = strdup(s1);              //equavalent to copy a string to another by also using dma
    char *c2 = strdup(s2);
    
    char *list1[1000], *list2[1000];            //pointers where each points to a specific token | max 1000 tokens
    int n1 = 0, n2 = 0;
    
    char *t = strtok(c1, " \n\t(){};,"); //tokenize by considering all of these as delimeters
    while (t && n1 < 1000) {               
        if (strlen(t) > 0)      
            list1[n1++] = t;
        t = strtok(NULL, " \n\t(){};,");        // token the next word
    }
    
    t = strtok(c2, " \n\t(){};,");
    while (t && n2 < 1000) {
        if (strlen(t) > 0)          // SIMILARLY FOR SECOND FILE
            list2[n2++] = t;
        t = strtok(NULL, " \n\t(){};,");
    }
    
    if (n1 == 0 || n2 == 0) {               // If no tokens found
        printf("No code tokens.\n");
        free(c1);
        free(c2);
        return;
    }
    
    int matched[1000] = {0};           
    int m = 0;
    
    for (int i = 0; i < n1; i++) {          
        for (int j = 0; j < n2; j++) {                              // comparing every ith c file with every jth+1 file
            if (!matched[j] && strcmp(list1[i], list2[j]) == 0) {           //if tokens are equal!
                if(fp_rep)          // check if code_report file is opened or not
                fprintf(fp_rep, "  Match: %s\n", list1[i]);         //write the matched word in the report
                matched[j] = 1;
                m++;        //increase the count
                break;
            }
        }
    }
    // DICE SIMILARITY FORMULA (V.IMP)
    
    float res = (2.0 * m) / (n1 + n2) * 100.0;
    
    printf("Matches: %d\n", m);
    printf("Similarity: %.2f%%\n", res);
    
    if (fp_rep) {
        fprintf(fp_rep, "\nTotal Matches: %d\nSimilarity: %.2f%%\n", m, res);
        fprintf(fp_rep, "--------------------------------\n");
    }
    
    free(c1);
    free(c2);
}
