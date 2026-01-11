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
    Model(float stroke);
    Model(std::string_view filepath, float stroke);

    virtual void draw(Shader& shader) const override;
    const std::vector<Mesh>& getMeshes() const;

    void addMesh(Mesh&& mesh);
  private:
    void bindModelNodes(
        const tinygltf::Model& model, 
        const tinygltf::Node& node, 
        const glm::mat4& transform);
  private:
    float stroke_;
    std::vector<Mesh> meshes_;
  };
}
