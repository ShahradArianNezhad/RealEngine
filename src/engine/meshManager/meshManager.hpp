#pragma once
#include "./mesh/mesh.hpp"
#include "core/idManager/idManager.hpp"
#include <iostream>
#include <unordered_map>

using MeshID = unsigned int;

class MeshManager {
private:
  IDManager idManager{};
  std::unordered_map<MeshID, Mesh> meshes;

public:
  enum class Primitive { Triangle = 0, Square };
  enum class Color {
    White = 0xFFFFFF,
    Black = 0x000000,
    Red = 0xFF0000,
    Blue = 0x0000FF,
    Green = 0x00FF00
  };

  MeshManager();
  Mesh &get(MeshID id) { return meshes[id]; };
  MeshID makePrimitive(Primitive, Color);
  MeshID submit(Mesh mesh) {
    auto id = idManager.get();
    meshes.emplace(id, mesh);
    return id;
  }
};
