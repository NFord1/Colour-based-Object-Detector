#ifndef CALIBRATION_H
#define CALIBRATION_H
#include "bitmap.h"
// This function measures the hues of the centre of a provided image and outputs the calibration data 
// with the specified label
void calibration(char *calibration_file, char *bmp_file);

#endif
