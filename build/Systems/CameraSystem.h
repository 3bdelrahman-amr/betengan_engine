//#pragma once
#ifndef CAMERA_SYSTEM
#define CAMERA_SYSTEM
//#include"../src/EngineApplication.h"
#endif // !CAMERA_SYSTEM
//#include"application.hpp"
//#include"application.hpp"
#include"../src/Manager.h"
//#include"../src/System.h"
#include"ComponentsDef.h"
#include"../src/Application/input/mouse.h"
#include"../src/Application/input/keyboard.h"

//class EngineApplication;

class CameraSystem {

    Manager* mngr = nullptr;
   // EngineApplication* app;
    Betngan::Mouse* mouse;
    Betngan::Keyboard* keyboard;
    GLFWwindow* win_ptr;
    
    
public:
   
    /////////////////////////////////
    void SetManger(Manager* m) {
        mngr = m;
    }
    void SetEngineApp_ptr(Betngan::Mouse*m, Betngan::Keyboard*k,GLFWwindow*w) {

        mouse = m, keyboard = k,win_ptr=w;
    }

    //Camera functions
    
    
    ////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // Setup the camera as a perspective camera
    void setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far,Entity e) {
        auto cmra = mngr->GetComponent< Camera>(e);
        
        cmra->type = CameraType::Perspective;
        cmra->field_of_view_y = field_of_view_y;
        cmra->aspect_ratio = aspect_ratio;
        cmra->near = near;
        cmra->far = far;
        cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY; // Both P & VP need to be regenerated
        //mngr->AddComponent(e, cmra);//add
    }
    ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
    // Setup the camera as an orthographic camera
    void setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        cmra->type = CameraType::Orthographic;
        cmra->orthographic_height = orthographic_height;
        cmra->aspect_ratio = aspect_ratio;
        cmra->near = near;
        cmra->far = far;
        cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY; // Both P & VP need to be regenerated
        //add
    }
    ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

    void setType(CameraType _type, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->type != _type) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->type = _type;
          //  mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
    void setOrthographicSize(float orthographic_height, Entity e)
    {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->orthographic_height != orthographic_height) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->orthographic_height = orthographic_height;
           // mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
    void setVerticalFieldOfView(float field_of_view_y, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->field_of_view_y != field_of_view_y) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->field_of_view_y = field_of_view_y;
          //  mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
    void setAspectRatio(float aspect_ratio, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->aspect_ratio != aspect_ratio) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->aspect_ratio = aspect_ratio;
            //mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setNearPlane(float near, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->near != near) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->near = near;
           // mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setFarPlane(float far, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->far != far) {
            cmra->dirtyFlags |= cmra->P_DIRTY | cmra->VP_DIRTY;
            cmra->far = far;
           // mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setEyePosition(glm::vec3 eye, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        //mngr->
        if (cmra->eye != eye) {
            cmra->dirtyFlags |= cmra->V_DIRTY | cmra->VP_DIRTY;
            cmra->eye = eye;
        }
       // mngr->AddComponent(e, cmra);
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setDirection(glm::vec3 direction, Entity e) {
         auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->direction != direction) {
            cmra->dirtyFlags |= cmra->V_DIRTY | cmra->VP_DIRTY;
            cmra->direction = direction;
        }
       // mngr->AddComponent(e, cmra);
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setTarget(glm::vec3 target, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        glm::vec3 direction = target - cmra->eye;
        if (cmra->direction != direction) {
            cmra->dirtyFlags |= cmra->V_DIRTY | cmra->VP_DIRTY;
            cmra->direction = direction;
        }
       // mngr->AddComponent(e, cmra);
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    void setUp(glm::vec3 up, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->up != up) {
            cmra->dirtyFlags |= cmra->V_DIRTY | cmra->VP_DIRTY;
            cmra->up = up;
            mngr->AddComponent(e, cmra);//add
        }
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::mat4 getProjectionMatrix( Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->dirtyFlags & cmra->P_DIRTY) { // Only regenerate the projection matrix if its flag is dirty
            if (cmra->type == CameraType::Orthographic) {
                float half_height = cmra->orthographic_height * 0.5f;
                float half_width = cmra->aspect_ratio * half_height;
                cmra->P = glm::ortho(-half_width, half_width, -half_height, half_height, cmra->near, cmra->far);
              //  mngr->AddComponent(e, cmra);//add
            }
            else {
                cmra->P = glm::perspective(cmra->field_of_view_y, cmra->aspect_ratio, cmra->near, cmra->far);
               // mngr->AddComponent(e, cmra);//add
            }
            cmra->dirtyFlags &= ~cmra->P_DIRTY; // P is no longer dirty
        }
        return cmra->P;
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::mat4 getViewMatrix( Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->dirtyFlags & cmra->V_DIRTY) { // Only regenerate the view matrix if its flag is dirty
            cmra->V = glm::lookAt(cmra->eye, cmra->eye + cmra->direction, cmra->up);
          //  mngr->AddComponent(e, cmra);
            cmra->dirtyFlags &= ~cmra->V_DIRTY; // V is no longer dirty
        }
        return  cmra->V;
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::mat4 getVPMatrix(Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->dirtyFlags & cmra->VP_DIRTY) {
            cmra->VP = getProjectionMatrix(e) * getViewMatrix(e);
            //mngr->AddComponent(e, cmra);
            // Note that we called the functions getProjectionMatrix & getViewMatrix instead of directly using V & P
            // to make sure that they are not outdated
            cmra->dirtyFlags = 0; // Nothing is dirty anymore
            //mngr->AddComponent(e, cmra);//add
        }
        return cmra->VP;
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////

    CameraType getType( Entity e) { auto cmra = mngr->GetComponent<Camera>(e); return cmra->type; }
    [[nodiscard]] float getVerticalFieldOfView( Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->field_of_view_y; }
    [[nodiscard]] float getHorizontalFieldOfView(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->field_of_view_y * cmra->aspect_ratio; }
    [[nodiscard]] float getOrthographicHeight(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->orthographic_height; }
    [[nodiscard]] float getOrthographicWidth(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->orthographic_height * cmra->aspect_ratio; }
    [[nodiscard]] float getAspectRatio(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->aspect_ratio; }
    [[nodiscard]] float getNearPlane(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->near; }
    [[nodiscard]] float getFarPlane(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->far; }
    [[nodiscard]] glm::vec3 getEyePosition(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->eye; }
    [[nodiscard]] glm::vec3 getDirection(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->direction; }
    [[nodiscard]] glm::vec3 getOriginalUp(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->up; }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
    // Get the directions of the camera coordinates in the world space
    glm::vec3 Right(Entity e) {
       
        getViewMatrix(e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { cmra->V[0][0],cmra->V[1][0],cmra->V[2][0] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::vec3 Left(Entity e) {
        getViewMatrix(e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { -cmra->V[0][0],-cmra->V[1][0],-cmra->V[2][0] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::vec3 Up(Entity e) {
        getViewMatrix(e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { cmra->V[0][1],cmra->V[1][1],cmra->V[2][1] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::vec3 Down(Entity e) {
        getViewMatrix( e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { -cmra->V[0][1],-cmra->V[1][1],-cmra->V[2][1] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::vec3 Forward(Entity e) {
        getViewMatrix( e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { -cmra->V[0][2],-cmra->V[1][2],-cmra->V[2][2] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    glm::vec3 Backward(Entity e) {
        getViewMatrix( e);
        auto cmra = mngr->GetComponent<Camera>(e);
        return { cmra->V[0][2],cmra->V[1][2],cmra->V[2][2] };
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    // Transform point from world space to normalized device coordinates
    glm::vec3 fromWorldToDeviceSpace(glm::vec3 world, Entity e) {
        glm::vec4 clip = getVPMatrix(e) * glm::vec4(world, 1.0f);
        return glm::vec3(clip) / clip.w;
        // Note that we must divide by w. This is because of the projection matrix.
    }
    ////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
    // Transform point from normalized device coordinates to world space
    glm::vec3 fromDeviceToWorldSpace(glm::vec3 device, Entity e) {
        glm::vec4 clip = glm::inverse(getVPMatrix(e)) * glm::vec4(device, 1.0f);
        return glm::vec3(clip) / clip.w;
        // Note that we must divide by w even though we not going to the NDC space. This is because of the projection matrix.
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Controller System


    void initializeController(Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
       // this->app = application;
       // this->camera = camera;
        cmra->controller = new CameraController;
        cmra->controller->yaw_sensitivity = cmra->controller->pitch_sensitivity = 0.01f;
        cmra->controller->position_sensitivity = { 3.0f, 3.0f, 3.0f };
        cmra->controller->fov_sensitivity = glm::pi<float>() / 10;

        cmra->controller->position = cmra->eye;
        auto direction = cmra->direction;
        cmra->controller->yaw = glm::atan(-direction.z, direction.x);
        float base_length = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
        cmra->controller->pitch = glm::atan(direction.y, base_length);
      //  mngr->AddComponent(e, cmra);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void release(Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (cmra->controller->mouse_locked) {
            cmra->controller->mouse_locked = false;
            mouse->unlockMouse(win_ptr);
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void update(double delta_time,Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        if (mouse->isPressed(GLFW_MOUSE_BUTTON_1) && !cmra->controller->mouse_locked) {
            mouse->lockMouse(win_ptr);
            cmra->controller->mouse_locked = true;
        }
        else if (!mouse->isPressed(GLFW_MOUSE_BUTTON_1) && cmra->controller->mouse_locked) {
            mouse->unlockMouse(win_ptr);
            cmra->controller->mouse_locked = false;
        }

        if (mouse->isPressed(GLFW_MOUSE_BUTTON_1)) {
            glm::vec2 delta = mouse->getMouseDelta();
            cmra->controller->pitch -= delta.y * cmra->controller->pitch_sensitivity;
            cmra->controller->yaw -= delta.x * cmra->controller->yaw_sensitivity;
        }

        if (cmra->controller->pitch < -glm::half_pi<float>() * 0.99f) cmra->controller->pitch = -glm::half_pi<float>() * 0.99f;
        if (cmra->controller->pitch > glm::half_pi<float>() * 0.99f) cmra->controller->pitch = glm::half_pi<float>() * 0.99f;
        cmra->controller->yaw = glm::wrapAngle(cmra->controller->yaw);

        float fov = cmra->field_of_view_y + mouse->getScrollOffset().y * cmra->controller->fov_sensitivity;
        fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
        setVerticalFieldOfView(fov,e);

        glm::vec3 front = Forward(e), up = Up(e), right = Right(e);

        glm::vec3 current_sensitivity = cmra->controller->position_sensitivity;
        if (keyboard->isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= cmra->controller->speedup_factor;

        if (keyboard->isPressed(GLFW_KEY_W))
            cmra->controller->position += front * ((float)delta_time * current_sensitivity.z);
        if (keyboard->isPressed(GLFW_KEY_S)) cmra->controller->position -= front * ((float)delta_time * current_sensitivity.z);
        if (keyboard->isPressed(GLFW_KEY_Q)) cmra->controller->position += up * ((float)delta_time * current_sensitivity.y);
        if (keyboard->isPressed(GLFW_KEY_E)) cmra->controller->position -= up * ((float)delta_time * current_sensitivity.y);
        if (keyboard->isPressed(GLFW_KEY_D)) cmra->controller->position += right * ((float)delta_time * current_sensitivity.x);
        if (keyboard->isPressed(GLFW_KEY_A)) cmra->controller->position -= right * ((float)delta_time * current_sensitivity.x);

        setDirection(glm::vec3(glm::cos(cmra->controller->yaw), 0, -glm::sin(cmra->controller->yaw)) * glm::cos(cmra->controller->pitch) + glm::vec3(0, glm::sin(cmra->controller->pitch), 0),e);
        setEyePosition(cmra->controller->position,e);
      //  mngr->AddComponent(e, cmra);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    [[nodiscard]] float getYaw(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->yaw; }
    [[nodiscard]] float getPitch(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->pitch; }
    [[nodiscard]] glm::vec3 getPosition(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->position; }

    [[nodiscard]] float getYawSensitivity(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->yaw_sensitivity; }
    [[nodiscard]] float getPitchSensitivity(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->pitch_sensitivity; }
    [[nodiscard]] float getFieldOfViewSensitivity(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->fov_sensitivity; }
    [[nodiscard]] glm::vec3 getPositionSensitivity(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->position_sensitivity; }
    [[nodiscard]] float getSpeedUpFactor(Entity e) const { auto cmra = mngr->GetComponent<Camera>(e); return cmra->controller->speedup_factor; }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setYaw(float _yaw,Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        cmra->controller->yaw = glm::wrapAngle(_yaw);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setPitch(float _pitch, Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        const float v = 0.99f * glm::pi<float>() / 2;
        if (_pitch > v) _pitch = v;
        else if (_pitch < -v) _pitch = -v;
        cmra->controller->pitch = _pitch;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setPosition(glm::vec3 _pos,Entity e) {
        auto cmra = mngr->GetComponent<Camera>(e);
        cmra->controller->position = _pos;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setYawSensitivity(float sensitivity, Entity e) { auto cmra = mngr->GetComponent<Camera>(e); cmra->controller->yaw_sensitivity = sensitivity; }
    void setPitchSensitivity(float sensitivity, Entity e) { auto cmra = mngr->GetComponent<Camera>(e); cmra->controller->pitch_sensitivity = sensitivity; }
    void setFieldOfViewSensitivity(float sensitivity, Entity e) { auto cmra = mngr->GetComponent<Camera>(e); cmra->controller->fov_sensitivity = sensitivity; }
    void setPositionSensitivity(glm::vec3 sensitivity, Entity e) { auto cmra = mngr->GetComponent<Camera>(e); cmra->controller->position_sensitivity = sensitivity; }
};

