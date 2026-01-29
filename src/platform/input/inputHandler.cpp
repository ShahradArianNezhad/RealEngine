#include "inputHandler.hpp"

InputHandler::InputHandler(GLFWwindow *window) : window(window) {}
bool InputHandler::checkKeyPress(int key) {
  return glfwGetKey(window, key) == GLFW_PRESS;
}
