#pragma once
#define GLFW_INCLUDE_NONE
#include "engine/graphics/batchManager/batchManager.hpp"
#include "engine/graphics/elementBuffer/elementBuffer.hpp"
#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/vertexArray/vertexArray.hpp"
#include "engine/graphics/vertexBuffer/vertexBuffer.hpp"
#include "engine/graphics/vertexLayout/vertexLayout.hpp"
#include "engine/meshManager/meshManager.hpp"
#include "engine/scene/scene.hpp"
#include <GLFW/glfw3.h>
#include <glad/gl.h>

class Renderer {
private:
  BatchManager batchManager;
  MeshManager &meshManager;
  VertexArray vao;
  VertexBuffer vbo;
  ElementBuffer ebo;
  Shader shader{VertexLayout::Pos};

public:
  Renderer(MeshManager &manager);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&other) = delete;
  static void initGLAD();

  void collectAndBatch(Scene &scene);
  void renderBatches();
  void flush();
};
