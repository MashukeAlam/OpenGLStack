/** All include libraries **/
// #include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <utility>

/** Important globals **/
#define SPACEBAR 32
#define SLIDING_LIMIT 60
struct point;
GLfloat zzz = 5;
void drawSphere(double radius,int slices,int stacks);
void drawCone(double radius,double height,int segments);
void drawCube(GLfloat cPosX, GLfloat cPosY, GLfloat cPosZ, GLfloat sideLenX, GLfloat sideLenY, GLfloat sideLenZ);
const GLfloat zDepthOfCube = 7.5f;
int currSuspect = 0;
bool directionOfSliding = false; // 0 means X | 1 means Y
int cameraPosX = 100;
int cameraPosY = 100;
int cameraPosZ = 100;

int multiplicant = 1;
const std::pair<int, int> colorChangeHelper[3] = { std::make_pair(1, 2), std::make_pair(0, 2), std::make_pair(1, 0) };
int currColor = 0;

struct point{
    double x,y,z;
};

const point defaultColors[3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};


struct cubePointVals {
    GLfloat centerPosX,centerPosY, centerPosZ, sideLenX, sideLenY, sideLenZ;
    GLfloat color[3];
};


struct point positionOfBalls[3] ={{20,30,0},{40,30,0},{50,50,0}};
const struct cubePointVals defaultCube = {20, 20, 20, 40, 30, zDepthOfCube, {1.0f, 0.0f, 0.0f}};
std::vector<cubePointVals> cubePointValsArr{ defaultCube };

float radiusOfBalles[3] = {10,10,10};

float speedOfBall = 0.2;
float highestZCoordinate = 40;
float lowestZCoordinate = -40;
float angleOfCone = 0;
float rotationSpeedOfCone = 0.5;
float radiusOfBallOnCone = 10;
float radiusOfCone = 20;
float heightOfCone = 40;
float ballsZCoordinate = 0;
float coneAndBallScalingFactor[3] = {1.2,1.2,0.8};

bool directionOfBall = false; //This parameter value can be changed only 



void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();

}



void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,	0,0,0,	0,0,1);

	glMatrixMode(GL_MODELVIEW);


	drawAxes();
    const int lenOfThatGoddamnArray = cubePointValsArr.size();
    currSuspect = lenOfThatGoddamnArray - 1;

    glPushMatrix();
    
    for (int i = 0; i < lenOfThatGoddamnArray; i++) {
        const struct cubePointVals curr = cubePointValsArr[i];
        glColor3f(curr.color[0], curr.color[1], curr.color[2]);
        drawCube(curr.centerPosX, curr.centerPosY, curr.centerPosZ, curr.sideLenX, curr.sideLenY, curr.sideLenZ);
    }
    // cubePointValsArr.push_back({10, 10, 20, 20, 20, zDepthOfCube});
    
    glPopMatrix();

	glutSwapBuffers();
}


void animate(){
    
    if(directionOfSliding) {
        // directionOfSliding = !directionOfSliding;
        if(abs(cubePointValsArr[currSuspect].centerPosX) == SLIDING_LIMIT) {
            multiplicant *= -1;
        }
        cubePointValsArr[currSuspect].centerPosX += multiplicant;
    } else {
        if(abs(cubePointValsArr[currSuspect].centerPosY) == SLIDING_LIMIT) {
            multiplicant *= -1;
        }
        cubePointValsArr[currSuspect].centerPosY += multiplicant;
    }
	glutPostRedisplay();
}
