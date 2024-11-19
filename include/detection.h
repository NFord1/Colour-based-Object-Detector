#ifndef DETECTION_H
#define DETECTION_H
#include "bitmap.h"
// This function performs a recursive depth first search algorithm on the objects above the threshold obtained 
// from the calibration file to determine connected regions and print a bounding box around the detected objects
int detection(char *calibration_file, char *bmp_file);

#endif
