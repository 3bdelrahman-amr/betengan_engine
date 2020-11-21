#include <application.hpp>
#include <shader.hpp>
#include <iostream>

class EngineApplication : public our::Application {

    our::ShaderProgram program;
    GLuint vertex_array = 0;

    glm::vec2 translation = glm::vec2(0,0);
    glm::vec2 resoultion = glm::vec2(720,720);
    glm::vec3 color = glm::vec3(0, 0, 0);
    int shape=1;

    our::WindowConfiguration getWindowConfiguration() override {
        return { "LAMA Engine", {resoultion.x, resoultion.y }, false };
    }
//getting the mouse position
public:
    /*int runE(int shape) {
        this->shape=shape;
        return EngineApplication().run();
    }*/

    void onCursorMoveEvent(double x, double y) override {
        Application::onCursorMoveEvent(x, y);
        double mouseX=((x-resoultion.x/2)/resoultion.x)*2;
        double mouseY=(((y-resoultion.y/2)/resoultion.y))*-2;
        translation.x=mouseX;
        translation.y=mouseY;
    }

private:

    void onInitialize() override {
        program.create();
        program.attach("../assets/shaders/shape.vert", GL_VERTEX_SHADER);
        switch (shape) {
            case 4:{
                //program.attach("../assets/shaders/g_shape/shape.vert", GL_VERTEX_SHADER);
                program.attach("../assets/shaders/g_shape/calc_color.frag", GL_FRAGMENT_SHADER);
            }
                break;
            case 3:{
                //program.attach("../assets/shaders/pac_man/shape.vert", GL_VERTEX_SHADER);
                program.attach("../assets/shaders/pac_man/calc_color.frag", GL_FRAGMENT_SHADER);
            }
                break;
            case 2:{
                //program.attach("../assets/shaders/pac_man/shape.vert", GL_VERTEX_SHADER);
                program.attach("../assets/shaders/heart/calc_color.frag", GL_FRAGMENT_SHADER);
            }
                break;
            case 1:{
                 //program.attach("../assets/shaders/smile_face/shape.vert", GL_VERTEX_SHADER);
                 program.attach("../assets/shaders/smile_face/calc_color.frag", GL_FRAGMENT_SHADER);
            }
                break;
            default:{
                //program.attach("../assets/shaders/smile_face/shape.vert", GL_VERTEX_SHADER);
                program.attach("../assets/shaders/smile_face/calc_color.frag", GL_FRAGMENT_SHADER);
            }
        }
        program.link();

        //blend config for using the alpha channel for transperency:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glGenVertexArrays(1, &vertex_array);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        GLuint translation_uniform_location = glGetUniformLocation(program, "translation");
        glUniform2f(translation_uniform_location, translation.x, translation.y);
        GLuint color_uniform_location = glGetUniformLocation(program, "color");
        glUniform3f(color_uniform_location, color.r, color.g, color.b);



        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 15);
        glBindVertexArray(0);
    }

    void onDestroy() override {
        program.destroy();
        glDeleteVertexArrays(1, &vertex_array);
    }




    void onImmediateGui(ImGuiIO &io) override {
        ImGui::Begin("Controls");
        ImGui::ColorEdit3("Color", glm::value_ptr(color));
        ImGui::End();
    }

};
int main(int argc, char** argv) {
    return EngineApplication().run();
}
/*int run(int shape) {
    EngineApplication engineApplication;
    engineApplication.setShape(shape);
    return engineApplication.run();
}*/
