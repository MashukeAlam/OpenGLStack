/** All include libraries **/
// #include<windows.h>
#include <GL/glut.h>
#include <math.h>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

/** Important globals **/
#define SPACEBAR 32
#define SLIDING_LIMIT 60
#define NUM_OF_COLORS 5

// for scoring
int s = 0;

// Game Over
bool over = false;

struct point;
void drawCube(GLfloat cPosX, GLfloat cPosY, GLfloat cPosZ, GLfloat sideLenX,
              GLfloat sideLenY, GLfloat sideLenZ);
const GLfloat zDepthOfCube = 7.5f;
int currSuspect = 0;
bool directionOfSliding = false;  // 0 means X | 1 means Y

// Camera positions need to be changed.
int cameraPosX = 100;
int cameraPosY = 100;
int cameraPosZ = 100;

// To alter sliding direction
int multiplicant = 1;

// Which colors to change when color is `currColor`
int currColor = 0;
const std::pair<int, int> colorChangeHelper[NUM_OF_COLORS] = {
    std::make_pair(1, 2), std::make_pair(0, 2), std::make_pair(1, 0),
    std::make_pair(0, 2), std::make_pair(1, 2)};

// Only used in `default colors`
struct point {
    double x, y, z;
};

// When color becomes white then use this to reset color.
const point defaultColors[NUM_OF_COLORS] = {{1.0f, 0.0f, 0.0f},
                                            {0.0f, 1.0f, 0.0f},
                                            {0.0f, 0.0f, 1.0f},
                                            {0.25f, 0.10f, 0.2f},
                                            {0.7f, 0.1f, 0.1f}};

// Brain and bron of cubes. All configs of it.
struct cubePointVals {
    GLfloat centerPosX, centerPosY, centerPosZ, sideLenX, sideLenY, sideLenZ;
    GLfloat color[3];
};

// Not used more than once. Shouda delete it.
const struct cubePointVals defaultCube = {
    20, 20, 20, 40, 30, zDepthOfCube, {1.0f, 0.0f, 0.0f}};

// Array for holding all cubes.
std::vector<cubePointVals> cubePointValsArr{defaultCube, defaultCube};

