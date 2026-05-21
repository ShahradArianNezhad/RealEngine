#pragma once
#include "engine/materialManager/materialManager.hpp"
#include "engine/meshManager/meshManager.hpp"
#include <glm/glm.hpp>

using ComponentId = uint32_t;
using EntityId = uint32_t;

struct RenderComponent {
  MeshID mesh;
  MaterialID material;
  uint32_t color=0xFFFFFFFF;
  bool visible=true;
};

struct TransformComponent {
  vec3 position={0,0,0};

  vec3 scale={0,0,0};
  float rotation={0};
};

struct CircleColliderComponent{
  float radius;
  vec2 offest={0,0};
};

struct RectColliderComponent{
  vec2 offest={0,0};
  vec2 scale={0,0};
  float rotation;
};

enum ComponentType{
  RENDER,
  TRANSFORM,
  CIRCLECOLLIDER,
  RECTCOLLIDER,
};

template<ComponentType I>
struct EnumToType {
  using type = std::tuple_element_t<static_cast<size_t>(I), 
        std::tuple<RenderComponent,TransformComponent,CircleColliderComponent,RectColliderComponent>>;
};


struct ComponentSlot {
  ComponentType type;
  ComponentId id=UINT32_MAX;
};
