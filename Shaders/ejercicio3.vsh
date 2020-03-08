#version 330

in vec2 vertexPosition;
in vec3 vertexColor;
in float vertexType;

out vec3 vertexColorToFS;

uniform float outRadius;
uniform float inRadius;

void main(){
    if(vertexType == 1.0){
        gl_Position=vec4(vertexPosition * outRadius, 0.0, 1.0);
    }
    else{
        gl_Position=vec4(vertexPosition * inRadius, 0.0, 1.0);
    }
    vertexColorToFS=vertexColor;
}