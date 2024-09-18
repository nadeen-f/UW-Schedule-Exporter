#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

const int PREAMBLE = 18;


// This function prints the program description
void printDescription (void) {
    cout << "\nUW Schedule Exporter\n" << endl;
    cout << "This program will convert your class schedule information from\n" 
         <<  "Quest into an iCalendar file which can be imported anywhere.\n" 
         << endl;
    cout << "To get started ...\n";
    cout << "   1. Log into Quest\n";
    cout << "   2. Click the \"Class Schedule\" tile.\n";
    cout << "   3. Choose a term and select continue.\n";
    cout << "   4. In List View, copy the entire page (ctrl A + ctrl C)\n";
    cout << "   5. Paste below:\n" << endl;
}

// returns true if line is only whitespace characters, otherwise returns false
bool allWhitespace(string line) {
    for (char c : line) {
        // if any char c in the string line is not whitespace, return false
        if (!isspace(c)) {
            return false;
        }
    }
    return true;
}

vector <Course> createSceduleArray (void) {
    vector <Course> courses;

    // read schedule from stdin
    string schedule = "";
    int numLines = 0;
    string line;
    
    while (getline(cin, line)) {
        if (! allWhitespace(line)) {
            if (numLines >= PREAMBLE) {
                schedule += line + "\n";
            }
            ++numLines;
        }
    }

    while (schedule.length() > 100) {
        Course course = Course(schedule);
        if (course.isValid()) {
            courses.push_back(course);
        }
    }
    return courses;
}

int main () {
    printDescription();
    vector <Course> courses = createSceduleArray();
}