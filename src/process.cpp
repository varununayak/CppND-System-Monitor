#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : mbRam_(0), pid_(pid){};

int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
  const struct LinuxParser::ProcessStatTimes pst =
      LinuxParser::ProcessStatTimes(pid_);
  auto total_time = pst.utime + pst.stime + pst.cutime + pst.cstime;
  total_time /= float(sysconf(_SC_CLK_TCK));
  return total_time / float(UpTime());
}

string Process::Command() { return LinuxParser::Command(pid_); }

void Process::UpdateRam() { mbRam_ = std::stoi(LinuxParser::Ram(pid_)) / 1000; }

string Process::Ram() {
  UpdateRam();
  return to_string(mbRam_);
}

string Process::User() {
  string uid = LinuxParser::Uid(pid_);
  return LinuxParser::User(uid);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const {
  const struct LinuxParser::ProcessStatTimes pst =
      LinuxParser::ProcessStatTimes(pid_);
  return LinuxParser::UpTime() - pst.starttime /  sysconf(_SC_CLK_TCK);
}