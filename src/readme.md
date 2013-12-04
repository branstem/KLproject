Copyright and Licensing Information
===================================
Copyright (C) 2013 Matthew Branstetter

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Contact Information
=================== 
Any questions or problems please feel to contact:
 
Matthew Branstetter
email:	branstem@pdx.edu
phone:	503-873-3181

Credits and Acknowledgements
=======================
I would like to acknowledge Dr. Malgorzata Chrzanowska-Jeske
for providing the steps to completing the project. This was
an assignment as part of Professor Jeske ECE428 VLSI Computer
Aided Design class Fall 2013.

General Information
===================
This project demonstrates the Kernighan–Lin algorithm to partition
a set of vertices. It was programmed in C++ language for a Linux 
environment. 

File Manifest
=============
The files included in project build are:

1.	project.cpp
2.	KLpartition.h
3.	KLpartition.cpp
4.	kl.txt
5.	kl2.txt
6.	kl3.txt
7.	kl4.txt
8.	kl5.txt
4.	makefile
5.	project

Compiling
=========
Pre-compiled binaries are available for Ubuntu Linux 10.04 and newer.  
Compiling this software is handled by a makefile. Copy all the files
provided into a build directory then run the makefile. You can do 
this by doing the following: 

$ mkdir build
$ cp project /build
$ cp project.cpp /build
$ cp KLpartition.h /build
$ cp KLpartition.cpp /build
$ cp kl.txt /build
$ cp kl2.txt /build
$ cp kl3.txt /build
$ cp kl4.txt /build
$ cp kl5.txt /build
$ cp makefile /build
$ cp readme.md /build
$ cd build
$ make

Running 
============
You can run the program one of two ways. You can provide the file 
name for the .txt file containing information on the vertices or 
you can use the default "kl.txt" file. Example:

$./project filename.txt

or the default file "kl.txt":

$./project
