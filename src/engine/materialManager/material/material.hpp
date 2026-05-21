#include "./texture/texture.hpp"
#include <cstdint>
#include <optional>

class Material {
public:
  std::optional<Texture> texture;

  Material() {};
  Material(std::string texPath) : texture(texPath) {}
  void setTexture(std::string imgPath){texture.emplace(Texture{imgPath});}
  void use() { if(texture)texture->bind(); }
};
