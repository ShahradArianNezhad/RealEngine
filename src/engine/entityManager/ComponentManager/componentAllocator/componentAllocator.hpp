#include "engine/entityManager/component/components.hpp"
#include <cstddef>
#include <iostream>


template <typename T>
class ComponentAllocator{

private:
  std::queue<size_t> unused;
  std::vector<T> components;
  std::unordered_map<EntityId, size_t> entityToIndex;
  std::vector<size_t> indexToEntity;

public:
  T getComponent(EntityId id){
    if(entityToIndex.contains(id))return components[entityToIndex[id]];
    std::cout << "wargning : getComponent called on entity which doesnt have that component" << std::endl;
    return T{};
  }


  void setComponent(EntityId id,T comp){
    if(entityToIndex.contains(id)){
      components[entityToIndex[id]] = comp;
      return;
    }
    size_t index;
    if(unused.empty())index = components.size();
    else{
      index = unused.front();
      unused.pop();
    }
    if(index>=components.size()){
      components.push_back(comp);
    }else{
      components[index]=comp;
    }
    entityToIndex[id]=index;
    if(index>=indexToEntity.size()){
      indexToEntity.push_back(id);
    }else{
      components[index]=comp;
    }
  }

  bool hasComponent(EntityId id){return entityToIndex.contains(id);};

  void deleteComponent(EntityId id){
    if(!entityToIndex.contains(id)){
      std::cout << "warning: trying to delete unexisting component" << std::endl;
      return;
    }
    size_t index = entityToIndex[id];
    entityToIndex.erase(id);
    indexToEntity[index]=UINT32_MAX;
    unused.push(index);
  }
  
};
