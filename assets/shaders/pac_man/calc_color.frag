#version 330 core

uniform vec3 color;
uniform vec2 translation;

in vec4 pixelPos;

// The output that goes to the frame buffer
out vec4 frag_color;

#define Reye 0.05
#define Rbody 0.4

void main() {

    vec2 center=vec2(0.0,0.0);
    center += translation;
    
                        vec2 centerEye=vec2(0.0,Rbody-Reye-0.1);
                        centerEye += translation;
                        vec2 pixelPosXY=pixelPos.xy;
                        float dist=distance(center,pixelPosXY);
                        float distEye=distance(centerEye,pixelPosXY);
                        if (dist <= Rbody )
                                if(distEye <= Reye)
                                frag_color = vec4(0.0,0.0,0.0,0.0);
                                else if (pixelPosXY.x-translation.x >= abs(pixelPosXY.y-translation.y))
                                frag_color = vec4(0.0,0.0,0.0,0.0);
                                else frag_color = vec4(color, 1.0);
                        else{
                                frag_color = vec4(0.0,0.0,0.0,0.0);//transperenet
                        }
}
