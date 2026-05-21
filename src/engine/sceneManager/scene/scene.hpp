#pragma once
#include "engine/eventManager/eventManager.hpp"
#include <cstdint>
#include <vector>


class Scene {
private:
  std::vector<EntityId> entities;
  std::vector<uint32_t> empty_slots;
  EntityId camera=UINT32_MAX;
  EventManager& eventManager;
  subscriptionId subId;

public:
  Scene(EventManager& eManager):eventManager(eManager){
    subId = eventManager.subscribe(
        [this](const EntityDestroyedEvent& e) {
        entityDestroyedEventHandler(e);
        });
  };
  ~Scene(){eventManager.unsubscribe(subId);}
  std::vector<EntityId> &collectEntities() {return entities;}

  void addEntity(EntityId entity) {
    if(empty_slots.empty())entities.push_back(entity);
    else {
      entities[empty_slots.back()]=entity;
      empty_slots.pop_back();
    }

  };
  void entityDestroyedEventHandler(const EntityDestroyedEvent& event){
    for(size_t i=0;i<entities.size();i++){
      if(entities[i]==event.id){
        entities[i]=UINT32_MAX;
        empty_slots.push_back(i);
        break;
      }
    }
  }

  void setActiveCamera(EntityId cam){camera=cam;}
  EntityId getActiveCamera(){
    return camera;
  }
};
