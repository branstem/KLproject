#
#	Author: 	Matthew Branstetter
#	Title: 		make
#	Date:		11/21/2013
#
#	Description:	This is a Makefile for a project 1 ECE428.  
#	Typing 'make' or 'make project' will create the executable 
#	file.
#
#	-g adds debugging information to the 
#	executable file.
#	-Wall turns on compiler warnings.
#
#
CC=g++
CFLAGS=-g -Wall
TARGET=project
SOURCES=$(TARGET).cpp KLpartition.cpp
EXECUTABLE=$(TARGET)

$(EXECUTABLE): 
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) 
 
clean: 
	rm -rf *o $(EXECUTABLE)