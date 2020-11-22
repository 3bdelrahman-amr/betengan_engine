#pragma once
#include"application.hpp"
#include "shader.hpp"
#include"VertexBuffer.h"
#include <iostream>
#include"../source/common/mesh/mesh.hpp"
#include"../source/common/mesh/mesh-utils.hpp"
#include"../source/common/imgui-utils/utils.hpp"
#include"../../source/common/camera/controllers/fly_camera_controller.hpp"
#include"../../source/common/camera/camera.hpp"
#include<glm/gtx/euler_angles.hpp>
#include"transform.h"
#include"MeshRenderer.h"
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
class EngineApplication : public our::Application {
//////////////////////
  
    our::Camera camera;
    MeshRenderer renderer;
    our::FlyCameraController FlyCamera;
 
    ///////////////////////////////////////////
    glm::vec2 translation = glm::vec2(0, 0);
    glm::vec2 resoultion = glm::vec2(1280, 720);
    glm::vec3 color = glm::vec3(1, 0, 0);
    ////////////////////////////////////////////
    //int shape=2;
   // VertexBuffer va;
    int state = 5;

    our::WindowConfiguration getWindowConfiguration() override {
        return { "BETANGNAT ENGINE", {resoultion.x, resoultion.y }, false };
    }
    //getting the mouse position

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
public:

    void onCursorMoveEvent(double x, double y) override {
        Application::onCursorMoveEvent(x, y);
        double mouseX = ((x - resoultion.x / 2) / resoultion.x) * 2;
        double mouseY = (((y - resoultion.y / 2) / resoultion.y)) * -2;
        translation.x = mouseX;
        translation.y = mouseY;
    }

private:
    //////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    void onInitialize() override {
        
        renderer.init(&camera);
       
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //////// set up camera vectors (
        camera.setEyePosition({ 10, 10, 10 }); //position vector which is x axis
        camera.setTarget({ 0, 0, 0 }); // target vector
        camera.setUp({ 0, 1, 0 }); // up vector 
        /////////////////////////////////////////////////////////////////////////////////////////////////
        camera.setupPerspective(glm::pi<float>() / 2, static_cast<float>(width) / height, 0.1f, 100.0f); //set perspective mode for the camera

        FlyCamera.initialize(this, &camera);
        glClearColor(0, 0, 0, 0);
    }

   
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //mba2ash leeha lzma
    //get keyboard input to draw the corresponding shape
    void getShapeToDraw() override {

        for (int i = 49; i <= 48 + 4; i++) {
            keyboard.keyEvent(i, 0, i, 0);
            if (keyboard.justPressed(i)) {
                state = i - 48;
            }

        }
      
   }
    ///////////////////////////////////////////////////////////////////////////////////////////////////


    void onDraw(double deltaTime) override {
        FlyCamera.update(deltaTime);
        renderer.Draw();
      
    }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void onImmediateGui(ImGuiIO& io) override {
        renderer.ImGui();
      
    }
   

};