#pragma once
#include "./component/components.hpp"
#include <optional>

struct Entity {
  std::optional<TransformComponent> transformComp;
  std::optional<RenderComponent> renderComp;
};

struct Camera : Entity {
  CameraComponent cameraComp;
};
