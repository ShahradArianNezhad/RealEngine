#include "./idManager.hpp"

unsigned int IDManager::get() {
  if (freeIds.empty()) {
    return next_count++;
  } else {
    auto id = freeIds.front();
    freeIds.pop();
    return id;
  }
}

void IDManager::release(unsigned int id) { freeIds.push(id); }
