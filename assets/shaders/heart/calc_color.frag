#version 330 core

uniform vec3 color;
uniform vec2 translation;

in vec4 pixelPos,colorr;

// The output that goes to the frame buffer
out vec4 frag_color;

#define R1 0.2357022604 // root(2)/6
#define R2 0.3535533906 // root(2)/4

void main() {
    vec2 center=vec2(0.0,0.0);
    center += translation;
    float x =pixelPos.x-center.x;
    float y =pixelPos.y-center.y;
    float inHeart=(x*x+(1.2*y-1*(abs(x)))*(1.2*y-1*(abs(x))))*20;

    if(inHeart<=3)
        frag_color = colorr+0.001;//vec4(color, 1.0);
    else{
        frag_color = vec4(0.0,0.0,0.0,0.0);//transperenet
    }



}
