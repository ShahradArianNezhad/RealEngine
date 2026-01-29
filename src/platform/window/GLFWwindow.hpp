#pragma once
#define GLFW_INCLUDE_NONE
#include "platform/input/inputHandler.hpp"
#include <GLFW/glfw3.h>
#include <glad/gl.h>

class EngineWindow {
public:
  InputHandler inputHandler{window};

  EngineWindow(uint32_t w, uint32_t h);
  EngineWindow(const EngineWindow &) = delete;
  EngineWindow &operator=(const EngineWindow &) = delete;
  EngineWindow(EngineWindow &&) = delete;
  ~EngineWindow();
  bool windowShouldClose();
  void updateWindow();
  void setViewport();

private:
  GLFWwindow *window;

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  void initGLFW();
  void createWindow();
  void cleanup();
  void checkWindowInit();

  static void sizeChange_callback(GLFWwindow *_, int width, int height) {
    glViewport(0, 0, width, height);
  }
};
