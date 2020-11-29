#pragma once


#include"../src/SomeDef.h"
class Mesh
{
public:
    GLuint vertex_array = 0;
    GLuint element_buffer = 0;
    std::vector<GLuint> vertex_buffers; // We allow the mesh to contain multiple buffers

    bool use_elements = false; // Whether the mesh should be drawn using glDrawElements or just glDrawArrays
    size_t element_size = 1; // The size of the element data type
    // The element data type, The mode of the primitive assembly step
    GLenum element_type = GL_UNSIGNED_SHORT, primitive_mode = GL_TRIANGLES;
    GLsizei element_count = 0, vertex_count = 0; // How meany elements/vertices are there. Needed by draw()
};

