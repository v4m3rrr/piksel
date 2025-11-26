#include "piksel/camera.hh"
#include "glm/ext/matrix_transform.hpp"

namespace piksel
{
  Camera::Camera(const glm::vec3& pos, const glm::vec3& target)
    :cam_pos_(pos),target_pos_(target)
  {}

  void Camera::moveBy(const glm::vec3& delta_pos)
  {
    cam_pos_+=delta_pos;
    target_pos_+=delta_pos;
  }

  glm::mat4 Camera::getCameraView() const
  {
    return glm::lookAt(cam_pos_,target_pos_,up_);
  }
}
