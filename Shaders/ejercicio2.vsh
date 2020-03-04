#version 330

in vec2 vertexPosition;
in vec3 color;
uniform vec2 windowSize;
out vec3 vertexColorToFS;

void main(){
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	vertexColorToFS = color;
} 