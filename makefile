CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=-lm
TARGET=cam_detect

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
_DEPS = bitmap.h calibration.h detection.h show_calibration_file.h 
_OBJS = bitmap.o calibration.o detection.o show_calibration_file.o cam_detect.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
