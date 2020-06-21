#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    string line;
    while (std::getline(filestream, line)) {
      line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
      auto keyPos = line.find('=');
      if (line.substr(0, keyPos) == "PRETTY_NAME") {
        return line.substr(keyPos + 1);
      }
    }
  }
  return "N/A";
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    string line;
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      string os, kernel, version;
      linestream >> os >> version >> kernel;
      return kernel;
    }
  }
  return "N/A";
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::ProcessorMemInfo(string key) {
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if (stream.is_open()) {
    string line;
    while(std::getline(stream, line)) {
      auto keyPos = line.find(':');
      if (line.substr(0, keyPos) == key) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        auto kPos = line.find('k');
        float val = stof(line.substr(keyPos+1, kPos));
        return val;
      }
    }
  }
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::ProcStatInfo(string key) { 
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    string line;
    while(std::getline(stream, line)) {
      auto keyPos = line.find(' ');
      if (line.substr(0, keyPos) == key) {
        float val = stof(line.substr(keyPos+1));
        return val;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }