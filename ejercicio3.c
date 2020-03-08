/*
 * 	Ejercicio 3
 *
 *  Created on: 17/02/2020
 *  Authors: Alfredo Rodriguez & Gustavo Rueda
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "Utils.h"

#define PEAKS 24

static float INNER_RADIUS = 0.25, OUTER_RADIUS = 0.5;

// Necessary ID's
GLuint programId, winSizeLoc, vertexArrayId, bufferId[3], vertexPosLoc, vertexColorLoc, vertexTypeLoc;
GLuint outRadiusLoc;
GLuint inRadiusLoc;

// Array declarations
static float *positionArray, *colorArray;
static float vertexType[PEAKS * 2 + 2] = {};

float factor_out = 1.0;
float factor_in  = 1.0;

// Absolute value function for float elements
float absolute_ej3(float value) {
	if(value < 0.0) {
		return value * -1;
	}
	return value;
}

// Array calculation function
void fillArrays_ej3(int peaks, float innerRadius, float outerRadius) {
	positionArray = (float*) malloc((PEAKS * 2 * 2 + 4) * sizeof(float)); // PEAKS * 2 for internal & external points * 2 for dimensions + 4 due to triangle fan elements needed
	colorArray = (float*) malloc((PEAKS * 2 * 3 + 6) * sizeof(float)); // PEAKS * 2 for internal & external points * 3 for dimensions + 6 due to extra 2 elements with rgb each
	float angle=0.0;
	float incremento=2*M_PI/(peaks*2);
	int index=0;
	int index_color=0;
	positionArray[index++]=0.0;
	positionArray[index++]=0.0;
	colorArray[index_color++]=1.0;
	colorArray[index_color++]=1.0;
	colorArray[index_color++]=1.0;
	vertexType[0]=0.0;
	for(int i=0;i<peaks;i++){
		positionArray[index++]=outerRadius*cos(angle);
		positionArray[index++]=outerRadius*sin(angle);
		colorArray[index_color++]=fabs(sin(angle));
		colorArray[index_color++]=fabs(cos(angle));
		colorArray[index_color++]=angle<M_PI?0.0:0.5;

		angle+=incremento;

		vertexType[(index-1)/2]=1.0;

		//X
		positionArray[index++]=innerRadius*cos(angle);
		//Y
		positionArray[index++]=innerRadius*sin(angle);
		//COLOR
		colorArray[index_color++]=fabs(sin(angle));
		colorArray[index_color++]=fabs(cos(angle));
		colorArray[index_color++]=angle<M_PI?0.0:0.5;
		angle+=incremento;
		vertexType[(index-1)/2]=0.0;
	}
	angle=0.0;
	positionArray[index++]=outerRadius*cos(angle);
	positionArray[index++]=outerRadius*sin(angle);
	colorArray[index_color++]=fabs(sin(angle));
	colorArray[index_color++]=fabs(cos(angle));
	colorArray[index_color++]=0.5;
	vertexType[(index-1)/2]=1.0;
}

// Shaders initialization function
static void initShaders(){
	GLuint vShaderId = compileShader("Shaders/ejercicio3.vsh",GL_VERTEX_SHADER);
	if(!shaderCompiled(vShaderId)) return;
	GLuint fShaderId = compileShader("Shaders/ejercicio3.fsh",GL_FRAGMENT_SHADER);
	if(!shaderCompiled(fShaderId)) return;
	programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);
	vertexPosLoc = glGetAttribLocation(programId, "vertexPosition");
	vertexColorLoc = glGetAttribLocation(programId, "vertexColor");
	vertexTypeLoc = glGetAttribLocation(programId, "vertexType");
	winSizeLoc = glGetUniformLocation(programId, "windowSize");
}

// Program init function
static void init() {
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	glGenBuffers(3, bufferId);
	// Vertex array
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, (PEAKS * 2 * 2 + 4) * sizeof(float), positionArray, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(vertexPosLoc);
	// Color array
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
	glBufferData(GL_ARRAY_BUFFER,(PEAKS * 2 * 3 + 6) * sizeof(float), colorArray, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(vertexColorLoc);
	//Vertex Type array
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexType), vertexType, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexTypeLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexTypeLoc);

	outRadiusLoc = glGetUniformLocation(programId, "outRadius");
	inRadiusLoc = glGetUniformLocation(programId, "inRadius");

}

// Display function
static void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programId);
	glBindVertexArray(vertexArrayId);
	glUniform1f(outRadiusLoc,factor_out);
	glUniform1f(inRadiusLoc,factor_in);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (PEAKS * 2 * 2 + 4));
	glutSwapBuffers();
}

static void keyboardFunc(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == 97||key == 65) {
		factor_out -= 0.005;
	}
	if (key == 98||key == 66) {
		factor_in -= 0.005;
	}
	if (key == 99||key == 67) {
		factor_out += 0.005;
	}
	if (key == 100||key == 68) {
		factor_in += 0.005;
	}
	glutPostRedisplay();
}

// Main function
int main3(int argc, char** argv) {
	glutInit(&argc, argv);
	int w = 600, h = 600;
	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;
	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Ejercicio 3");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glewInit();
	glClearColor(0.5, 0.5, 0.5, 1.0);

	// Arrays calculation function:
	fillArrays_ej3(PEAKS, INNER_RADIUS, OUTER_RADIUS);
	initShaders();
	init();
	glutMainLoop();
	return 0;
}
