/*
 * Practica.cpp
 *
 *  Created on: 17/02/2020
 *      Author: Alfredo Rodriguez
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "Utils.h"
#include "Transforms.h"

#define PEAKS 16
#define INNER_RADIUS 0.25
#define OUTER_RADIUS 0.5


GLuint programId, winSizeLoc, vertexArrayId, bufferId[2], vertexPosLoc, vertexColorLoc;
static float positionArray[PEAKS * 2 * 2 + 4]; // PEAKS * 2 for internal & external points * 2 for dimensions + 4 due to triangle fan elements needed
static float colorArray[PEAKS * 2 * 3 + 4];

float absolute(float value) {
	if(value < 0.0) {
		return value * -1;
	}
	return value;
}

void fillArray() {
	float step = (2 * M_PI) / (PEAKS * 2), angle = 0.0;
	int i = 0, j = 2, c = 3;
	positionArray[0] = 0.0;
	positionArray[1] = 0.0;
	colorArray[0] = 1.0;
	colorArray[1] = 1.0;
	colorArray[2] = 1.0;
	for(i = 0, j = 2, c = 3; i < (PEAKS * 2); i++, angle += step) {
		if((i % 2) == 0) {
			positionArray[j++] = OUTER_RADIUS * cos(angle);
			positionArray[j++] = OUTER_RADIUS * sin(angle);
			colorArray[c++] = absolute(sin(angle));
			colorArray[c++] = absolute(cos(angle));
			if(OUTER_RADIUS * sin(angle) > 0){
				colorArray[c++] = 0.0;
			} else {
				colorArray[c++] = 0.5;
			}
		} else {
			positionArray[j++] = INNER_RADIUS * cos(angle);
			positionArray[j++] = INNER_RADIUS * sin(angle);
			colorArray[c++] = absolute(sin(angle));
			colorArray[c++] = absolute(cos(angle));
			if(INNER_RADIUS * sin(angle) > 0){
				colorArray[c++] = 0.0;
			} else {
				colorArray[c++] = 0.5;
			}
		}
	}
	if((i % 2) == 0) {
		positionArray[j++] = OUTER_RADIUS * cos(angle);
		positionArray[j++] = OUTER_RADIUS * sin(angle);
		colorArray[c++] = absolute(sin(angle));
		colorArray[c++] = absolute(cos(angle));
		if(OUTER_RADIUS * sin(angle) > 0){
			colorArray[c++] = 0.0;
		} else {
			colorArray[c++] = 0.5;
		}
	} else {
		positionArray[j++] = INNER_RADIUS * cos(angle);
		positionArray[j++] = INNER_RADIUS * sin(angle);
		colorArray[c++] = absolute(sin(angle));
		colorArray[c++] = absolute(cos(angle));
		if(INNER_RADIUS * sin(angle) > 0){
			colorArray[c++] = 0.0;
		} else {
			colorArray[c++] = 0.5;
		}
	}
	for(int k = 0; k < (PEAKS * 2 * 2 + 4); k++) {
		printf("%f ",positionArray[k]);
	}
	printf("\n");
	for(int k = 0; k < (PEAKS * 3 * 2 + 4); k++) {
		printf("%f ",colorArray[k]);
	}
}

static void initShaders(){
	GLuint vShaderId = compileShader("Shaders/ejercicio2.vsh",GL_VERTEX_SHADER);
	if(!shaderCompiled(vShaderId)) return;
	GLuint fShaderId = compileShader("Shaders/ejercicio2.fsh",GL_FRAGMENT_SHADER);
	if(!shaderCompiled(fShaderId)) return;
	programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);
	vertexPosLoc = glGetAttribLocation(programId, "vertexPosition");
	vertexColorLoc = glGetAttribLocation(programId, "color");
	winSizeLoc = glGetUniformLocation(programId, "windowSize");
}

static void init() {
	fillArray();
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	glGenBuffers(2, bufferId);
	// Vertex array
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray), positionArray, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(vertexPosLoc);
    // Color array
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorArray), colorArray, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(vertexColorLoc);

}

static void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programId);
	glBindVertexArray(vertexArrayId);
	glUniform2f(winSizeLoc, (float) glutGet(GLUT_WINDOW_WIDTH), (float) glutGet(GLUT_WINDOW_HEIGHT));
	glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(positionArray) / 4 / 2);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	int w = 600, h = 600;
	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;
	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Ejercicio 2");
	glutDisplayFunc(display);
	glewInit();
	glClearColor(0.5, 0.5, 0.5, 1.0);
	initShaders();
	init();
	glutMainLoop();
	return 0;
}
