#pragma once

#include "piksel/object.hh"
#include "piksel/mesh.hh"

#include <assimp/scene.h>

#include <string_view>
#include <vector>

namespace piksel
{
  class Model : public Object
  {
  public:
    Model(std::string_view filepath);
    virtual void draw(Shader& shader) const override;
  private:
    void processNode(aiNode * node, const aiScene * scene);
  private:
    std::vector<Mesh> meshes_;
  };
}
