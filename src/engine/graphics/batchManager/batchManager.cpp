#include "./batchManager.hpp"

void BatchManager::submit(Entity &entity) {
  BatchKey key = {.mesh = entity.mesh};
  if (!batches.contains(key)) {
    batches[key] = Batch(key);
  }
  batches[key].submit(entity);
}
