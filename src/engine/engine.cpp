#include "./engine.hpp"
#include "engine/meshManager/meshManager.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

void Engine::mainloop() {

  Scene scene;
  scene.addEntity(makeTriangle());
  auto camera = entityManager.newCamera();
  camera->cameraComp.eye = {0.0f, 0.0f, 5.0f};
  camera->cameraComp.center = {0.0f, 0.0f, 0.0f};
  camera->cameraComp.up = {0.0f, 1.0f, 0.0f};
  renderer.useCamera(camera);

  while (!window.windowShouldClose()) {
    renderer.flush();
    renderer.renderScene(scene);
    window.updateWindow();
  }
}

Entity &Engine::makeTriangle() {
  auto id = meshManager.makePrimitive(MeshManager::Primitive::Square,
                                      MeshManager::Color::Blue);
  Entity &e = entityManager.newEntity();
  e.renderComp = RenderComponent(id, 2, true);
  e.transformComp = TransformComponent{.position = {1.0f, 1.0f, 1.0f}};

  return e;
}
