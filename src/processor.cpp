#include <vector>
#include <string>
#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() {
    std::vector<std::string> cpuUtilVals = LinuxParser::CpuUtilization();
    std::vector<long int> cpuUtilIntVals;
    std::transform(cpuUtilVals.begin(), cpuUtilVals.end(), std::back_inserter(cpuUtilIntVals),
               [](const std::string& str) { return std::stoi(str); });
    
    using namespace LinuxParser;
    // CPU Percentage formula: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    long int Idle = cpuUtilIntVals[CPUStates::kIdle_] + cpuUtilIntVals[CPUStates::kIOwait_]; 
    long int NonIdle = cpuUtilIntVals[CPUStates::kUser_] + cpuUtilIntVals[CPUStates::kNice_] +
         cpuUtilIntVals[CPUStates::kSystem_] + cpuUtilIntVals[CPUStates::kIRQ_] +
          cpuUtilIntVals[CPUStates::kSoftIRQ_] + cpuUtilIntVals[CPUStates::kSteal_];
    long int Total = Idle + NonIdle;
    // Differentiate: actual value minus the previous one
    static long int PrevTotal = 0;
    static long int PrevIdle = 0;
    long int totald = Total - PrevTotal;
    long int idled = Idle - PrevIdle;
    auto CPU_Percentage = (totald - idled) / float(totald);
    PrevTotal = Total;
    PrevIdle = Idle;
    return CPU_Percentage;
 }