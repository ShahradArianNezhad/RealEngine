#pragma once
#include "engine/eventManager/eventManager.hpp"
#include "utils/logger/logger.hpp"
#include <cstdint>
#include <vector>

using SceneId = uint32_t;

class Scene {
private:
  SceneId id;
  std::vector<EntityId> entities;
  EntityId camera=UINT32_MAX;
  EventManager& eventManager;
  subscriptionId subId;

public:
  Scene(SceneId id,EventManager& eManager):id(id),eventManager(eManager){
    subId = eventManager.subscribe<EntityDestroyedEvent>(
        [this](const EntityDestroyedEvent& e) {
        entityDestroyedEventHandler(e);
        });
  };
  ~Scene(){
    LOG_DEBUG("scene destructed id:{}",id);
    eventManager.unsubscribe<EntityDestroyedEvent>(subId);
  }
  std::vector<EntityId> &collectEntities() {return entities;}

  void addEntity(EntityId entity) {
    LOG_DEBUG("entity:{} added to scene:{}",entity,id);
    entities.push_back(entity);

  };
  void entityDestroyedEventHandler(const EntityDestroyedEvent& event){
    LOG_DEBUG("entity:{} removed from scene:{}", event.id, id);

    for(size_t i = 0; i < entities.size(); i++) {
      if(entities[i] == event.id) {
        entities[i] = std::move(entities.back());
        entities.pop_back();
        return; 
      }
    }
    LOG_WARN("delete entity called on entity:{} not found in scene:{}", event.id, id);
  }

  void setActiveCamera(EntityId cam){
    LOG_DEBUG("camera:{} set active in scene:{}",cam,id);
    camera=cam;
  }
  EntityId getActiveCamera(){
    return camera;
  }
};
