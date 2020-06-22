#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : mbRam_(0), pid_(pid) {};

int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

string Process::Command() { return LinuxParser::Command(pid_); }

void Process::UpdateRam() {
    mbRam_ = std::stoi(LinuxParser::Ram(pid_)) / 1000;
}

string Process::Ram() {
    UpdateRam();
    return to_string(mbRam_); 
}

string Process::User() { 
  string uid = LinuxParser::Uid(pid_);
  return LinuxParser::User(uid);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }