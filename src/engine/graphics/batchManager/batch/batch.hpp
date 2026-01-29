#include "engine/scene/entity/entity.hpp"
#include <vector>

struct BatchKey {
  MeshID mesh;
  bool operator==(const BatchKey &other) const {
    if (other.mesh == mesh) {
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
  std::vector<Entity> entities;
  BatchKey key;

public:
  Batch() {};
  Batch(BatchKey aKey) : key(aKey) {};
  BatchKey getKey() { return key; };
  std::vector<Entity> getEntities() { return entities; };
  void submit(Entity &entity) { entities.push_back(entity); }
};
