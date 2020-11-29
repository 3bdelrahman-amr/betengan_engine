#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"../src/SomeDef.h"
#include"CameraController.h"
// Dirty Flags are programming pattern where we only regenerate some output if:
      // 1- The inputs were changed.
      // 2- The output is needed.
      // Where we have flags for whether the View, Projection & ViewProjection matrices needed to be regenerated.


class Camera {
public:

    CameraController* controller;
    static const uint8_t V_DIRTY = 1, 
                         P_DIRTY = 2, 
                         VP_DIRTY = 4;
    uint8_t dirtyFlags = 0;
   

    // The camera position, camera forward direction and camera up direction
    glm::vec3 eye = { 0, 0, 0 }, 
              direction = { 0, 0, -1 }, 
              up = { 0, 1, 0 };

    CameraType type = CameraType::Perspective;

    // The field_of_view_y is in radians and is only used for perspective cameras
    // The orthographic_height is only used for orthographic cameras
    float field_of_view_y = glm::radians(90.0f), 
          orthographic_height = 2.0f, 
          aspect_ratio = 1.0f, 
          near = 0.01f, far = 100.0f;

    glm::mat4 V{},  //view matrix 
              P{}, // projection matrix
              VP{};  // view * projection matrix

};