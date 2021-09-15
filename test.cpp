//#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include<vector>
#define pi (2*acos(0.0))
struct point;

void drawSphere(double radius,int slices,int stacks);
void drawCone(double radius,double height,int segments);



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
    glColor3f( 1.0f, 0.0f, 0.0f );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
}






struct point{
    double x,y,z;
};
struct cubePointVals {
    GLfloat centerPosX,centerPosY, centerPosZ, sideLenX, sideLenY, sideLenZ;
};


struct point positionOfBalls[3] ={{20,30,0},{40,30,0},{50,50,0}};
std::vector<cubePointVals> cubePointValsArr{ {20, 20, 20, 40, 30, 5} };


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


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(100,100,100,	0,0,0,	0,0,1);



	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();


    // glPushMatrix();
    // glScaled(coneAndBallScalingFactor[0], coneAndBallScalingFactor[1], coneAndBallScalingFactor[2]);
    // glRotatef(angleOfCone, 0, 1, 0); // 145 % 3 = 1, so as per question, y axis will be rotated.
    // drawCone(radiusOfCone, 40, 40);
    // glTranslated(0, 0, radiusOfBallOnCone + heightOfCone);
    // drawSphere(radiusOfBallOnCone, 40, 40);
    // glPopMatrix();

    // glPushMatrix();
    // glTranslated(positionOfBalls[0].x, positionOfBalls[0].y, positionOfBalls[0].z);
    // drawSphere(10, 40, 40);
    // glPopMatrix();

    // glPushMatrix();
    // glTranslated(positionOfBalls[1].x, positionOfBalls[1].y, positionOfBalls[1].z);
    // drawSphere(10, 40, 40);
    // glPopMatrix();
    glPushMatrix();
    for (int i = 0; i < cubePointValsArr.size(); i++){
      const struct cubePointVals curr = cubePointValsArr[i];

      drawCube(curr.centerPosX, curr.centerPosY, curr.centerPosZ, curr.sideLenX, curr.sideLenY, 5);

    }

    glPopMatrix();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){

	//codes for any changes in Models, Camera
	angleOfCone += rotationSpeedOfCone;
    if(directionOfBall) {
          cubePointValsArr.push_back({10,10,positionOfBalls[0].z,10,10,5});

      cubePointValsArr[0].centerPosX ++;
        int currZpos = positionOfBalls[0].z;
        if(currZpos == highestZCoordinate) {
            directionOfBall = !directionOfBall;
        } else {
            currZpos ++;
            for(int i = 0; i < 3; i++) {
                positionOfBalls[i].z = currZpos;
            }
        }
    } else {
        int currZpos = positionOfBalls[0].z;
        if(currZpos == lowestZCoordinate) {
            directionOfBall = !directionOfBall;
        } else {
            currZpos --;
            for(int i = 0; i < 3; i++) {
                positionOfBalls[i].z = currZpos;
            }
        }
    }
    // marks the current window as needing to be redisplayed
    glutPostRedisplay();
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view -
	//in the X direction (horizontally) = width/height
	//near distance
	//far distance
}


void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
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


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
