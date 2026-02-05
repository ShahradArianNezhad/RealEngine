#include "entityManager.hpp"
#include "./entity/entity.hpp"
#include <utility>

Entity &EntityManager::newEntity() {
  auto e = new Entity;
  entities.push_back(e);
  return *e;
}

Camera *EntityManager::newCamera() {
  auto e = new Camera;
  entities.push_back(e);
  return e;
}
