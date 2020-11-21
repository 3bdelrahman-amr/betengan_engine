#version 330 core
// Here we will define Uniform Variable
// they are called uniform because every run of the shader (under the same draw call) will see the same value
// so it is uniform across all executions of the shader
uniform vec2 translation;

// The output that goes to the frag shader
out vec4 pixelPos,colorr;

void clamp(){
if(colorr.x<0)
colorr.x=-1*colorr.x;
if(colorr.y<0)
colorr.y=-1*colorr.y;



}
void main() {
    const vec3 positions[6] = vec3[6](
	vec3(-0.5,-0.5,0.0),
	vec3(0.5,-0.5,0.0),
	vec3(0.5,0.5,0.0),
	vec3(0.5,0.5,0.0),
	vec3(-0.5,0.5,0.0),
	vec3(-0.5,-0.5,0.0)
    );

    vec3 position = positions[gl_VertexID];
     
    // Translate it
    position.xy += translation;
  /////////////////////////////////////////////  trying to  intarpolate 
    colorr=vec4((position),1.0);
     clamp();
   ////////////////////////////////////////////
    // Finally send the value to "gl_Position".
    gl_Position = vec4(position, 1.0);
    //and to the shader fragment as well
    pixelPos=gl_Position;
}