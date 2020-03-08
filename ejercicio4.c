#define RESET 0xFFFF

#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Utils.h"
#include <time.h>

#define COLUMNS 30
#define ROWS 30

GLint  programID;
GLuint vertexArrayId;
GLuint bufferId[3];

static float vertexPosition[ (ROWS+1) * (COLUMNS+1) * 2] = {};
static float vertexColor   [(ROWS+1)*(COLUMNS+1) * 3] = {};
static GLushort indexes   [((COLUMNS+1) * 2) * ROWS + ROWS ] = {};

void init(){
    GLuint vshID=compileShader("shaders/ejercicio4.vsh", GL_VERTEX_SHADER);
    GLuint fshID=compileShader("shaders/ejercicio4.fsh", GL_FRAGMENT_SHADER);

    if(!shaderCompiled(vshID)){
        return;
    }
	if(!shaderCompiled(fshID)){
        return;
    }

    programID=glCreateProgram();
    glAttachShader(programID, vshID);
    glAttachShader(programID, fshID);
    glLinkProgram(programID);
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glGenBuffers(3,bufferId);

    GLuint vertexPosLoc=glGetAttribLocation(programID, "vertexPosition");
    GLuint vertexColLoc=glGetAttribLocation(programID, "vertexColor");

    glBindBuffer(GL_ARRAY_BUFFER,bufferId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexPosLoc);

    glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexColLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexColLoc);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	glPrimitiveRestartIndex(RESET);
	glEnable(GL_PRIMITIVE_RESTART);
}

void fill_arrays(int rows, int columns){
    float inc_y =-2.0/rows;
    float inc_x =2.0/columns;
    float y = 1.0;
    int count =0;
    int countColor=0;
    for(int i=0; i < rows + 1; i++){
        float x = -1.0;
        for(int j=0;j<columns+1;j++){
            vertexPosition[count++] = x;
            vertexPosition[count++] = y;
            vertexColor[countColor++] = (float)rand()/RAND_MAX;
            vertexColor[countColor++] = (float)rand()/RAND_MAX;
            vertexColor[countColor++] = (float)rand()/RAND_MAX;
            x += inc_x;
        }
        y +=inc_y;
    }
    count=0;
    for(int j=0; j < rows; j++){
        for(int i = 0; i < columns + 1; i++){
            indexes[count++] = i + (j + 1)*(columns + 1);
            indexes[count++] =i + (j) * (columns + 1);
        }
        indexes[count++] = RESET;
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4.0);
	glUseProgram(programID);
	glBindVertexArray(vertexArrayId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
	glDrawElements(GL_TRIANGLE_STRIP,((COLUMNS+1)*2)*ROWS+ROWS,GL_UNSIGNED_SHORT,0);

	glutSwapBuffers();
}

static void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
    glutInit(&argc, argv);
	int ww = 600;
	int wh = 600;
	int sw = glutGet(GLUT_SCREEN_WIDTH);
	int sh = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((sw - ww) / 2, (sh - wh) / 2);
	glutInitWindowSize(ww, wh);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ejercicio 4");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardFunc);
    glewInit();
    fill_arrays(ROWS, COLUMNS);
    init();
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glutMainLoop();
    return 0;
}
