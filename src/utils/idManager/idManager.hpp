#pragma once

#include <queue>
class IDManager {
private:
  unsigned int next_count = 0;
  std::queue<unsigned int> freeIds;

public:
  IDManager() {};
  IDManager(unsigned int start) { next_count = start; };
  unsigned int get();
  void release(unsigned int id);
};
