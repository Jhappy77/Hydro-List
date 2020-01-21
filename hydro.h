#ifndef HYDRO_H
#define HYDRO_H

#include "list.h"

void displayHeader();
//PROMISES: Shows header for the program in Cout

int readData(FlowList& my_list);
//PROMISES: Reads data into the list obj. Returns number of records in the
//file that it reads from.

int menu();
//PROMISES: Displays a menu and returns the users input (a number from 1-5)

void display(const FlowList& list);
//PROMISES: Displays the contents of the list, the average, and the median

void addData(FlowList& list);
//PROMISES: Inserts user-added data into the list, updates # of records.

void removeData(FlowList& list);
//PROMISES: Removes a single data member w/ the specified year,
//updates # of records

double average(const FlowList& list);
//PROMISES: Returns flow average in given List

double median(const FlowList& list);
//PROMISES: Returns flow median in given list.

void saveData(const FlowList& list);
//PROMISES: Opens flow.txt for writing and writes content of linked list
// into file, using the truncate option.

void pressEnter();
//PROMISES: Displays message, waits for user to press enter to continue.

void manage_UI(FlowList& list);
//PROMISES: Uses the menu() function to receive an integer, and uses this int to
//perform the action corresponding to the user selection.

double getDouble(const char * message);
//PROMISES: Retrieves the first nonzero double from the buffer.

int getInt(const char * message);
//PROMISES: Retrieves the first nonzero int from the buffer.

void time_delay(double x);
//REQUIRES: Program is running in a Unix environment (or Unix-based)
//PROMISES: Introduces a time delay of x milliseconds. Uses the sleep function
//from <unistd.h> to accomplish this, but this implementation
//should vary by system.

void clear_buffer();
//PROMISES: Clears the buffer to prevent program from taking in junk
//inputs.

#endif
