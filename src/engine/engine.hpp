#pragma once
#include "../platform/window/GLFWwindow.hpp"
#include "./graphics/renderer/renderer.hpp"
#include "engine/entityManager/entity/entity.hpp"
#include "engine/entityManager/entityManager.hpp"
#include "engine/materialManager/materialManager.hpp"
#include "engine/meshManager/meshManager.hpp"

class Engine {
private:
  EngineWindow window{800, 600};
  MeshManager meshManager;
  MaterialManager materialManager;
  EntityManager entityManager;

public:
  Renderer renderer{meshManager, materialManager};
  Engine() {};
  Entity &makeTriangle();
  void mainloop();
};
