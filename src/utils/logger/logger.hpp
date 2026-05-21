#include <array>
#include <atomic>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int MaxStoredLogs = 200;

enum LogLevel{
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Fatal
};



struct Log{
  std::chrono::system_clock::time_point timestamp;
  LogLevel level;
  char file[30];
  char message[512];
};

class Logger{
  private:
  static std::array<Log, MaxStoredLogs> logBuffer;
  static inline std::atomic<bool> running = false;
  static inline std::ofstream file;
  static inline int readIndex = 0;
  static inline int writeIndex = 0;
  static inline std::thread worker_thread;
  static inline std::mutex bufferLock;

  static void writeLogs();
  static inline void flush(){
    std::cout.flush();
    file.flush();
  }

  static void bufferLog(Log log);
  static void workerFunction();

  public:
  static void startLogger(const std::string& logFile=""){
    running=true;
    if(logFile!="")file.open(logFile);
  }
  static void logMessage(LogLevel level,const char* msg);

};
