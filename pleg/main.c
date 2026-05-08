#include "plagiarism.h"

FILE *fp_rep = NULL;                    //Global Pointer to a file

int main() {

    while (1) {                                             // Starting Menu
         printf("\n==============================================\n");
        printf("        PLAGIARISM CHECKER SYSTEM              \n");
        printf("          FAST NUCES PESHAWAR                  \n");
        printf("==============================================\n\n");
        printf("1. Check Text Files\n");
        printf("2. Check Code Files\n");
        printf("3. Exit\n");
        printf("----------------------------------------------\n");
        printf("Choice: ");
        int opt;

        scanf(" %d", &opt);      // option selection

        // FOR TEXT/DOCX/PDF
        if(opt == 1) {         
            int n;

            printf("How many files? (2-20): ");

            scanf("%d", &n);            //Number of files to check plagiagrism
            
            if (n<2 || n>20) {              //Setting up limit to check for pleg

                printf("Number of Files Must be in between 2 - 20.\n");

                continue;
            }
            
            char fnames[20][200];           // an array to store file names upto 20
            for (int i=0;i<n;i++) {
                printf("\n==============================================\n");
                printf("File %d name: ",i + 1);            
                scanf("%s", fnames[i]);            // file name input with its extension
            }


            // To open and conversion of file formats
            
            fp_rep = fopen("report.txt", "a");          //Create or open a file in append mode
            if(fp_rep==NULL){
                printf("FAILED TO OPEN FILE: ");            /// validating file opening
                continue;
            }
            if (fp_rep){ 
                fprintf(fp_rep, "\n--- NEW TEXT ANALYSIS ---\n");
            }
            char *data[20];                            // a pointer array where each index point will point each file
            int err = 0;        //flag!!! succees
            
            for (int i=0; i<n; i++) {
                data[i] = read_f(fnames[i]);        //passing i-th file to read_f, and storing its address to the data of i-th pointer
                if (data[i]== NULL) {   // to validate the pointer is being pointer to the correct address or not
                    printf("Failed to read %s\n", fnames[i]);
                    err =1;     //failed to read
                }
            }
            
            if (!err) {     // if pointer points to a correct address
                char processed[20][5000];
                for (int i=0; i<n; i++) {
                    clean_str(data[i], processed[i]);
                }
                
                for (int i=0; i<n; i++) {  
                    for (int j=i+1;j<n;j++) {        //comparing ith file with every ith+1 file
                        printf("\nChecking %s vs %s...\n", fnames[i], fnames[j]);
                        
                        if (fp_rep){
                         fprintf(fp_rep, "Files: %s vs %s\n", fnames[i], fnames[j]);        // writing this into report
                        }   
                        float res = compare_txt(processed[i], processed[j]);        //passing ith and ith+1 file to compare_txt function, which will return probablity percentage
                        printf("Result: %.2f%%\n", res);
                        
                        if (fp_rep)
                             fprintf(fp_rep, "Probability: %.2f%%\n", res);     //writing the res into probablity
                    }
                }
                
                // free memory after use
                for (int i = 0; i < n; i++) 
                    free(data[i]);
            }
            
            if (fp_rep) {
                fclose(fp_rep);             // Close the file!
                printf("Saved to report.txt\n");
            }
        }
        
        else if(opt==2) {           // FOR CODE PLEG CHECKER!
            int n;
            printf("Number of code files (2-20): ");
            scanf("%d", &n);                    
            
            char fnames[20][200];           //20 files
            for (int i=0; i<n; i++) {
                printf("Code file %d (.c / cpp): ", i+1);
                scanf("%s", fnames[i]);
            }
            
            fp_rep = fopen("code_report.txt", "a");
            if (fp_rep){ 
                fprintf(fp_rep, "\n--- NEW CODE ANALYSIS ---\n");
        }
            char *data[20];
            int err = 0;
            
            for (int i=0; i<n; i++) {
                data[i] = read_f(fnames[i]);
                if (!data[i]) {
                    printf("Error reading %s\n", fnames[i]);
                    err = 1;
                }
            }
            
            if (!err) {
                char temp[20][5000];       
                char final[20][5000];
                
                for (int i=0; i<n; i++) {
                    rem_cmt(data[i], temp[i]);

                    rem_key(temp[i], final[i]);
                }
                
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        printf("\nComparing %s and %s\n", fnames[i], fnames[j]);
                        if(fp_rep) 
                            fprintf(fp_rep, "Files: %s - %s\n", fnames[i], fnames[j]);
    
                        code_sim(final[i], final[j]);
                    }
                }
                for(int i=0; i<n; i++) 
                    free(data[i]);
            }
            
            if (fp_rep)
            printf("Successful Report Generation: \n");
                fclose(fp_rep);
        }
        
        else if (opt == 3) {        // If choice =3
            printf("\n-----------EXITING THE PROGRAM BYE-----------\n");
            
            getchar();                 // wait untill a char is entered:
            break;
        }
    }
    return 0;
}