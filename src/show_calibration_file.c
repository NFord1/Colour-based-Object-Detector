#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "show_calibration_file.h"

// This function displays the contents of the calibration file from the command line
int show_calibration_file(char *calibration_file){

    // Open calibration file
    FILE* filePointer = fopen(calibration_file, "r");

    // Check if file actually opened
    if (filePointer == NULL){
        fprintf(stderr, "Could not open calibration file\n");
        return 0;
    }

    printf("Calibrated Objects:\n");

    // Read strings line by line
    char string[50];
    while(fgets(string, 50, filePointer)) // fgets returns null when EOF is found
    {
        //Set the first token
        char *token = strtok(string, " ");

        char *object;
        int hue,maxdiff,mins,minv;
        int count=0;

        // Keep printing tokens while one of the delimiters present in string[].
        while (token != NULL){

            //Set each token to the appropriate variable
            if (count==0){
                object=token;
            }
            if (count==1){
                hue=atoi(token);
            }
            if (count==2){
                maxdiff=atoi(token);
            }
            if (count==3){
                mins=atoi(token);
            }
            if (count==4){
                minv=atoi(token);
            }
            token = strtok(NULL, " ");
            count=count+1;
        }

        printf("%s: Hue: %d (Max. Diff: %d), Min. SV: %d %d\n",object, hue, maxdiff, mins, minv);
    }

    // Close the file
    fclose(filePointer);
    return 1;
}

