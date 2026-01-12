#include "piksel/object.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace piksel
{
    void Object::setTransform(const glm::mat4& transform)
    {
      glm::vec3 scale;
      scale.x=glm::length(transform[0]);
      scale.y=glm::length(transform[1]);
      scale.z=glm::length(transform[2]);

      this->scale=glm::scale(glm::mat4(1.f),scale);

      this->rotate=glm::mat4(1.f);
      this->rotate[0]=transform[0]/scale.x;
      this->rotate[1]=transform[1]/scale.y;
      this->rotate[2]=transform[2]/scale.z;

      this->translate=glm::translate(glm::mat4(1.f),glm::vec3(transform[3]));
    }

    Object::Object()
      :translate(1.f),rotate(1.f),scale(1.f),color(Color::White)
    {
    }
}
