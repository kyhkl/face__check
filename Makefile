
CROSS = /home/ky/work/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/arm-linux-gnueabihf-
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c 
RM = rm -r

SRCS = $(wildcard ./src/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
SRCO = $(wildcard ./src/*.o)

HEADER_PATH = -I./inc
LIB_PATH = -L./lib


LIBS = -lmxml  -lpaho-mqtt3c


# LIBS = libdiv.a

VERSION = 1.0.0.1
TARGET = face_check.$(VERSION)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LIB_PATH) $(LIBS)  -lpthread -lrt

$(OBJS):%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER_PATH) -std=c99

clean:
	$(RM) $(TARGET) $(SRCO)  *.o

