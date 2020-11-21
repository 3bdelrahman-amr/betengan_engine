#version 330 core

uniform vec3 color;
uniform vec2 translation;

in vec4 pixelPos;

// The output that goes to the frame buffer
out vec4 frag_color;

#define Reye 0.05
#define Rbody 0.4
#define Rsmile1 0.185
#define Rsmile2 0.215

void main() {

    vec2 center=vec2(0.0,0.0);
    vec2 centerEyeLeft=vec2(-0.5*Rbody,0.5*Rbody);
    vec2 centerEyeRight=vec2(0.5*Rbody,0.5*Rbody);
    center += translation;
    centerEyeLeft += translation;
    centerEyeRight += translation;
    vec2 pixelPosXY=pixelPos.xy;
    float dist=distance(center,pixelPosXY);
    float distEyeL=distance(centerEyeLeft,pixelPosXY);
    float distEyeR=distance(centerEyeRight,pixelPosXY);
    bool smile = pixelPosXY.y-translation.y<0 && dist>=Rsmile1 && dist <=Rsmile2;
    if (dist <= Rbody )
    //in the circle body
        if(distEyeL <= Reye || distEyeR<=Reye || smile)
            frag_color = vec4(color,0.0);
        else
            frag_color = vec4(color, 1.0);
    else{
        frag_color = vec4(0.0,0.0,0.0,0.0);//transperenet
    }



}
