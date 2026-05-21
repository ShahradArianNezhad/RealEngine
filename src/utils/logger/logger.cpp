#include "./logger.hpp"
#include <format>


std::array<Log, MaxStoredLogs> Logger::logBuffer;


void Logger::writeLogs(){
  while(readIndex!=writeIndex){
    bufferLock.lock();
    auto& log = logBuffer[readIndex];
    auto time_t = std::chrono::system_clock::to_time_t(log.timestamp);
    std::string time_str = std::ctime(&time_t);
    time_str.pop_back();
    std::string level_str;
    switch(log.level){
      case LogLevel::Trace: level_str="TRACE"; break;
      case LogLevel::Debug: level_str="DEBUG"; break;
      case LogLevel::Info: level_str="INFO"; break;
      case LogLevel::Warn: level_str="WARN"; break;
      case LogLevel::Error: level_str="ERROR"; break;
      case LogLevel::Fatal: level_str="FATAL"; break;
    }
    std::string log_message = std::format("[{}][{}][{}]:{}\n", 
        time_str, level_str, log.file, log.message);
    std::cout << log_message;
    if(file.is_open()) file << log_message;
    readIndex = (readIndex+1)%MaxStoredLogs;
  }
  bufferLock.unlock();
}


void Logger::bufferLog(Log log){
  bufferLock.lock();
  logBuffer[writeIndex] = log;
  bufferLock.unlock();

  if((writeIndex+1)%MaxStoredLogs==readIndex){
    writeLogs();
    flush();
  }
  writeIndex = (writeIndex+1)%MaxStoredLogs;
}
