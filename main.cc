#include <iostream>
#include <string>
using namespace std;

const int PREAMBLE = 18;

// This function prints the program description
void printDescription (void) {
    cout << "\nUW Schedule Exporter\n" << endl;
    cout << "This program will convert your class schedule information from\n" 
         <<  "Quest into an iCalendar file which can be imported anywhere.\n" << endl;
    cout << "To get started ...\n";
    cout << "   1. Log into Quest\n";
    cout << "   2. Click the \"Class Schedule\" tile.\n";
    cout << "   3. Choose a term and select continue.\n";
    cout << "   4. In List View, copy the entire page (press ctrl A and ctrl C)\n";
    cout << "   5. Paste below:\n" << endl;
}

bool allWhitespace(string line) {
    for (char c : line) {
        // if any char c in the string line is not whitespace, return false
        if (c != '\n' && c != ' ' && c != '\t') {
            return false;
        }
    }
    return true;
}

int main () {
    printDescription();
    //string schedule = createSceduleArray();

    // ========================================================================
    string schedule = "";
    int numLines = 0;
    string line;
    
    while (getline(cin, line)) {
        if (! allWhitespace(line)) {
            if (numLines >= PREAMBLE) {
                schedule += line + "\n";
            }
            ++ numLines;
        }
    }
    numLines -= PREAMBLE;
    cout << schedule;
}