#version 330

uniform vec2 windowSize;
out vec4 pixelColor; 

void main() {
	float delta = 2.4 / windowSize.x;
	vec2 x = vec2(-1.2 + (gl_FragCoord.x * delta),-1.2 + (gl_FragCoord.y * delta));
	vec2 z = vec2(-0.74543, 0.11301);
	int count = 0;
	while(length(x) <= 2.0 && count < 128){
		x =  x * x + z;
		count++;
	}
	if(length(x) <= 2.0){
		pixelColor = vec4(0.5,0.5,0.5, 1);
	} else {
		pixelColor = vec4(count / 128, count / 128, count / 128, 1);
	}
}
