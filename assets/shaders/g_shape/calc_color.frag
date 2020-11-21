#version 330 core

uniform vec3 color;
uniform vec2 translation;

in vec4 pixelPos;

// The output that goes to the frame buffer
out vec4 frag_color;

#define R1 0.2357022604 // root(2)/6
#define R2 0.3535533906 // root(2)/4

void main() {
    /* dist = center -> pixel to be drawn
        if (dist >= R1 && dist <= R2)     //R2>R1
            frag_color = vec4(color, 1.0);
        else
            frag_color = vec4(0.0,0.0,0.0,1.0);
    */
    vec2 center=vec2(0.0,0.0);
    center += translation;
     vec2 pixelPosXY=pixelPos.xy;
                        float dist=distance(center,pixelPosXY);
                        if(pixelPosXY.x >= 0.1666666667+translation.x && pixelPosXY.x <= 0.28+translation.x &&
                        pixelPosXY.y-translation.y <0 && pixelPosXY.y-translation.y >-0.1666666667)
                        frag_color = vec4(color, 1.0);
                        else if (dist >= R1 && dist <= R2 )     //R2>R1
                                if (pixelPosXY.x-translation.x >= abs(pixelPosXY.y-translation.y))
                                {
                                        if(pixelPosXY.x >= 0.1666666667+translation.x && pixelPosXY.x <= 0.28+translation.x &&pixelPosXY.y-translation.y <0 )
                                        frag_color = vec4(color, 1.0);
                                        else frag_color = vec4(0.0,0.0,0.0,0.0);
                                }
                                else
                                frag_color = vec4(color, 1.0);
                        else{
                                frag_color = vec4(0.0,0.0,0.0,0.0);//transperenet
                        }



}
