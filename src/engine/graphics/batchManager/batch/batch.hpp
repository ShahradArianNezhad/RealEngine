#pragma once
#include "engine/entityManager/component/components.hpp"
#include "engine/materialManager/materialManager.hpp"
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>

struct BatchKey {
  MeshID mesh;
  MaterialID material;
  bool operator==(const BatchKey &other) const {
    if (other.mesh == mesh && other.material == material) {
      return true;
    }
    return false;
  };
};

namespace std {
template <> struct hash<BatchKey> {
  size_t operator()(const BatchKey &k) const noexcept {
    return std::hash<int>{}(k.mesh);
  }
};
} // namespace std

class Batch {
private:
  std::vector<EntityId> entities;
  std::vector<mat4> transformInstances;
  std::vector<vec4> colorInstances;
  BatchKey key;

public:
  Batch() {};
  Batch(BatchKey aKey) : key(aKey) {};
  BatchKey getKey() { return key; };
  std::vector<EntityId> getEntities() { return entities; };
  void submit(EntityId entity) { entities.push_back(entity); }
  void addTransform(mat4 transform){transformInstances.push_back(transform);};
  void addColor(vec4 color){colorInstances.push_back(color);};
  std::vector<mat4>& getModelInstanceData(){return transformInstances;};
  std::vector<vec4>& getColorInstanceData(){return colorInstances;};
  auto begin() { return entities.begin(); }
  auto end() { return entities.end(); }
  size_t size(){return entities.size();}
};
