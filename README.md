
# Colour-based Object Detector

This project is a colour-based object detection system that processes BMP images to detect and highlight objects based on their colour properties. The system includes functionalities for calibration, detection, and displaying calibration data.

## Features

- **Calibration**: Measures the hues of the center of a provided image and outputs the calibration data with the specified label.
- **Detection**: Reads and processes an image to detect objects based on calibration data, and highlights detected objects with bounding boxes.
- **Show Calibration File**: Displays the contents of the calibration file from the command line.

## File Structure

- `src/`: Contains the source code files.
  - `bitmap.c`: Functions for reading, writing, copying, and manipulating BMP images.
  - `calibration.c`: Functions for calibrating the system using a BMP image.
  - `detection.c`: Functions for detecting objects in a BMP image based on calibration data.
  - `show_calibration_file.c`: Functions for displaying the contents of a calibration file.
  - `cam_detect.c`: Main program file that handles user input and calls the appropriate functions.
- `include/`: Contains the header files.
  - `bitmap.h`: Header file for BMP image functions.
  - `calibration.h`: Header file for calibration functions.
  - `detection.h`: Header file for detection functions.
  - `show_calibration_file.h`: Header file for displaying calibration file functions.
- `test_calibrations/`: Contains sample calibration files.
- `makefile`: Makefile for building the project.

## Usage

### Compilation

To compile the project, run the following command:

```sh
make
```

### Running the Program

The program can be run in three modes: show calibration file, calibration, and detection.

#### Show Calibration File

To display the contents of a calibration file:

```sh
./cam_detect s <calibration_file>
```
**Example Output:**
```sh
Calibrated Objects:
blueblock: Hue: 191 (Max. Diff: 4), Min. SV: 50 30
```

#### Calibration

To calibrate the system using a BMP image:

```sh
./cam_detect c <calibration_file> <bmp_file>
```
**Example:**
```sh
./cam_detect c orangeblock images/orangeblock.bmp 
```
```sh
orangeblock 10 10 50 30
```
#### Detection

To detect objects in a BMP image based on calibration data:

```sh
./cam_detect d <calibration_file> <bmp_file>
```
**Example:**
```sh
./cam_detect d test_calibrations/blobs.txt images/blobs001.bmp 
```
```sh
Detected redblob: 77 15 114 110
Detected redblob: 222 82 72 31
Detected redblob: 186 162 56 36
Detected redblob: 100 171 26 28
Detected redblob: 47 177 31 32
Detected greenblob: 29 25 29 21
Detected greenblob: 21 104 61 68
Detected greenblob: 216 130 65 21
Detected blueblob: 251 193 38 27
```

## Dependencies

- GCC (GNU Compiler Collection)
- Standard C libraries

## Learn More
For a more detailed overview of the project visit [Colour-based Object Detector.pdf](./Colour-based%20Object%20Detector.pdf)

## License

This project is licensed under the MIT License.
```
