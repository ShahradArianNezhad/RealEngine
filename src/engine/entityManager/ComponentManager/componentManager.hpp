#pragma once
#include "engine/entityManager/component/components.hpp"
#include "./componentAllocator/componentAllocator.hpp"
#include <tuple>


using ComponentId = uint32_t;

class ComponentManager {
private:
  std::tuple<
  ComponentAllocator<TransformComponent>,
  ComponentAllocator<RenderComponent>,
  ComponentAllocator<CircleColliderComponent>,
  ComponentAllocator<RectColliderComponent>
    > allocators;

public:
  template<ComponentType T>
    EnumToType<T>::type getComponent(EntityId id){
      auto allocator = std::get<ComponentAllocator<typename EnumToType<T>::type>>(allocators);
      return allocator.getComponent(id);
    }

  template<ComponentType T>
    void setComponent(EntityId id,typename EnumToType<T>::type comp){
      auto& allocator = std::get<ComponentAllocator<typename EnumToType<T>::type>>(allocators);
      allocator.setComponent(id,comp);
    }


  template<ComponentType T>
    void deleteComponent(EntityId id){
      auto& allocator = std::get<ComponentAllocator<typename EnumToType<T>::type>>(allocators);
      allocator.deleteComponent(id);
    }


  template<ComponentType T>
    bool hasComponent(EntityId id){
      auto& allocator = std::get<ComponentAllocator<typename EnumToType<T>::type>>(allocators);
      return allocator.hasComponent(id);
    };
  
};
