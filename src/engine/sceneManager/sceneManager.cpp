#include "./sceneManager.hpp"
#include <stdexcept>


SceneId SceneManager::newScene(){
  auto id = idManager.get();
  scenes.try_emplace(id, eventManager);
  return id;
}


Scene* SceneManager::get(SceneId id) {
    auto it = scenes.find(id);
    if (it == scenes.end())
        throw std::runtime_error("invalid sceneId");

    return &it->second;
}
