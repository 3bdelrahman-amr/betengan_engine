#pragma once
#include"../src/SomeDef.h"
class ShaderProg
{
 public:
    //Shader Program Handle
    GLuint program;
    map<std::string, GLuint> uniform_location_cache;
};

