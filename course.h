#include <string>
#include <vector>
#include <tuple>

enum tupleFields {
        COMPONENT,
        DAYS,
        TIMES,
        LOCATION,
        INSTRUCTOR,
        START,
        END
    };

const std::string FILE_START = "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:-//appsheet.com//appsheet 1.0//EN\nCALSCALE:GREGORIAN\nMETHOD:PUBLISH";
const std::string FILE_END = "END:VCALENDAR";
const std::string EVENT_START = "BEGIN:VEVENT";
const std::string EVENT_END = "END:VEVENT";
const std::string TIME_ZONE = "TZID=America/Toronto:";

class Course {
    public:
    std::string name;
    std::string code;
    std::string professor;
    int numComponents;

    // vector of (component, location, days, times, instructor, start, end) 
    //     tuples
    std::vector <std::tuple <std::string, std::string, std::string, 
    std::string, std::string, std::string, std::string>> components;

        Course(std::string &schedule);
        bool isValid();
        //std::string getField(tupleFields field, auto component);
};
