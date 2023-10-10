#include "Bar.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Inside the parameters for main, we can pass arguments
// argc is the count of arguments
// argv are the parameters themselves


int main(int argc, char *argv[])
{
    cout << "Welcome to UMBC Grid of Bar Charts" << endl;
    while (argc < 2)
    { // Checks to make sure the user passes a file to load
        cout << "You are missing a data file." << endl;
        cout << "Expected usage ./proj5 proj5_test1.txt" << endl;
        cout << "arg[1] is the input file" << endl;
        return 0;
    }
    Bar myBar(argv[1]); // Creates bar charts by passing the filename
    myBar.Start();      // Starts the bar charts
    return 0;
}

