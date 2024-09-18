#include "course.h"
#include <string>
#include <tuple>

#include <iostream>

// ============================================================================
//                            Helper functions
// ============================================================================

const int NUM_UNEEDED_LINES = 8;
const int COMPONENT_LENGTH = 3;
const int DATE_LEN = 10;
const char CODE_NAME_SEPARATOR = '-';
const char DAYS_SEPARATOR = ' ';

// extracts and returns the course code from schedule
std::string getCourseCode(std::string &schedule) {
    std::string code;
    for (char letter : schedule) {
        if (letter != CODE_NAME_SEPARATOR) {
            code += letter;
        } else {
            break;
        }
    }
    schedule = schedule.substr(code.length() + 2, schedule.length());
    return code;
}

// extracts and returns the course name from schedule
std::string getCourseName(std::string &schedule) {
    std::string name;
    // extract name
    for (char letter : schedule) {
        if (letter != '\n') {
            name += letter;
        } else {
            break;
        }
    }
    schedule = schedule.substr(name.length() + 1, schedule.length());

    // skip the next NUM_UNEEDED_LINES
    int numLines = 0;
    int numChars = 1;
    for (char letter : schedule) {
        if (letter == '\n') {
            ++numLines;
        }
        if (numLines < NUM_UNEEDED_LINES) {
            ++numChars;
        }
    }
    schedule = schedule.substr(numChars, schedule.length());
    return name;
}

// returns true if there are more compontents for the current course, and 
//     false otherwise
bool moreComponents(std::string schedule) {
    std::string component = schedule.substr(0, COMPONENT_LENGTH);
    if (component != "LEC" && component != "TUT" && component != "LAB" 
        && component != "TST" && component != "WRK") {
        return false;
    }
    return true;
}

// extracts and returns the course component from schedule
std::string getComponent(std::string &schedule) {
    std::string component;
    component = schedule.substr(0, COMPONENT_LENGTH);
    schedule = schedule.substr(component.length() + 1, schedule.length());
    return component;
}

// extracts and returns the days in which the component occurs from schedule
std::string getDays(std::string &schedule) {
    std::string days;
    for (char letter : schedule) {
        if (letter != DAYS_SEPARATOR && letter != '\n') {
            days += letter;
        } else {
            break;
        }
    }
    if (days != "TBA") {
        schedule = schedule.substr(days.length() + 1, schedule.length());
    }
    return days;
}

// extracts and returns the times in which the component occurs from schedule
std::string getTimes(std::string &schedule) {
    std::string time;
    for (char letter : schedule) {
        if (letter != '\n') {
            time += letter;
        } else {
            break;
        }
    }
    schedule = schedule.substr(time.length() + 1, schedule.length());
    return time;
}

// extracts and returns the course building from schedule
std::string getBuilding(std::string &schedule) {
    std::string building = schedule.substr(0, schedule.find('\n'));
    schedule = schedule.substr(building.length() + 1, schedule.length());
    return building;
}

// extracts and returns the course instructor from schedule
std::string getInstructor(std::string &schedule) {
    std::string instructor = schedule.substr(0, schedule.find('\n'));
    schedule = schedule.substr(instructor.length() + 1, schedule.length());
    return instructor;
}

std::string getDate(std::string &schedule) {
    std::string date = schedule.substr(0, DATE_LEN);
    int offset = 1;
    if (schedule.at(DATE_LEN) != '\n') {
        offset = 3;
    }
    schedule = schedule.substr(DATE_LEN + offset, schedule.length());
    return date;
}

// ============================================================================
//                            Member functions
// ============================================================================

// returns true if course is valid, and false otherwise. A valid course is one
//     has scheduled in person components that need to be marked on a calendar
bool Course::isValid() {
    for (auto component : components) {
        if (std::get<1>(component) == "ONLN") { // location
            return false;
        } else if (std::get<0>(component) == "WRK") { // component
            return false;
        }
    }
    return true;
}

// ctor
Course::Course(std::string &schedule) {
    numComponents = 0;
    code = getCourseCode(schedule);
    name = getCourseName(schedule);
    std::cout << code << std::endl;
    std::cout << name << std::endl;
    while (moreComponents(schedule)) {
        ++numComponents;
        auto component = std::make_tuple(getComponent(schedule),
                                         getDays(schedule),
                                         getTimes(schedule),
                                         getBuilding(schedule),
                                         getInstructor(schedule),
                                         getDate(schedule),
                                         getDate(schedule));
        components.push_back(component);
        std::cout << std::get<COMPONENT>(component) << std::endl;
        std::cout << std::get<DAYS>(component) << std::endl;
        std::cout << std::get<TIMES>(component) << std::endl;
        std::cout << std::get<LOCATION>(component) << std::endl;
        std::cout << std::get<INSTRUCTOR>(component) << std::endl;
        std::cout << std::get<START>(component) << std::endl;
        std::cout << std::get<END>(component) << "\n" << std::endl;

        // remove class number and section info if there are more components
        if (isdigit(schedule.at(0))) {
            schedule = schedule.substr(10, schedule.length());
        }
    }
}