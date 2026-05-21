#include "renderer.hpp"
#include "engine/entityManager/component/components.hpp"
#include "engine/graphics/gpuBuffers/vertexBuffer/vertexBuffer.hpp"
#include "engine/sceneManager/sceneManager.hpp"
#include "glad/gl.h"
#include "platform/window/GLFWwindow.hpp"
#include <cstdint>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <stdexcept>


mat4 Renderer::projectionMatrix = mat4(1.0f);

void Renderer::flush() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::initGLAD() {
  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    throw std::runtime_error("ERROR: Failed to initialize glad");
  }
}
Renderer::Renderer(MeshManager &manager, MaterialManager &matManager,SceneManager& sManager,EntityManager& eManager)
    : meshManager(manager), materialManager(matManager),sceneManager(sManager),entityManager(eManager) {
  initGLAD();
  Renderer::projectionMatrix = getProjectionMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LEQUAL);
}

void Renderer::collectAndBatch(Scene *scene) {
  for (auto entityId : scene->collectEntities()) {
    if(entityId==UINT32_MAX)continue;
    if (entityManager.componentManager.hasComponent<ComponentType::RENDER>(entityId))
      batchManager.submit(entityId);
  }
}

mat4 Renderer::getProjectionMatrix() {
  float w = static_cast<float>(Screen::width);
  float h = static_cast<float>(Screen::height);
  return glm::ortho(0.0f, w, h, 0.0f, -100.0f, 100.0f);
}


void Renderer::renderBatches() {

  auto view = getViewMatrix();
  for (auto &[key, batch] : batchManager.getBatches()) {
    auto &mesh = meshManager.get(key.mesh);
    auto &mat = materialManager.get(key.material);
    auto &shader = shaderManager.getShaderHandle(mesh.layout);
    shader.use();
    VertexBuffer modelInstanceVBO = gpu.makeInstanceVBO(batch.getModelInstanceData());
    gpu.useInstanceMat4(modelInstanceVBO,3);
    VertexBuffer colorInstanceVBO = gpu.makeInstanceVBO(batch.getColorInstanceData());
    gpu.useInstanceVec4(colorInstanceVBO,2);
    shader.setunifotmMat4("projection", Renderer::projectionMatrix);
    shader.setunifotmMat4("view", view);
    gpu.useMesh(mesh);
    mat.use();
    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0, batch.size());
  }
  getGlErrors();

}

void Renderer::renderCurrentScene() {
  if (!sceneManager.get(currentScene)) {
    std::cout << "ERROR: rendering invalid scene" << std::endl;
    return;
  }
  if(sceneManager.get(currentScene)->getActiveCamera()==UINT32_MAX){
    std::cout << "warning: not using a camera" << std::endl;
    return;
  }
  collectAndBatch(sceneManager.get(currentScene));
  renderBatches();
  batchManager.cleanBatches();
}

mat4 Renderer::getViewMatrix(){
  mat4 view = mat4(1.0f);
  auto camera = sceneManager.get(currentScene)->getActiveCamera();
  view = glm::translate(view, entityManager.getPos(camera));
  return view;
}

void Renderer::getGlErrors(){
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }
}


