/*
 * Transforms.c
 *
 *  Created on: 17 feb. 2020
 *      Author: alfre
 */
#include "Transforms.h"
#
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void translate(Mat4* csMatrix, float tx, float ty, float tz) {
	Mat4 trMatrix;
	mIdentity(&trMatrix);
	trMatrix.at[0][3] = tx;
	trMatrix.at[1][3] = ty;
	trMatrix.at[2][3] = tz;
	mMult(csMatrix, trMatrix);
	// mPrint(*csMatrix);
}

void rotateX(Mat4* csMatrix, float degrees) {
	Mat4 rotMatrix;
	mIdentity(&rotMatrix);
	float radians = degrees * M_PI / 180;
	rotMatrix.at[1][1] =  cos(radians);
	rotMatrix.at[1][2] = -sin(radians);
	rotMatrix.at[1][2] =  sin(radians);
	rotMatrix.at[2][2] =  cos(radians);
	mMult(csMatrix, rotMatrix);

}

void rotateY(Mat4* csMatrix, float degrees) {
	Mat4 rotMatrix;
	mIdentity(&rotMatrix);
	float radians = degrees * M_PI / 180;
	rotMatrix.at[0][0] =  cos(radians);
	rotMatrix.at[0][2] = sin(radians);
	rotMatrix.at[2][0] =  -sin(radians);
	rotMatrix.at[2][2] =  cos(radians);
	mMult(csMatrix, rotMatrix);
}

void rotateZ(Mat4* csMatrix, float degrees) {
	Mat4 rotMatrix;
	mIdentity(&rotMatrix);
	float radians = degrees * M_PI / 180;
	rotMatrix.at[0][0] =  cos(radians);
	rotMatrix.at[0][1] = -sin(radians);
	rotMatrix.at[1][0] =  sin(radians);
	rotMatrix.at[1][1] =  cos(radians);
	mMult(csMatrix, rotMatrix);
	// mPrint(*csMatrix);
}

void scale (Mat4* csMatrix, float sx, float sy, float sz) {
	Mat4 scMatrix;
	mIdentity(&scMatrix);
	scMatrix.at[0][0] = sx;
	scMatrix.at[1][1] = sy;
	scMatrix.at[2][2] = sz;
	mMult(csMatrix, scMatrix);
	// mPrint(*csMatrix);
}

struct strNode{
	Mat4* data;
	struct strNode* prior;
};

typedef struct strNode* Node;

typedef struct {
	Node top;
	int size;
}Stack;

Stack stack = {NULL,0};

void clearStack() {
	Node current = stack.top;
	while(current != NULL) {
		Node tmp = current->prior;
		free(current->data);
		free(current);
		current = tmp;
	}
	stack.top = NULL;
	stack.size = 0;
}

void loadIdentity(Mat4* m) {
	mIdentity(m);
	clearStack();
}

void pushMatrix(Mat4* m) {
	Node n = (Node) malloc(sizeof(struct strNode));
	Mat4* mat = (Mat4*) malloc(sizeof(Mat4));
	int i = 0;
	for(; i < 16; i++) {
		mat->values[i] = m->values[i];
	}
	n->data = mat;
	n->prior = stack.top;
	stack.top = n;
	stack.size++;
}

void popMatrix(Mat4* m) {
	if(stack.size == 0) return;
	int i = 0;
	for(; i < 16; i++) {
		m->values[i] = stack.top->data->values[i];
	}
	Node tmp = stack.top;
	stack.top = tmp->prior;
	free(tmp->data);
	free(tmp);
	stack.size--;
}


void setOrtho(Mat4* m, float left, float right, float bottom, float top, float far, float near){
	mIdentity(m);
	m->at[0][0] = 2 / (right - left);
	m->at[1][1] = 2 / (top - bottom);
	m->at[2][2] = 2 / (near - far);
	m->at[0][3] = -(right + left) / (right - left);
	m->at[1][3] = -(top + bottom) / (top - bottom);
	m->at[2][3] = -(near + far) / (near - far);
	mPrint(*m);
}

