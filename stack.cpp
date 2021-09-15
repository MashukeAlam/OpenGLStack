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
// GLfloat zzz = 5;
// void drawSphere(double radius,int slices,int stacks);
// void drawCone(double radius,double height,int segments);
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
    
    glPopMatrix();

	glutSwapBuffers();
}


void animate(){
    
    if(directionOfSliding) {
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


void init(){

	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(80,	1,	1,	5000.0);
}



void drawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLengthX, GLfloat edgeLengthY, GLfloat edgeLengthZ )
{
    GLfloat halfSideLengthX = edgeLengthX * 0.5f;
    GLfloat halfSideLengthY = edgeLengthY * 0.5f;
    GLfloat halfSideLengthZ = edgeLengthZ * 0.5f;
    
    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ, // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ, // bottom left
        
        // back face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom left
        
        // left face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // top left
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // top right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ, // bottom left
        
        // right face
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ, // bottom left
        
        // top face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // top left
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // top right
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom right
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ + halfSideLengthZ, // bottom left
        
        // top face
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ, // top left
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ - halfSideLengthZ, // bottom right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ + halfSideLengthZ  // bottom left
    };
    
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // glColor3f( 1.0f, 0.0f, 0.0f );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
}



void myKeyBoard(unsigned char key, int x, int y){


   switch (key)
   {
       case SPACEBAR:
            std::pair<int, int> toChange = colorChangeHelper[currColor];
            GLfloat lastCubeColor[3] = {cubePointValsArr[currSuspect].color[0], cubePointValsArr[currSuspect].color[1], cubePointValsArr[currSuspect].color[2]};
            lastCubeColor[toChange.first] += 0.1;
            lastCubeColor[toChange.second] += 0.1;
            GLfloat red = lastCubeColor[0];
            GLfloat green = lastCubeColor[1];
            GLfloat blue = lastCubeColor[2];

            if (cubePointValsArr.size() % 10 == 0) {
                currColor = (currColor + 1) % 3;
                red = defaultColors[currColor].x;
                green = defaultColors[currColor].y;
                blue = defaultColors[currColor].z;
                std::cout << currColor << " " << red << " " << green << " " << blue << " " << cubePointValsArr.size() << "\n";
            }
            
            cameraPosZ += 7.5;
            cameraPosY += 3;
            cameraPosX += 3;
            cubePointValsArr.push_back({20, 20, 20 + (zDepthOfCube * cubePointValsArr.size()), 40, 30, zDepthOfCube, {red, green, blue}});
            break;
   }
   glutPostRedisplay();
}


int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	/*
	GLUT_DOUBLE - allows for display on the double buffer window

    GLUT_RGB - shows color (Red, green, blue)

    GLUT_DEPTH - allows for depth buffer
    */

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);
	//When depth testing is enabled, OpenGL tests the depth value
	//of a fragment against the content of the depth buffer

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
    glutKeyboardFunc(myKeyBoard);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
