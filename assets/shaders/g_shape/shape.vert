#version 330 core

// Here we will define Uniform Variable
// they are called uniform because every run of the shader (under the same draw call) will see the same value
// so it is uniform across all executions of the shader
uniform vec2 translation;

// The output that goes to the frag shader
out vec4 pixelPos;

void main() {
    // This time we have 6 points since we are drawing a Quad (in NDC, it is a square).
    const vec3 positions[] = vec3[](
        //right angled rect
        vec3(-0.5, -0.5, 0.0),
        vec3( 0.5, -0.5, 0.0),
        vec3(-0.5,  0.5, 0.0),

        //equ triangle
        vec3(0.0, 0.0, 0.0),
        vec3(-0.5,  0.5, 0.0),
        vec3( 0.5, 0.5, 0.0),

        //small comp triangle
        vec3(0.125, -0.125, 0.0),
        vec3(0.25, -0.25, 0.0),
        vec3(0.25, -0.125, 0.0),

        //2 R.A.triangle of compliting G
        vec3(0.125, -0.125, 0.0),
        vec3(0.25, -0.125, 0.0),
        vec3(0.25, 0.0, 0.0),
        vec3(0.125, -0.125, 0.0),
        vec3(0.125,0.0, 0.0),
        vec3(0.25, 0.0, 0.0)
    );

    // get the position based on the vertex id
    vec3 position = positions[gl_VertexID];
    // Translate it
    position.xy += translation;

    // Finally send the value to "gl_Position".
    gl_Position = vec4(position, 1.0);
    pixelPos=gl_Position;
}