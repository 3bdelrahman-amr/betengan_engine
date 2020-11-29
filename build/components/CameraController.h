#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"../src/SomeDef.h"


class CameraController
{
     public:

    float yaw, pitch;
    glm::vec3 position;

    float yaw_sensitivity, pitch_sensitivity, fov_sensitivity;
    glm::vec3 position_sensitivity;
    float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.
    bool mouse_locked = false;
};

