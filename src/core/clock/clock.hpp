#include <chrono>
#include <thread>




class Clock{
public:
  Clock(){
    last = std::chrono::high_resolution_clock::now();
  }
  double getDeltaTime(){
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = now - last;
    last = now;
    return delta.count(); 
  }

  void reset(){last=std::chrono::high_resolution_clock::now();}

  void sleep(double s){
    long ms = s*1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }

private:
  std::chrono::high_resolution_clock::time_point last;
};
