#pragma once
#include "engine/entityManager/entityManager.hpp"
#include "engine/materialManager/materialManager.hpp"
#define GLFW_INCLUDE_NONE
#include "engine/graphics/batchManager/batchManager.hpp"
#include "engine/graphics/gpuBuffers/gpuBuffers.hpp"
#include "engine/graphics/shaderManager/shaderManager.hpp"
#include "engine/meshManager/meshManager.hpp"
#include "engine/sceneManager/scene/scene.hpp"
#include "engine/sceneManager/sceneManager.hpp"
#include <GLFW/glfw3.h>
#include <glad/gl.h>

class Renderer {
private:
  MeshManager &meshManager;
  MaterialManager &materialManager;
  SceneManager& sceneManager;
  EntityManager& entityManager;
  BatchManager batchManager{entityManager};
  GpuBuffers gpu;
  ShaderManager shaderManager;
  SceneId currentScene=0;
  static mat4 projectionMatrix;

  void getGlErrors();
  void collectAndBatch(Scene *scene);
  void renderBatches();
  mat4 getViewMatrix();
  static mat4 getProjectionMatrix();
  mat4 makeModelMatrix(EntityId id);
 

public:
  Renderer(MeshManager &manager, MaterialManager &matManager,SceneManager& sceneManager,EntityManager& entityManager);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&other) = delete;
  static void initGLAD();
  static void recalculateProjectionMatrix(){Renderer::projectionMatrix=getProjectionMatrix();};

  void useScene(SceneId scene) { currentScene = scene; };
  void addEntity(EntityId e){sceneManager.get(currentScene)->addEntity(e);}
  SceneId getCurrentScene(){return currentScene;}
  void flush();
  void renderCurrentScene();

};
