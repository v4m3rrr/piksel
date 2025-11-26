#pragma once

#include <glm/glm.hpp>

namespace piksel
{
  class Camera
  {
  public:
    Camera(const glm::vec3& pos, const glm::vec3& target);
    void moveBy(const glm::vec3& delta_pos);
    glm::mat4 getCameraView() const;
  private:
    glm::vec3 cam_pos_;
    glm::vec3 target_pos_;
    glm::vec3 up_={0.f,1.f,0.f};
  };
}
