#ifndef ENGINE
#define ENGINE

#include<vector>
#include"SomeDef.h"
#include"Application/Application.h"
#include"../Systems/MeshRendererSystem.h"
//#include"../Systems/CameraSystem.h"
//#include "shader.hpp"
#include <iostream>
//#include"../source/common/mesh/mesh.hpp"
//#include"../source/common/mesh/mesh-utils.hpp"
#include"../source/common/imgui-utils/utils.hpp"
//#include"../../source/common/camera/controllers/fly_camera_controller.hpp"
//#include"../../source/common/camera/camera.hpp"
//#include<glm/gtx/euler_angles.hpp>
//#include"../components/transform.h"
//#include"MeshRenderer.h"
//#include"Manager.h"
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class EngineApplication : public Betngan::Application {
//////////////////////
    Entity CameraEntity;
    vector<Entity> entities;
    Manager manager;
    //////////////////////////////////////
    CameraSystem* CSys;
    shared_ptr<MeshRendererSystem> MSys;
 
    ///////////////////////////////////////////
    glm::vec2 translation = glm::vec2(0, 0);
    glm::vec2 resoultion = glm::vec2(1280, 720);
    glm::vec3 color = glm::vec3(1, 0, 0);
    ////////////////////////////////////////////
   
    int state = 5;

    Betngan::WindowConfiguration getWindowConfiguration() override {
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
        ////////////////////////////////////////////////////////
        
        manager.Init();
        Entity e = manager.CreateEntity();
        entities.push_back(e);
         MSys= manager.RegisterSystem<MeshRendererSystem>();
         MSys->Set_Mngr_ptr(&manager);
         manager.RegisterComponent<MeshRendererr>();
         manager.AddComponent(e, MeshRendererr());
         //manager.RegisterComponent<ShaderProg>();
         manager.RegisterComponent<vector<Transform>>();
         manager.AddComponent(e, vector<Transform>());
         
         //MSys->Entities.insert(e);
         MSys->init(e);
         CSys = MSys->get_cam_ptr();
         CSys->SetEngineApp_ptr(&mouse,&keyboard,window);
        CameraEntity = manager.CreateEntity();
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //////////////////////
        manager.RegisterComponent<Camera>();
        manager.AddComponent(CameraEntity, Camera());
        ////////////////
        CSys->setEyePosition({ 10, 10, 10 },CameraEntity); //position vector which is x axis
        CSys->setTarget({ 0, 0, 0 },CameraEntity); // target vector
        CSys->setUp({ 0, 1, 0 }, CameraEntity); // up vector 
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //CameraSystem::se
        CSys->setupPerspective(glm::pi<float>() / 2, static_cast<float>(width) / height, 0.1f, 100.0f,CameraEntity); //set perspective mode for the camera

        CSys->initializeController(CameraEntity);
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
      MSys->Draw(deltaTime,CameraEntity);
}
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void onImmediateGui(ImGuiIO& io) override {
        //renderer.ImGui();
      
    }
   

};
#endif // !ENGINE
