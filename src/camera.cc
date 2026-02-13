#include "piksel/camera.hh"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

namespace piksel
{
  Camera::Camera(
      const glm::vec3& pos, 
      const glm::vec3& target,
      const glm::vec3& up)
    :cam_pos_(pos),target_pos_(target),up_(up)
  {}

  void Camera::set(const glm::vec3& target, const glm::vec3& pos)
  {
    cam_pos_=pos;
    target_pos_=target;
  }

  void Camera::moveBy(const glm::vec3& delta_pos)
  {
    cam_pos_+=delta_pos;
    target_pos_+=delta_pos;
  }

  void Camera::moveLongitudinal(float value)
  {
    value*=movement_speed_;

    glm::vec3 delta_pos=glm::normalize(target_pos_-cam_pos_);
    delta_pos*=value;

    moveBy(delta_pos);
  }

  void Camera::moveLateral(float value)
  {
    value*=movement_speed_;

    glm::vec3 delta_pos=glm::cross(target_pos_-cam_pos_,up_);
    delta_pos=glm::normalize(delta_pos);
    delta_pos*=value;

    moveBy(delta_pos);
  }

  void Camera::rotateYaw(float radians)
  {
    radians*=rotation_speed_;

    glm::vec3 dir=target_pos_-cam_pos_;
    glm::mat4 rotate=glm::rotate(glm::mat4(1.f),radians,up_);

    dir=glm::vec3(rotate*glm::vec4(dir,1.f));

    target_pos_=cam_pos_+dir;
  }

  void Camera::rotatePitch(float radians)
  {
    radians*=rotation_speed_;

    static float angle=0;
    if(glm::abs(angle+radians)>=glm::radians(89.f))
      return;

    angle+=radians;
    glm::vec3 dir=target_pos_-cam_pos_;
    glm::mat4 rotate=
      glm::rotate(glm::mat4(1.f),radians,glm::cross(target_pos_-cam_pos_,up_));

    dir=glm::vec3(rotate*glm::vec4(dir,1.f));

    target_pos_=cam_pos_+dir;
  }

  glm::mat4 Camera::getCameraView() const
  {
    return glm::lookAt(cam_pos_,target_pos_,up_);
  }
}
