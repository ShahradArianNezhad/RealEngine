#pragma once
#include <glm/glm.hpp>
#include "utils/types.hpp"
#include <optional>
#include <vector>

class Vertex {
private:
  vec3 position;
  std::optional<vec3> color;
  std::optional<vec2> textureCoords;
  void addPosition(std::vector<float> &aVertex);
  void addColor(std::vector<float> &aVertex);
  void addTextureCoords(std::vector<float> &aVertex);

public:
  Vertex(vec3 aPosition) : position(aPosition) {}
  Vertex(vec3 aPosition, vec3 aColor)
      : position(aPosition), color(aColor) {};
  Vertex(vec3 aPosition, vec2 aTextureCoords)
      : position(aPosition), textureCoords(aTextureCoords) {};
  Vertex(vec3 aPosition, vec3 aColor, vec2 aTextureCoords)
      : position(aPosition), color(aColor), textureCoords(aTextureCoords) {};

  static std::vector<float> mergeVertices(std::vector<Vertex> vertices);

  std::vector<float> getVertexData();
};
