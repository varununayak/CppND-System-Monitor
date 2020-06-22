#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  void UpdateRam();
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime() const;                       // TODO: See src/process.cpp
  int mbRam_;

  // TODO: Declare any necessary private members
 private:
  int pid_;
};

#endif