#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { return processes_; }

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { 
  float MemTotal = LinuxParser::ProcessorMemInfo("MemTotal");
  float MemFree = LinuxParser::ProcessorMemInfo("MemFree");
  if (MemTotal > 0) {
    /// Formula For Usage
    return (MemTotal - MemFree) / MemTotal;
  }
  return 0.0;
}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::ProcStatInfo("procs_running"); }

int System::TotalProcesses() { return LinuxParser::ProcStatInfo("processes"); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }