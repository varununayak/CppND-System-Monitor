#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    const int numHours = seconds / 3600;
    string hours = std::to_string(numHours);
    string minutes = std::to_string((seconds - numHours * 3600) / 60);
    if (minutes.size() == 1) minutes = "0" + minutes;
    string nseconds = std::to_string(seconds % 60);
    if (nseconds.size() == 1) nseconds = "0" + nseconds;
    return hours + ":" + minutes + ":" + nseconds;
 }