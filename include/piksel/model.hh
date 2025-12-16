#pragma once

#include "piksel/object.hh"
#include "piksel/mesh.hh"

#include <tiny_gltf.h>

#include <string_view>
#include <vector>

namespace piksel
{
  class Model : public Object
  {
  public:
    Model()=default;
    Model(std::string_view filepath);
    virtual void draw(Shader& shader) const override;
  private:
    void bindModelNodes(
        const tinygltf::Model& model, 
        const tinygltf::Node& node, 
        const glm::mat4& transform);
  private:
    std::vector<Mesh> meshes_;
  };
}
