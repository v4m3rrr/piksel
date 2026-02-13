#pragma once

#include <glm/glm.hpp>

namespace piksel
{
  class Camera
  {
  public:
    Camera(
        const glm::vec3& pos, 
        const glm::vec3& target,
        const glm::vec3& up={0.f,1.f,0.f});

    void set(const glm::vec3& target, const glm::vec3& pos);

    void moveBy(const glm::vec3& delta_pos);
    void moveLongitudinal(float value);
    void moveLateral(float value);

    void rotateYaw(float radians);
    void rotatePitch(float radians);

    glm::mat4 getCameraView() const;

    float getMovementSpeed() const {return movement_speed_;}
    float getRotationSpeed() const {return rotation_speed_;}

    void setMovementSpeed(float speed) {movement_speed_=speed;}
    void setRotationSpeed(float speed) {rotation_speed_=speed;}
  private:
    glm::vec3 cam_pos_;
    glm::vec3 target_pos_;
    glm::vec3 up_;

    float movement_speed_=10.f;
    float rotation_speed_=10.f;
  };
}
