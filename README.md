# Filter
A filter application written in C. Main purpose is loading a BMP, and converting it pixel by pixel depending on the selected filter. Its a command line app.

#bmp.h 
We find definition of datatypes and some structures for the Bmps headers and the usage of RGB triples.

#Filter.c 
Is where the main app happens and where the code for handling the files and applying the correct filter to it, also alocates and clear the memory up so no leaks happens.

#Helpers.c
In this file are the functions for every filter and other helpers needed.

#Helpers.H
This files provides the prototypes of the functions in helpers.c

#Makefile
Are the instruction for compiling all the app.

#usage.txt
Just simply instructions on how to run the app.
