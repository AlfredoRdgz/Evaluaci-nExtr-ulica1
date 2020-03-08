#version 330

uniform vec2 windowSize;
out vec4 pixelColor; 

float magnitude(vec2 x) {
 	return sqrt((x.x * x.x) + (x.y * x.y));
}

vec2 squareVec(vec2 x) { 
	return vec2((x.x * x.x) - (x.y * x.y), 2 * x.x * x.y);
}

void main() {
	float delta = 2.4 / windowSize.x, i = gl_FragCoord.x, j = gl_FragCoord.y;
	vec3 color1 = vec3(0.04, 0.16, 0.08), color2 = vec3(0.90, 0.98, 0.67), color3 = vec3(0.67, 0.17, 0.17);
	vec2 x = vec2(-1.2 + (i * delta),-1.2 + (j * delta));
	vec2 z = vec2(-0.74543, 0.11301);
	int count = 0;
	float magnitude = magnitude(x);
	while(magnitude <= 2.0 && count < 128) {
		x =  squareVec(x) + z;
		magnitude = magnitude(x);
		count++;
	}
	float gray = 0.0;
	magnitude = magnitude(x);
	if(magnitude <= 2.0){
		pixelColor = vec4(color1, 1.0);
	} else {
		if(count == 128) {
			pixelColor = vec4(color2, 1.0);
		} 
		else if (count == 0) {
			pixelColor = vec4(color3, 1.0);
		}
		else {
			vec3 mix = (1/2 * (color2 + color3)) / count;
			pixelColor = vec4(mix,1.0);
		}
	}
}

