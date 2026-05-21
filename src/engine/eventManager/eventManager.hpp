#pragma once
#include "engine/entityManager/component/components.hpp"
#include "utils/idManager/idManager.hpp"

struct EntityDestroyedEvent{
  EntityId id;
};


using subscriptionId = uint32_t;

class EventManager{

public:
  using Handler = std::function<void(const EntityDestroyedEvent&)>;

   subscriptionId subscribe(Handler handler){
    auto id = idManager.get();
    if(id>=listeners.size()){
      listeners.push_back(handler);
    }else{
      listeners[id]=handler;
    }
    return id;
  }

  void unsubscribe(subscriptionId id){listeners[id]=nullptr;}

  void emit(const EntityDestroyedEvent& event){
    for(auto& listener:listeners){
      if(listener!=nullptr){
        listener(event);
      };

    }
  }


private:
  std::vector<Handler> listeners;
  IDManager idManager;


};
