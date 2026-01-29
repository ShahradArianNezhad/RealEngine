#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <vector>

class Vertex {
private:
  glm::vec3 position;
  std::optional<glm::vec3> color;
  std::optional<glm::vec2> textureCoords;
  void addPosition(std::vector<float> &aVertex);
  void addColor(std::vector<float> &aVertex);
  void addTextureCoords(std::vector<float> &aVertex);

public:
  Vertex(glm::vec3 aPosition) : position(aPosition) {}
  Vertex(glm::vec3 aPosition, glm::vec3 aColor)
      : position(aPosition), color(aColor) {};
  Vertex(glm::vec3 aPosition, glm::vec2 aTextureCoords)
      : position(aPosition), textureCoords(aTextureCoords) {};
  Vertex(glm::vec3 aPosition, glm::vec3 aColor, glm::vec2 aTextureCoords)
      : position(aPosition), color(aColor), textureCoords(aTextureCoords) {};

  static std::vector<float> mergeVertices(std::vector<Vertex> vertices);

  std::vector<float> getVertexData();
};
