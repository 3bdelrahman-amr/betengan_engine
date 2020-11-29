#include "ShaderSystem.h"
//#include <glad/gl.h>
void ShaderSystem:: create(Entity e, Manager* mangr) {
   // assert(Entities.find(e) != Entities.end());
    //auto shader = mangr->GetComponent<ShaderProg>(e);
   // mangr->AddComponent(e, ShaderProg());
    auto MeshRend = mangr->GetComponent<MeshRendererr>(e);
    MeshRend->shader.program = glCreateProgram();
    mng = mangr;
    //mangr->AddComponent(e, MeshRend);

}
//void ShaderSystem::destroy() {
//    for (auto entt : Entities) {
//        mng
//    }
//
//}
//GLuint getProgramId() { return program; }
//ShaderSystem(Manager*m): System(m) { //program = 0;
//}
//ShaderSystem::~ShaderSystem() { destroy(); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Cast Class to an OpenGL Object name
// operator GLuint() const { return program; } // NOLINT: Allow implicit casting for convenience

 //Read shader from file, send it to GPU, compile it then attach it to shader
bool ShaderSystem:: attach(const std::string& filename, GLenum type, Entity e) const // NOLINT: attach does alter the object state so [[nodiscard]] is unneeded
{ // first, we use C++17 filesystem library to get the directory (parent) path of the file.
// the parent path will be sent to stb_include to search for files referenced by any "#include" preprocessor command.
    auto file_path = std::filesystem::path(filename);
    auto file_path_string = file_path.string();
    auto parent_path_string = file_path.parent_path().string();
    auto path_to_includes = &(parent_path_string[0]);
    char error[256];

    // Read the file as a string and resolve any "#include"s recursively
    auto source = stb_include_file(&(file_path_string[0]), nullptr, path_to_includes, error);

    // Check if any loading errors happened
    if (source == nullptr) {
        std::cerr << "ERROR: " << error << std::endl;
        return false;
    }

    GLuint shaderID = glCreateShader(type); //Create shader of the given type

    // Function parameter:
    // shader (GLuint): shader object name.
    // count (GLsizei): number of strings passed in the third parameter. We only have one string here.
    // string (const GLchar**): an array of source code strings.
    // lengths (const GLint*): an array of string lengths for each string in the third parameter. if null is passed,
    //           then the function will deduce the lengths automatically by searching for '\0'.
    glShaderSource(shaderID, 1, &source, nullptr); //Send shader source code
    glCompileShader(shaderID); //Compile the shader code
    free(source);

    //Check and log for any error in the compilation process
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char* logStr = new char[length];
        glGetShaderInfoLog(shaderID, length, nullptr, logStr);
        std::cerr << "ERROR IN" << filename << std::endl;
        std::cerr << logStr << std::endl;
        delete[] logStr;
        glDeleteShader(shaderID);
        return false;
    }
    auto MeshRend = mng->GetComponent<MeshRendererr>(e);


    
    glAttachShader(MeshRend->shader.program, shaderID); //Attach shader to program
    glDeleteShader(shaderID); //Delete shader (the shader is already attached to the program so its object is no longer needed)
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//Link Program (Do this after all shaders are attached)
bool ShaderSystem::link(Entity e) const // NOLINT: link does alter the object state so [[nodiscard]] is unneeded
{
    //Link
    auto MeshRend = mng->GetComponent<MeshRendererr>(e);

    glLinkProgram(MeshRend->shader.program);

    //Check and log for any error in the linking process
    GLint status;
    glGetProgramiv(MeshRend->shader.program, GL_LINK_STATUS, &status);
    if (!status) {
        GLint length;
        glGetProgramiv(MeshRend->shader.program, GL_INFO_LOG_LENGTH, &length);
        char* logStr = new char[length];
        glGetProgramInfoLog(MeshRend->shader.program, length, nullptr, logStr);
        std::cerr << "LINKING ERROR" << std::endl;
        std::cerr << logStr << std::endl;
        delete[] logStr;
        return false;
    }
    return true;


}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//Get the location of a uniform variable in the shader
GLuint ShaderSystem::getUniformLocation(const string& name, Entity e) {


    //assert(Entities.find(e) != Entities.end());

    auto MeshRend = mng->GetComponent<MeshRendererr>(e);
    auto it = MeshRend->shader.uniform_location_cache.find(name);

    if (it != MeshRend->shader.uniform_location_cache.end()) {
        return it->second; // We found the uniform in our cache, so no need to call OpenGL.
    }
    GLuint location = glGetUniformLocation(MeshRend->shader.program, name.c_str()); // The uniform was not found, so we retrieve its location
    MeshRend->shader.uniform_location_cache[name] = location; // and cache the location for later queries
    return location;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//A group of setter for uniform variables
//NOTE: It is inefficient to call glGetUniformLocation every frame
//So it is usually a better option to either cache the location
//or explicitly define the uniform location in the shader
void ShaderSystem::set(const std::string& uniform, GLfloat value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform1f(getUniformLocation(uniform, e), value);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


void ShaderSystem::set(const std::string& uniform, GLint value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform1i(getUniformLocation(uniform, e), value);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderSystem:: set(const std::string& uniform, GLboolean value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform1i(getUniformLocation(uniform, e), value);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderSystem:: set(const std::string& uniform, glm::vec2 value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform2f(getUniformLocation(uniform, e), value.x, value.y);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderSystem:: set(const std::string& uniform, glm::vec3 value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform3f(getUniformLocation(uniform, e), value.x, value.y, value.z);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderSystem:: set(const std::string& uniform, glm::vec4 value, Entity e) {
    //assert(Entities.find(e) != Entities.end());
    glUniform4f(getUniformLocation(uniform, e), value.x, value.y, value.z, value.w);
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void ShaderSystem:: set(const std::string& uniform, glm::mat4 value, Entity e, GLboolean transpose ) {
    //assert(Entities.find(e) != Entities.end());
    glUniformMatrix4fv(getUniformLocation(uniform, e), 1, transpose, glm::value_ptr(value));
}



//ShaderSystem::ShaderSystem(ShaderSystem const&) = delete;
//ShaderSystem::ShaderSystem& operator=(ShaderSystem const&) = delete;
