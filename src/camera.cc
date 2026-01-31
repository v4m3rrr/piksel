#include "piksel/camera.hh"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

namespace piksel
{
  Camera::Camera(const glm::vec3& pos, const glm::vec3& target)
    :cam_pos_(pos),target_pos_(target)
  {}

  void Camera::set(const glm::vec3& target, const glm::vec3& pos)
  {
    cam_pos_=pos;
    target_pos_=target;
  }

  void Camera::moveBy(const glm::vec3& delta_pos)
  {
    if(!enable_camera_)
      return;

    cam_pos_+=delta_pos;
    target_pos_+=delta_pos;
  }

  void Camera::moveLongitudinal(float value)
  {
    if(!enable_camera_)
      return;

    glm::vec3 delta_pos=glm::normalize(target_pos_-cam_pos_);
    delta_pos*=value;

    moveBy(delta_pos);
  }

  void Camera::moveLateral(float value)
  {
    if(!enable_camera_)
      return;

    glm::vec3 delta_pos=glm::cross(target_pos_-cam_pos_,up_);
    delta_pos=glm::normalize(delta_pos);
    delta_pos*=value;

    moveBy(delta_pos);
  }

  void Camera::rotateYaw(float radinas){
    if(!enable_camera_)
      return;

    glm::vec3 dir=target_pos_-cam_pos_;
    glm::mat4 rotate=glm::rotate(glm::mat4(1.f),radinas,up_);

    dir=glm::vec3(rotate*glm::vec4(dir,1.f));

    target_pos_=cam_pos_+dir;
  }

  void Camera::rotatePitch(float radinas){
    if(!enable_camera_)
      return;

    static float angle=0;
    if(glm::abs(angle+radinas)>=glm::radians(89.f)){
      return;
    }

    angle+=radinas;
    glm::vec3 dir=target_pos_-cam_pos_;
    glm::mat4 rotate=
      glm::rotate(glm::mat4(1.f),radinas,glm::cross(target_pos_-cam_pos_,up_));

    dir=glm::vec3(rotate*glm::vec4(dir,1.f));

    target_pos_=cam_pos_+dir;
  }

  glm::mat4 Camera::getCameraView() const
  {
    return glm::lookAt(cam_pos_,target_pos_,up_);
  }

  void Camera::enable(bool enable)
  {
    enable_camera_=enable;
  }
}
