#define WIDTH 320
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"
#include "detection.h"

// This function performs the recursive depth first search algorithm on the objects above the threshold to determine connected regions
void DFS(int i, int j, int (*visited)[WIDTH], Bmp threshold, int width, int height, int (*regions)[WIDTH], int region_num);

// This function performs a recursive depth first search algorithm on the objects above the threshold obtained 
// from the calibration file to determine connected regions and print a bounding box around the detected objects
int detection(char *calibration_file, char *bmp_file){
    // Read and make a copy of the specified image
    Bmp bmp=read_bmp(bmp_file);
    Bmp threshold=copy_bmp(bmp);
    int width=bmp.width;
    int height=bmp.height;
    
    // Open a file
    FILE* filePointer = fopen(calibration_file, "r");

    // Check if file opened
    if (filePointer == NULL){
        fprintf(stderr, "Could not open calibration file\n");
        return 0;
    }

    // Read strings line by line
    char string[50];
    while(fgets(string, 50, filePointer)) // fgets returns null when EOF is found
    {
        //Set the first token
        char *token = strtok(string, " ");

        char *object;
        int midhue,maxdiff,mins,minv;
        int count=0;

        // Keep printing tokens while one of the delimiters present in string[].
        while (token != NULL){

            //Set each token to the appropriate variable
            if (count==0){
                object=token;
            }
            if (count==1){
                midhue=atoi(token);
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
        // Check if each pixel in the image is an object based on the calibration data and set the possible 
        // objects to white in the threshold image and everything else to black
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                HSV hsv=rgb2hsv(bmp.pixels[i][j]);
                if (hue_difference(hsv.hue, midhue)<=maxdiff && hsv.saturation>=mins && hsv.value>=minv){
                    threshold.pixels[i][j][RED]=255;
                    threshold.pixels[i][j][GREEN]=255;
                    threshold.pixels[i][j][BLUE]=255;
                }
                else{
                    threshold.pixels[i][j][RED]=0;
                    threshold.pixels[i][j][GREEN]=0;
                    threshold.pixels[i][j][BLUE]=0;    
                }
            }
        }
        write_bmp(threshold, "images/threshold.bmp");

        // Initialise arrays the size of the image to represent whether a pixel has been visitied or not 
        // and what region it is in
        int visited[height][width];
        int regions[height][width];
        int region_num=1;

        // Initially set all to zero
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                visited[i][j]=0;
                regions[i][j]=0;
            }
        }

        // Check if each pixel is a possible object which hasn't been visited yet, if checks are passed 
        // conduct DFS to find all connected pixels of object
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                if (threshold.pixels[i][j][RED]==255 && visited[i][j]==0){
                    DFS(i, j, visited, threshold, width, height, regions, region_num);
                    // Once all connected pixels are found increase the region number
                    region_num=region_num+1;
                }
                
            }
        }

        // Determine the minimum and maximum x and y values for each region
        for (int r=1; r<region_num; r++){
            int min_x=width;
            int min_y=height;
            int max_x=0;
            int max_y=0;
            for (int i=0; i<height; i++){
                for (int j=0; j<width; j++){
                    if (regions[i][j]==r){
                        if (j<min_x){
                            min_x=j;
                        }
                        if (i<min_y){
                            min_y=i;
                        }
                        if (j>max_x){
                            max_x=j;
                        }
                        if (i>max_y){
                            max_y=i;
                        }
                    }
                }        
            }

            // Calculate the width and height of the region and if it is greater then 20 pixels wide 
            // and 20 pixels high draw a box around the object
            int diff_x=max_x-min_x+1;
            int diff_y=max_y-min_y+1;
            if (diff_x>=20 && diff_y>=20){
                printf("Detected %s: %d %d %d %d\n",object, min_x, min_y, diff_x, diff_y);
                draw_box(threshold, min_x, min_y, diff_x, diff_y);
                write_bmp(threshold, "images/threshold.bmp");
            }
        }
    }

    // Close and free files
    fclose(filePointer);
    free_bmp(threshold);
    free_bmp(bmp);
    return 1;
}


void DFS(int i, int j, int (*visited)[WIDTH], Bmp threshold, int width, int height, int (*regions)[WIDTH], int region_num){
    // Once node is reached store that it has been visited and what region it is in
    visited[i][j]=1;
    regions[i][j]=region_num;
    
    // Check each surrounding pixel above, below, right and left, whether it is a possible object, 
    // and that it is within the image and conduct DFS on the next pixel if it passes checks
    if (i+1<=height && visited[i+1][j]==0 && threshold.pixels[i+1][j][RED]==255){
        DFS(i+1, j, visited, threshold, width, height, regions, region_num);
    }
    if (i-1>=0 && visited[i-1][j]==0 && threshold.pixels[i-1][j][RED]==255){
        DFS(i-1, j, visited, threshold, width, height, regions, region_num);
    }
    if (j+1<=width && visited[i][j+1]==0 && threshold.pixels[i][j+1][RED]==255){
        DFS(i, j+1, visited, threshold, width, height, regions, region_num);
    }
    if (j-1>=0 && visited[i][j-1]==0 && threshold.pixels[i][j-1][RED]==255){
        DFS(i, j-1, visited, threshold, width, height, regions, region_num);
    }
}

