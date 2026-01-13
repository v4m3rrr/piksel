#pragma once

#include "piksel/IDrawable.hh"
#include "piksel/shader.hh"
#include "piksel/color.hh"
#include "piksel/mesh.hh"

#include <glm/glm.hpp>
#include <memory>

namespace piksel
{
  class Object : public IDrawable
  {
  public:
    Object(
        std::shared_ptr<const Mesh> mesh,
        const glm::mat4& transform=glm::mat4(1.f),
        const Color& color=Color::White);
    virtual ~Object() noexcept=default;

    virtual void draw(Shader& shader) const override;

    const glm::mat4& getTransform() const { return transform_;}
    void setTransform(const glm::mat4& transform) {transform_=transform;}

    const Color& getColor() const {return color_;}
    void setColor(const Color& color) {color_=color;}

    std::shared_ptr<const Mesh> getMesh() const {return mesh_;}
  private:
    std::shared_ptr<const Mesh> mesh_;

    glm::mat4 transform_;
    Color color_;
  };
}
