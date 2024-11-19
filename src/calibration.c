#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"
#include "calibration.h"

//Compare function for qsort to sort the stored hues in ascending order with duplicates as neighbours
int compare(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

// This function measures the hues of the centre of a provided image and outputs the calibration data 
// with the specified label
void calibration(char *bmp_file, char *calibration_file){

    // Read bmp file and set variables for centre window starting coordinates
    Bmp bmp=read_bmp(bmp_file); 
    int mid_horizontal=bmp.width/2;
    int mid_vertical=bmp.height/2;
    int start_horizontal=mid_horizontal-25;
    int start_vertical=mid_vertical-25;
    int count=0;
    int* centre_window_hues=malloc(sizeof(int)*1);

    // Loop through each pixel in the centre window and if the pixel passes the checks store the hue
    for (int i=start_vertical; i<start_vertical+50; i++){
        for (int j=start_horizontal; j<start_horizontal+50; j++){
            HSV hsv=rgb2hsv(bmp.pixels[i][j]);

            if (hsv.saturation>=50){
                if (hsv.value>=30){
                count=count+1;
                centre_window_hues=(int*)realloc(centre_window_hues,sizeof(int)*count);
                centre_window_hues[count-1]=hsv.hue; 
                }   
            }
        }

    }
    //Sort the stored hues in ascending order with duplicates as neighbours
    qsort(centre_window_hues, count, sizeof(int), compare);

    // Set and calculate variables to determine the middle hue and the maximum hue difference
    int max_hue=centre_window_hues[count-1];
    int min_hue=centre_window_hues[0];
    int mid_hue=hue_midpoint(max_hue,min_hue);
    int max_hue_diff=hue_difference(max_hue,min_hue)/2;

    // Print the contents of the established calibration file
    printf("%s %d %d 50 30\n",calibration_file,mid_hue, max_hue_diff);

    // Free dynamic memory and bmp file
    free(centre_window_hues);
    free_bmp(bmp);
}