void drawAxes() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1000, 0, 0);
        glVertex3f(-1000, 0, 0);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, 0, 0, 0, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    // drawAxes();
    const int lenOfThatGoddamnArray = cubePointValsArr.size();
    currSuspect = lenOfThatGoddamnArray - 1;

    const std::string score = "Score: " + std::to_string(s);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, GLUT_WINDOW_WIDTH, 0.0, GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 1.0f);
    glRasterPos2f(10.0f, 55.0f);
    glTranslatef(5, 50, -25);
    for (int i = 0; score[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);

    if (over) {
        const std::string gameOver = "Game Over!";
        glColor3f(1.0f, 0.0f, 1.0f);
        glRasterPos2f(10.0f, 55.0f);
        glTranslatef(5, 50, -25);
        for (int i = 0; gameOver[i]; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
        return;
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Cube draw... grab all cubes and draw it.
    glPushMatrix();

    for (int i = 0; i < lenOfThatGoddamnArray; i++) {
        const struct cubePointVals curr = cubePointValsArr[i];
        glColor3f(curr.color[0], curr.color[1], curr.color[2]);
        // std::cout << curr.centerPosY << " \n";
        drawCube(curr.centerPosX, curr.centerPosY, curr.centerPosZ, curr.sideLenX,
                 curr.sideLenY, curr.sideLenZ);
    }

    glPopMatrix();

    glutSwapBuffers();
}

// To animate the sliding
void animate() {
    if (over) {
        return;
    }

    if (directionOfSliding) {
        if (abs(cubePointValsArr[currSuspect].centerPosX) == SLIDING_LIMIT) {
            multiplicant *= -1;
        }
        cubePointValsArr[currSuspect].centerPosX += multiplicant;
    } else {
        if (abs(cubePointValsArr[currSuspect].centerPosY) == SLIDING_LIMIT) {
            multiplicant *= -1;
        }
        cubePointValsArr[currSuspect].centerPosY += multiplicant;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 1, 1, 5000.0);
}

void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ,
              GLfloat edgeLengthX, GLfloat edgeLengthY, GLfloat edgeLengthZ) {
    GLfloat halfSideLengthX = edgeLengthX * 0.5f;
    GLfloat halfSideLengthY = edgeLengthY * 0.5f;
    GLfloat halfSideLengthZ = edgeLengthZ * 0.5f;

    GLfloat vertices[] = {
        // front face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // bottom left

        // back face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom left

        // left face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top left
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // bottom left

        // right face
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // bottom left

        // top face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top left
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top right
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom right
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // bottom left

        // top face
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ,  // top left
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ - halfSideLengthZ,  // bottom right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY,
        centerPosZ + halfSideLengthZ  // bottom left
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void keyboardListener(unsigned char key, int x, int y) {
    switch (key) {
        case SPACEBAR:
            over = true;
            std::pair<int, int> toChange = colorChangeHelper[currColor];
            GLfloat lastCubeColor[3] = {cubePointValsArr[currSuspect].color[0],
                                        cubePointValsArr[currSuspect].color[1],
                                        cubePointValsArr[currSuspect].color[2]};
            lastCubeColor[toChange.first] += 0.1;
            lastCubeColor[toChange.second] += 0.1;

            GLfloat red = lastCubeColor[0];
            GLfloat green = lastCubeColor[1];
            GLfloat blue = lastCubeColor[2];

            GLfloat previousCenterX = cubePointValsArr[currSuspect - 1].centerPosX;
            GLfloat previousCenterY = cubePointValsArr[currSuspect - 1].centerPosY;
            GLfloat currSideLenX = cubePointValsArr[currSuspect].sideLenX;
            GLfloat currSideLenY = cubePointValsArr[currSuspect].sideLenY;
            GLfloat currCenterX = cubePointValsArr[currSuspect].centerPosX;
            GLfloat currCenterY = cubePointValsArr[currSuspect].centerPosY;

            GLfloat newLenX, newLenY;

            GLfloat distanceBetweenCenterX = abs(previousCenterX - currCenterX);
            GLfloat distanceBetweenCenterY = abs(previousCenterY - currCenterY);
            GLfloat halfSideLengthByX = std::max(currSideLenX * 0.5f, 1.0f);
            GLfloat halfSideLengthByY = std::max(currSideLenY * 0.5f, 1.0f);
            GLfloat gapBetweenTwoCubeByX =
                distanceBetweenCenterX - (halfSideLengthByX * 2);
            GLfloat gapBetweenTwoCubeByY =
                distanceBetweenCenterY - (halfSideLengthByY * 2);

            if (gapBetweenTwoCubeByX >= 0) {
                std::cout << " Game Over! X "
                          << " " << halfSideLengthByX << " " << distanceBetweenCenterX
                          << " " << gapBetweenTwoCubeByX << "\n";
            } else {
                newLenX = abs(gapBetweenTwoCubeByX);
            }

            if (gapBetweenTwoCubeByY >= 0) {
                std::cout << " Game Over! Y " << gapBetweenTwoCubeByY << "\n";
            } else {
                newLenY = abs(gapBetweenTwoCubeByY);
            }

            s++;

            // If color becomes white
            if (cubePointValsArr.size() % 10 == 0) {
                currColor = (currColor + 1) % NUM_OF_COLORS;  // Devil of my headache.
                red = defaultColors[currColor].x;
                green = defaultColors[currColor].y;
                blue = defaultColors[currColor].z;
            }

            cameraPosZ += 7.5;
            cameraPosY += 5;
            cameraPosX += 4.5;

            cubePointValsArr[currSuspect].sideLenX = newLenX;
            cubePointValsArr[currSuspect].sideLenY = newLenY;
            cubePointValsArr.push_back(
                {currCenterX,
                 currCenterY,
                 20 + (zDepthOfCube * cubePointValsArr.size() - 1),
                 newLenX,
                 newLenY,
                 zDepthOfCube,
                 {red, green, blue}});

            directionOfSliding = !directionOfSliding;
            over = false;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Stack");

    init();

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);

    glutMainLoop();

    return 0;
}
