#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
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

// TODO: Read and return the system memory utilization, it does not give the expected Value!!!
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float memTotal;
  float memFree;
  float memAvailable;
  float buffer;
  string value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  memTotal = std::stof(value.substr(start, end - start));
        }
        if (key == "MemFree") {
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  memFree = std::stof(value.substr(start, end - start));
        }
        if (key == "MemAvailable") {
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  memAvailable = std::stof(value.substr(start, end - start));
        }
         if (key == "Buffer") {
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  buffer = std::stof(value.substr(start, end - start));
        }
      }
    }
  }
  //std::cout << memFree <<   "," << memTotal<< std::endl;
  return memTotal - memFree;  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long upTime, totalTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime >> totalTime;
  }
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization, Results are not being displayed!!!
vector<string> LinuxParser::CpuUtilization() { 
  //string cpu0, cpu1, cpu2,cpu3,cpu4,cpu5,cpu6,cpu7,cpu8,cpu9;
  string non,totalCPU, usedCPU;
  //CPUStates cpu;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>non >> totalCPU >> usedCPU;
    //linestream >> cpu0 >> cpu1>>  cpu2 >> cpu3 >> cpu4 >> cpu5 >> cpu6 >> cpu7 >> cpu8 >> cpu9;
  }

	//std::vector<string> result = {cpu0, cpu1, cpu2,cpu3,cpu4,cpu5,cpu6,cpu7,cpu8,cpu9};
    std::vector<string> result {totalCPU,usedCPU};
    //std::cout << result[0] <<std::endl;
    return result; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  int nOfProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {

      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  nOfProcesses = std::stoi(value.substr(start, end - start));
        }
      }
    }
  }
  return nOfProcesses;  
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  int runningProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {

      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          size_t start = value.find_first_not_of(' ');    
          size_t end = value.find(' ', start);
   		  runningProcesses = std::stoi(value.substr(start, end - start));
        }
      }
    }
  }
  return runningProcesses;  

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
