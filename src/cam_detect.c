#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"
#include "show_calibration_file.h"
#include "calibration.h"
#include "detection.h"


int main(int argc, char** argv) {

    // Check that user has inputed correct arguments
    if (*argv[1]=='d'|| *argv[1]=='c'){
        if (argc!=4){
            printf("Incorrect input\n");
            return 0;
        }
    }
    else if (*argv[1]=='s'){
        if (argc!=3){
            printf("Incorrect input\n");
            return 0;
        }
    }
    else {
        printf("Incorrect input\n");
        return 0;
    }
    
    // Store the calibration file and image name
    char *calibration_file=argv[2];
    char *bmp_file=argv[3];
    
    // Show the calibration file
    if (*argv[1]=='s'){
        if (show_calibration_file(calibration_file)==0){
            return 0;
        }
    }

    // Obtain calibration data for image
    if (*argv[1]=='c'){
        calibration(bmp_file,calibration_file);
    }

    // Detect objects
    if (*argv[1]=='d'){
        if (detection(calibration_file, bmp_file)==0){
            return 0;
        }
    }
    return 0;
}

