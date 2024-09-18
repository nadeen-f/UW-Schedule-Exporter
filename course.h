#include <string>
#include <vector>
#include <tuple>

class Course {
    std::string name;
    std::string code;
    std::string professor;
    int numComponents;

    // vector of (component, location, days, times, instructor, start, end) 
    //     tuples
    std::vector <std::tuple <std::string, std::string, std::string, 
    std::string, std::string, std::string, std::string>> components;

    enum tupleFields {
        COMPONENT,
        DAYS,
        TIMES,
        LOCATION,
        INSTRUCTOR,
        START,
        END
    };

    public:
        Course(std::string &schedule);
        bool isValid();
};
