#pragma once
#include"../src/Manager.h"
#include"../src/System.h"
#include"ComponentsDef.h"
#include <functional>
class MeshSystem {

    Manager* mngr = nullptr;
public:

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    void SetManger(Manager* m) {
        mngr = m;
    }
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    // The underlying OpenGL objects creator
        // This receives a list of functions with the signature void(void).
        // Each function setups up how to access each buffer to send data to the attributes
        // So the number of allocated vertex buffer will be equal the number of passed accessor functions
    void create(Entity e,const std::vector<std::function<void()>>& accessors, bool has_elements = true) {
        
        auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        MeshRend->mesh.vertex_buffers.resize(accessors.size()); // reserve space for the vertex buffers

        // Generate & bind the vertex array to store the buffer access details
        glGenVertexArrays(1, &MeshRend->mesh.vertex_array);
        glBindVertexArray(MeshRend->mesh.vertex_array);

        if (has_elements) {
            // If this mesh will have elements, generate a buffer for it and
            // bind it such that the vertex array can take it into account while drawing
            glGenBuffers(1, &MeshRend->mesh.element_buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshRend->mesh.element_buffer);
            MeshRend->mesh.use_elements = true;
        }

        // Generate the needed vertex buffers
        size_t buffer_count = accessors.size();
        glGenBuffers(buffer_count, MeshRend->mesh.vertex_buffers.data());

        // bind each buffer and call its corresponding accessor-setup function such that the vertex array stores these configuration details
        for (size_t buffer_index = 0; buffer_index < buffer_count; ++buffer_index) {
            glBindBuffer(GL_ARRAY_BUFFER, MeshRend->mesh.vertex_buffers[buffer_index]);
            accessors[buffer_index]();
        }
        //mngr->AddComponent(e, MeshRend);
        glBindVertexArray(0); // Remember to unbind the vertex array such that it stops storing any more configuration
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Was create called (vertex array is allocated)
    [[nodiscard]] bool isCreated(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.vertex_array != 0; }
    [[nodiscard]] bool hasElements(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.element_buffer != 0; }
    [[nodiscard]] bool isUsingElements(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.use_elements; }
    [[nodiscard]] GLenum getPrimitiveMode(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.primitive_mode; }
    [[nodiscard]] GLsizei getElementCount(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.element_count; }
    [[nodiscard]] GLsizei getVertexCount(Entity e) const { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); return  MeshRend->mesh.vertex_count; }

