CROSS =/home/ky/work/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/arm-linux-gnueabihf-
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf

SRCS = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

HEADER_PATH = -I../../inc
LIB_PATH = -L../../lib

LIBS = -lmxml

# LIBS = libdiv.a

VERSION = 1.0.0.1
TARGET = test.$(VERSION)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LIB_PATH) $(LIBS) -lpthread

$(OBJS):%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER_PATH) -std=c99

clean:
	$(RM) $(TARGET) *.o 
