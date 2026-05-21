#pragma once
#include "./batch/batch.hpp"
#include "engine/entityManager/entityManager.hpp"
#include <unordered_map>

class BatchManager {
private:
  std::unordered_map<BatchKey, Batch> batches;
  EntityManager& entityManager;

public:
  BatchManager(EntityManager& eManager):entityManager(eManager) {};
  BatchKey submit(EntityId entity);
  std::unordered_map<BatchKey, Batch> &getBatches() { return batches; }
  void cleanBatches() { batches.clear(); }
};