    void setUseElements(bool value,Entity e) { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); MeshRend->mesh.use_elements = value && (MeshRend->mesh.element_buffer != 0); }
    void setElementCount(GLsizei value, Entity e) { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); MeshRend->mesh.element_count = value; }
    void setVertexCount(GLsizei value, Entity e) { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); MeshRend->mesh.vertex_count = value; }
    void setPrimitiveMode(GLenum mode, Entity e) { auto MeshRend = mngr->GetComponent<MeshRendererr>(e); MeshRend->mesh.primitive_mode = mode; }

    // Destroy the OpenGL objects if they were allocated
    void destroy( Entity e) {
        auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        if (MeshRend->mesh.vertex_array != 0) glDeleteVertexArrays(1, &MeshRend->mesh.vertex_array);
        MeshRend->mesh.vertex_array = 0;
        if (MeshRend->mesh.element_buffer != 0) glDeleteBuffers(1, &MeshRend->mesh.element_buffer);
        MeshRend->mesh.element_buffer = 0;
        glDeleteBuffers(MeshRend->mesh.vertex_buffers.size(), MeshRend->mesh.vertex_buffers.data());
        MeshRend->mesh.vertex_buffers.resize(0);
    }

    MeshSystem() = default;
    // Destroy the OpenGL objects since we are using the RAII pattern for handling GPU resources
    ~MeshSystem() {  }

   
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Send the mesh data down the pipeline
    // Start and count can be used to only send a contiguous subset of the data
    // if count is 0, it will send all the vertices from start till the end of the vertices
    void draw(Entity e,GLsizei start = 0, GLsizei count = 0) const {
        auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        if (MeshRend->mesh.use_elements) {
            const void* pointer = (void*)(MeshRend->mesh.element_size * start);
            if (count == 0) count = MeshRend->mesh.element_count - start;
            glBindVertexArray(MeshRend->mesh.vertex_array); // First we bind the vertex array since it know how to send the data from the buffers to shader attributes
            glDrawElements(MeshRend->mesh.primitive_mode, count, MeshRend->mesh.element_type, pointer); // Then we draw
            glBindVertexArray(0); // Then unbind the vertex array
        }
        else {
            if (count == 0) count = MeshRend->mesh.vertex_count - start;
            glBindVertexArray(MeshRend->mesh.vertex_array); // First we bind the vertex array since it know how to send the data from the buffers to shader attributes
            glDrawArrays(MeshRend->mesh.primitive_mode, start, count); // Then we draw
            glBindVertexArray(0); // Then unbind the vertex array
        }
    }

    //Delete copy constructor and assignment operation
    //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
    //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
    MeshSystem(MeshSystem const&) = delete;
    MeshSystem& operator=(MeshSystem const&) = delete;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Set the element data from a vector of elements
    template<typename T>
    void setElementData(Entity e,const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        //auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        //MeshRend
        setElementData(e,data.data(), data.size(), usage);
    }

    // Set the element data from a raw pointer
    template<typename T>
    void setElementData(Entity e,T const* data, size_t count, GLenum usage = GL_STATIC_DRAW) {
         auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        if (MeshRend->mesh.element_buffer == 0) {
            std::cerr << "MESH ERROR: Setting element data before creating element buffer\n";
            return;
        }

        MeshRend->mesh.element_size = sizeof(T);
        // Note: elements types are always unsigned
        if constexpr (sizeof(T) == 4) MeshRend->mesh.element_type = GL_UNSIGNED_INT;
        else if constexpr (sizeof(T) == 2) MeshRend->mesh.element_type = GL_UNSIGNED_SHORT;
        else if constexpr (sizeof(T) == 2) MeshRend->mesh.element_type = GL_UNSIGNED_BYTE;
        else static_assert(sizeof(T) != sizeof(T), "Unsupported Element type size");

        MeshRend->mesh.element_count = count;
        // Bind the elements buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshRend->mesh.element_buffer);
        // Send data to the buffer
        // The 2nd parameter is the data size in bytes, the 3rd parameter is a pointer to the data
        // The last parameter is how we plan to use the buffer later, we usually follow the following rules:
        // Use GL_STATIC_DRAW for buffers where we don't plan to modify the data again.
        // Use GL_DYNAMIC_DRAW for buffers where we plan to modify the data but not frequently.
        // Use GL_STREAM_DRAW for buffers where we plan to frequently modify the data (once or even more per frame)
        // This helps the driver optimize where to store the buffer.
        // For example, data with GL_STATIC_DRAW are usually stored on the VIDEO memory which is fast for reading in the GPU but slow for writing from the CPU.
        // while data with GL_STREAM_DRAW are usually stored on a part of the RAM that is accessible by the GPU which is slow for reading in the GPU but fast for writing from the CPU.
        // Note that "usage" is just a hint and you can break these rules but you'll most probably suffer from bad performance.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MeshRend->mesh.element_count * MeshRend->mesh.element_size, data, usage);
        //mngr->AddComponent(e, MeshRend);
    }

    // read the element data from the GPU. Don't use frequently (for the sake of performance)
    template<typename T>
    void getElementData(std::vector<T>& elements) {
        assert(sizeof(T) == element_size);
        GLint size;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        assert((size % sizeof(T)) == 0);
        elements.resize(size / sizeof(T));
        glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, elements.data());
    }

    // read the element data from the GPU. Don't use frequently (for the sake of performance)
    template<typename T>
    std::vector<T>&& getElementData() {
        std::vector<T> elements;
        getElementData(elements);
        return elements;
    }

    // Set the vertex data to one of the VBOs from a vector
    template<typename T>
    void setVertexData(Entity e,size_t buffer_index, const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        setVertexData(e,buffer_index, data.data(), data.size(), usage);
    }

    // Set the vertex data to one of the VBOs from a raw pointer
    template<typename T>
    void setVertexData(Entity e,size_t buffer_index, T const* data, size_t count, GLenum usage = GL_STATIC_DRAW) {
        auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
        if (buffer_index >= MeshRend->mesh.vertex_buffers.size()) {
            std::cerr << "MESH ERROR: Setting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << MeshRend->mesh.vertex_buffers.size() << ")\n";
            return;
        }
        // Bind the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, MeshRend->mesh.vertex_buffers[buffer_index]);
        // Send data to the buffer
        // The 2nd parameter is the data size in bytes, the 3rd parameter is a pointer to the data
        // The last parameter is how we plan to use the buffer later, we usually follow the following rules:
        // Use GL_STATIC_DRAW for buffers where we don't plan to modify the data again.
        // Use GL_DYNAMIC_DRAW for buffers where we plan to modify the data but not frequently.
        // Use GL_STREAM_DRAW for buffers where we plan to frequently modify the data (once or even more per frame)
        // This helps the driver optimize where to store the buffer.
        // For example, data with GL_STATIC_DRAW are usually stored on the VIDEO memory which is fast for reading in the GPU but slow for writing from the CPU.
        // while data with GL_STREAM_DRAW are usually stored on a part of the RAM that is accessible by the GPU which is slow for reading in the GPU but fast for writing from the CPU.
        // Note that "usage" is just a hint and you can break these rules but you'll most probably suffer from bad performance.
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, usage);
    }


    // Set vertex data to a part of the buffer from a vector
    template<typename T>
    void setVertexSubData(size_t buffer_index, const std::vector<T>& data, GLintptr offset, GLenum usage = GL_STATIC_DRAW) {
        setVertexSubData(buffer_index, data.data(), offset, data.size(), usage);
    }

    // Set vertex data to a part of the buffer from a raw pointer
    template<typename T>
    void setVertexSubData(size_t buffer_index, T const* data, GLintptr offset, size_t count, GLenum usage = GL_STATIC_DRAW) {
        if (buffer_index >= vertex_buffers.size()) {
            std::cerr << "MESH ERROR: Setting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << vertex_buffers.size() << ")\n";
            return;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(T), data, usage);
    }

    // read the vertex data from the GPU. Don't use frequently (for the sake of performance)
    template<typename T>
    void getVertexData(size_t buffer_index, std::vector<T>& vertices, GLintptr offset = 0, size_t count = 0) {
        if (buffer_index >= vertex_buffers.size()) {
            std::cerr << "MESH ERROR: Requesting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << vertex_buffers.size() << ")\n";
            return;
        }
        GLint size;
        if (count == 0) {
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
            glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            size -= offset;
            assert((size % sizeof(T)) == 0);
            vertices.resize(size / sizeof(T));
        }
        else {
            size = count * sizeof(T);
            vertices.resize(count);
        }
        glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices.data());
    }

    // read the vertex data from the GPU. Don't use frequently (for the sake of performance)
    template<typename T>
    std::vector<T>&& getVertexData(size_t buffer_index, GLintptr offset = 0, size_t count = 0) {
        std::vector<T> vertices;
        getVertexData<>(buffer_index, vertices, offset, count);
        return vertices;
    }


};





/*

 


*/