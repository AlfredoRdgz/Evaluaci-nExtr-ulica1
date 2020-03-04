///*
// * Practica.cpp
// *
// *  Created on: 17/02/2020
// *      Author: Alfredo Rodriguez
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <math.h>
//#include "Utils.h"
//#include "Transforms.h"
//
//GLuint programId, winSizeLoc;
//GLuint vertexArrayId, bufferId;
//static float pos[] = {-1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0};
//
//static void initShaders(){
//	// GLuint fShaderId = compileShader("Shaders/bnwEj1.fsh",GL_FRAGMENT_SHADER); // Uncomment for Black & White mode
//	GLuint fShaderId = compileShader("Shaders/colorEj1.fsh",GL_FRAGMENT_SHADER); // Uncomment for color mode
//	if(!shaderCompiled(fShaderId)) return;
//	programId = glCreateProgram();
//	glAttachShader(programId, fShaderId);
//	glLinkProgram(programId);
//	winSizeLoc = glGetUniformLocation(programId, "windowSize");
//}
//
//static void init() {
//	glGenVertexArrays(1, &vertexArrayId);
//	glBindVertexArray(vertexArrayId);
//	glGenBuffers(1, &bufferId);
//	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
//	glVertexPointer(2, GL_FLOAT, 0, 0);
//	glEnableClientState(GL_VERTEX_ARRAY);
//}
//
//static void display() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glUseProgram(programId);
//	glBindVertexArray(vertexArrayId);
//	glUniform2f(winSizeLoc, (float) glutGet(GLUT_WINDOW_WIDTH), (float) glutGet(GLUT_WINDOW_HEIGHT));
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	int w = 600, h = 600;
//	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
//	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;
//	glutInitWindowSize(w, h);
//	glutInitWindowPosition(x, y);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutCreateWindow("Ejercicio 1");
//	glutDisplayFunc(display);
//	glewInit();
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	initShaders();
//	init();
//	glutMainLoop();
//	return 0;
//}
