#include "./engine.hpp"
#include "engine/entityManager/component/components.hpp"
#include "engine/meshManager/meshManager.hpp"
#include <chrono>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <thread>
#include "../game/game.hpp"


Engine::Engine(){
  SceneId defaultScene = newScene();
  renderer.useScene(defaultScene);
}



EntityId Engine::makeSprite(float x,float y,float width,float height,std::string spritePath){
  auto meshId = meshManager.makePrimitive(MeshManager::Primitive::SquareSprite);
  auto matId = materialManager.newMat(spritePath);
  auto transformComp = TransformComponent{
      .position = {x, y, 0.0f},
      .scale = {width, height, 1.0f},
      .rotation=0
  };
  auto id = entityManager.newEntity(RenderComponent{meshId,matId},transformComp);
  renderer.addEntity(id);
  return id;

}

EntityId Engine::makeRect(float x, float y, float width, float height) {
  auto meshId = meshManager.makePrimitive(MeshManager::Primitive::Square);
  auto matId = materialManager.newMat();
  auto transformComp = TransformComponent{
      .position = {x, y, 0.0f},
      .scale = {width, height, 1.0f},
  };

  auto id = entityManager.newEntity(RenderComponent{meshId,matId},transformComp);
  renderer.addEntity(id);
  return id;
}

EntityId Engine::makeCircle(float x, float y, float r) {
  auto meshId = meshManager.makePrimitive(MeshManager::Primitive::Circle);
  auto matId = materialManager.newMat();
  auto transformComp = TransformComponent{
      .position = {x, y, 0.0f},
      .scale = {r, r, 1.0f},
  };

  auto id = entityManager.newEntity(RenderComponent{meshId,matId},transformComp);
  renderer.addEntity(id);
  return id;
}

void Engine::useCamera(EntityId camera,SceneId sceneid){
  auto scene = sceneManager.get(sceneid);
  if(scene!=nullptr) scene->setActiveCamera(camera);
  else std::cout << "error : cannot set camera on non existing scene" << std::endl;
}



void Engine::syncFPS(){
  double dt = clock.getDeltaTime();
  double targetFrameTime = (targetFPS > 0) ? 1.0 / targetFPS : 0.0;
  if (targetFPS > 0 && dt < targetFrameTime) {
    clock.sleep(targetFrameTime - dt);
  }
}


void Engine::run(Game* game) {
    game->init();
    clock.reset();
    while (!window.windowShouldClose()) {
        double dt = clock.getDeltaTime();
        clock.setTimestamp();
        syncFPS();
        game->update(dt);
        renderer.flush();
        renderer.renderCurrentScene();
        window.updateWindow();
    }
}


void Engine::sleep(int ms){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
