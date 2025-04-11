#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  std::vector<std::string> cpuState = LinuxParser::CpuUtilization();
  float totalCPU = std::stof(cpuState[0]);
  float usedCPU = std::stof(cpuState[1]);
  return (usedCPU/totalCPU)*100;
}