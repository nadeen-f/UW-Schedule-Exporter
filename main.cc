#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;


// ============================================================================
//                                Constants
// ============================================================================

const int PREAMBLE = 18; // number of lines to skip in the preamble
const string FILE_NAME = "Class_schedule.ics"; // default file name



// ============================================================================
//                             Helper functions
// ============================================================================

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

// initializes a vector of courses based on the provided input
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

    // loop through and initialize all the courses
    while (schedule.length() > 100) {
        Course course = Course(schedule);
        if (course.isValid()) {
            courses.push_back(course);
        }
    }
    return courses;
}


// formats the given date into iCal UTC form
string formatDate(string date) {
    return "**" + date + "**";
}

// formats the given time into iCal UTC form
string formatTime(string time, bool isStartTime) {
    string ftime = "";
    int separator = time.find("-");
    if (isStartTime) {
        ftime = time.substr(0, separator - 1);
    } else {
        ftime = time.substr(separator + 2, time.length() - separator + 2);
    }
    ftime.pop_back();
    string period = ftime; // ftime.back() need last char
    ftime.pop_back();
    if (period == "P") {

    }
    return ftime;
}

// formats the occurences (ie the days on which the event repeats)
string formatOccurences(string occurences) {
    return "**" + occurences + "**";
}

// adds the course name to the schedule
void addCourseName (ofstream &schedule, Course course, auto component) {
    schedule << EVENT_START << endl;
    schedule << "SUMMARY:" << course.code << get<COMPONENT>(component) << endl;
}

// adds the course description to the schedule
void addCourseDescription (ofstream &schedule, Course course, auto component) {
    schedule << "DESCRIPTION:" << get<LOCATION>(component) << "\n"
            << course.name << " with " << get<INSTRUCTOR>(component) << endl;
}

// adds the date and time for the course component to the schedule
void addDateAndTime (ofstream &schedule, Course course, auto component) {
    //DTSTART;TZID=America/Toronto:20240904T133000
    //DTEND;TZID=America/Toronto:20240904T142000
    schedule << "DTSTART;" << TIME_ZONE <<
             << formatTime(get<TIMES>(component), true) << endl;
    schedule << "DTEND;" << TIME_ZONE <<
             << formatTime(get<TIMES>(component), false) << endl;
    schedule << "RRULE:FREQ=WEEKLY;UNTIL=" << formatDate(get<END>(component))
             << ";BYDAY=" << formatOccurences(get<DAYS>(component)) << endl;
    schedule << EVENT_END << endl;
}

// generates the ics file with all the course information
void createScheduleFile() {
    ofstream schedule;
    string scheduleName = FILE_NAME; 
    schedule.open(scheduleName);

    // initialize all the courses
    vector <Course> courses = createSceduleArray();

    // ics file preamble
    schedule << FILE_START << endl;

    for (Course course : courses) {
        for (auto component : course.components) {
            addCourseName(schedule, course, component);
            addCourseDescription(schedule, course, component);
            addDateAndTime(schedule, course, component);
        }
    }

    // ics file ending 
    schedule << FILE_END << endl;
}

// ============================================================================
//                                   Main
// ============================================================================

int main () {
    printDescription();
    createScheduleFile();
}