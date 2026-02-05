#include "renderer.hpp"
#include "engine/graphics/vertexLayout/vertexLayout.hpp"
#include "glad/gl.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <stdexcept>

void Renderer::flush() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::initGLAD() {
  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    throw std::runtime_error("ERROR: Failed to initialize glad");
  }
}
Renderer::Renderer(MeshManager &manager, MaterialManager &matManager)
    : meshManager(manager), materialManager(matManager) {
  initGLAD();
}

void Renderer::collectAndBatch(Scene &scene) {
  for (auto &entity : scene.collectEntities()) {
    if (entity.renderComp)
      batchManager.submit(entity);
  }
}

void Renderer::renderBatches() {

  glm::vec3 eye = currentCamera->cameraComp.eye;
  glm::vec3 center = currentCamera->cameraComp.center;
  glm::vec3 up = currentCamera->cameraComp.up;
  glm::mat4 view = glm::lookAt(eye, center, up);

  float fov = glm::radians(45.0f); // field of view in radians
  float aspect = 800.0f / 600.0f;  // screen width / height
  float near = 0.1f;               // near clipping plane
  float far = 100.0f;              // far clipping plane

  glm::mat4 projection = glm::perspective(fov, aspect, near, far);

  for (auto &[key, batch] : batchManager.getBatches()) {
    auto &mesh = meshManager.get(key.mesh);
    auto &mat = materialManager.get(key.material);
    shaderManager.useShader(mesh.layout);
    auto &shader = shaderManager.getShaderHandle(mesh.layout);
    gpu.useMesh(mesh);
    mat.use();
    for (auto &e : batch) {
      auto transform = glm::mat4(1.0f);
      if (e.transformComp) {
        transform = glm::translate(transform, e.transformComp->position);
      }
      shader.setunifotmMat4("view", view);
      shader.setunifotmMat4("model", transform);
      shader.setunifotmMat4("projection", projection);
      glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    }
  }
}

void Renderer::renderScene(Scene &scene) {
  if (!currentCamera)
    return;

  collectAndBatch(scene);
  renderBatches();
  batchManager.cleanBatches();
}

void Renderer::useCamera(Camera *cam) { currentCamera = cam; }
