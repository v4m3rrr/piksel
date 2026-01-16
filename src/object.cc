#include "piksel/object.hh"

#include "piksel/color.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

namespace piksel
{
  Object::Object(
        std::shared_ptr<const Mesh> mesh,
        const glm::mat4& transform,
        const Color& color)
    :
      mesh_(mesh),
      transform_(transform),
      color_(color)
  {
  }

  void Object::draw(Shader& shader) const
  {
    shader.use();
    shader.set("trans",transform_);
    shader.set("color",color_.rgb());

    glLineWidth(1.f);

    mesh_->bind();
    glDrawElements(
        GL_LINES,mesh_->getIndices().size(),GL_UNSIGNED_INT,0);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to render object");
    }
    glBindVertexArray(0);
  }
}
