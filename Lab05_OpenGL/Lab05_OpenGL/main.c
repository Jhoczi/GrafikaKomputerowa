/*
 * CPSC 424, Fall 2015, Lab 4:  Some objects in 3D.  The arrow keys
 * can be used to rotate the object.  The number keys 1 through 5
 * select the object.  The space bar toggles the use of anaglyph
 * stereo.  Compile this program with:
 *
 *           gcc -o lab4 lab4.c -lGL -lglut
 */
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

 //-------------------Data for stellated dodecahedron ------------------

double dodecVertices[][3] = {
    {-0.650000,0.000000,-0.248278},
    {0.401722,0.401722,0.401722},            // This array contains the coordinates
    {0.650000,0.000000,0.248278},            // for the vertices of the polyhedron
    {0.401722,-0.401722,0.401722},           // known as a stellated dodecahedron
    {0.000000,-0.248278,0.650000},
    {0.000000,0.248278,0.650000},            // Each row of the 2D array contains
    {0.650000,0.000000,-0.248278},           // the xyz-coordinates for one of
    {0.401722,0.401722,-0.401722},           // the vertices.
    {0.248278,0.650000,0.000000},
    {-0.248278,0.650000,0.000000},
    {-0.401722,0.401722,-0.401722},
    {0.000000,0.248278,-0.650000},
    {0.401722,-0.401722,-0.401722},
    {0.248278,-0.650000,0.000000},
    {-0.248278,-0.650000,0.000000},
    {-0.650000,0.000000,0.248278},
    {-0.401722,0.401722,0.401722},
    {-0.401722,-0.401722,-0.401722},
    {0.000000,-0.248278,-0.650000},
    {-0.401722,-0.401722,0.401722},
    {0.000000,1.051722,0.650000},
    {-0.000000,1.051722,-0.650000},
    {1.051722,0.650000,-0.000000},
    {1.051722,-0.650000,-0.000000},
    {-0.000000,-1.051722,-0.650000},
    {-0.000000,-1.051722,0.650000},
    {0.650000,0.000000,1.051722},
    {-0.650000,0.000000,1.051722},
    {0.650000,-0.000000,-1.051722},
    {-0.650000,0.000000,-1.051722},
    {-1.051722,0.650000,-0.000000},
    {-1.051722,-0.650000,0.000000}
};

int dodecTriangles[][3] = {
   {16,9,20},
   {9,8,20},
   {8,1,20},              // This array specifies the faces of
   {1,5,20},              // the stellated dodecahedron.
   {5,16,20},
   {9,10,21},             // Each row in the 2D array is a list
   {10,11,21},            // of three integers.  The integers
   {11,7,21},             // are indices into the vertex array,
   {7,8,21},              // dodecVertices.  The vertices at
   {8,9,21},              // at those indices are the vertices
   {8,7,22},              // of one of the triangular faces of
   {7,6,22},              // the polyhedron.
   {6,2,22},
   {2,1,22},              // For example, the first row, {16,9,20},
   {1,8,22},              // means that vertices number 16, 9, and
   {6,12,23},             // 20 are the vertices of a face.
   {12,13,23},
   {13,3,23},             // There are 60 faces.
   {3,2,23},
   {2,6,23},
   {18,17,24},
   {17,14,24},
   {14,13,24},
   {13,12,24},
   {12,18,24},
   {14,19,25},
   {19,4,25},
   {4,3,25},
   {3,13,25},
   {13,14,25},
   {4,5,26},
   {5,1,26},
   {1,2,26},
   {2,3,26},
   {3,4,26},
   {15,16,27},
   {16,5,27},
   {5,4,27},
   {4,19,27},
   {19,15,27},
   {7,11,28},
   {11,18,28},
   {18,12,28},
   {12,6,28},
   {6,7,28},
   {10,0,29},
   {0,17,29},
   {17,18,29},
   {18,11,29},
   {11,10,29},
   {0,10,30},
   {10,9,30},
   {9,16,30},
   {16,15,30},
   {15,0,30},
   {17,0,31},
   {0,15,31},
   {15,19,31},
   {19,14,31},
   {14,17,31}
};



//------------------- TODO: Complete this section! ---------------------

int objectNumber = 1;        // Which object to draw (1 ,2, 3, 4, 5, or 6)?
                                     //   (Controlled by number keys.)

int useAnaglyph = 0; // Should anaglyph stereo be used?
                             //    (Controlled by space bar.)

int rotateX = 0;    // Rotations of the cube about the axes.
int rotateY = 0;    //   (Controlled by arrow, PageUp, PageDown keys;
int rotateZ = 0;    //    Home key sets all rotations to 0.)

const float GREEN[3] = { 0,1,0 };
const float BLUE[3] = { 0,0,1 };
const float BROWN[3] = { 0.35,0.16,0.14 };

/*
 * The function that draws the current object, with its modeling transformation.
 */

void Korkociag()
{
    float x, z;
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int count = 7000;
    float height = 1.0;
    int n = 20;
    double delta = n * M_PI / count;
    glBegin(GL_LINE_STRIP);
    glLineWidth(10);
    glColor3b(0, 0, 255);
    int r = 1;
    float angle = 270.0;
    for (int i = 1; i <= count; i++)
    {
        glColor3f(BLUE[0], BLUE[1], BLUE[2]);
        x = (float)(r * cos(angle) / 1.0);
        z = (float)(r * sin(angle) / 1.0);
        glVertex3f(x, height, z);
        angle = i * delta;
        height += n / 18000.0;
    }
    glEnd();
}
    /*glColor3f(GREEN[0],GREEN[1],GREEN[2]);
    glTranslated(0, height, -2.5);
    gluCylinder(gluNewQuadric(), 1, 1, 5, 100, 50);

    gluDisk(gluNewQuadric(), 0, 1, 100, 1);
    glTranslated(0, 0, 5);
    gluDisk(gluNewQuadric(), 0, 1, 100, 1);*/

void Piramida()
{
    float vertices2d[] =
    {
        -1.0f, 0.0f, // X Y
        1.0f, 0.0f,
        0.0f, 3.5f
    };
    float vertices3d[] =
    {
        -1.0f, 0.0f, 0.0f, // X Y Z
        1.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 6.0f
    };
    glColor3f(GREEN[0], GREEN[1], GREEN[2]);
    glBegin(GL_TRIANGLES);
        glVertex3f(vertices3d[0], vertices3d[1], vertices3d[2]);
        glVertex3f(vertices3d[3], vertices3d[4], vertices3d[5]);
        glVertex3f(vertices3d[6], vertices3d[7], vertices3d[8]);
    glEnd();
    for (int i = 1; i < 10; ++i)
    {
        glPushMatrix();
            glTranslatef(0.f, 3.0f, 0.f);
            glRotatef(i * 36, 0.f, 0.f, 1.0f);
            glTranslatef(0.f, -3.0f, 0.f);
            glBegin(GL_TRIANGLES);
                glVertex3f(vertices3d[0], vertices3d[1], vertices3d[2]);
                glVertex3f(vertices3d[3], vertices3d[4], vertices3d[5]);
                glVertex3f(vertices3d[6], vertices3d[7], vertices3d[8]);
            glEnd();
        glPopMatrix();
    }
   
}

void draw() {
    
    glRotatef(rotateZ, 0, 0, 1);   // Apply rotations to complete object.
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateX, 1, 0, 0);

    // TODO: Draw the currently selected object, number 1, 2, 3, 4, or 5.
    // (Objects should lie in the cube with x, y, and z coordinates in the
    // range -5 to 5.)
    if (objectNumber == 1)
    {
        Korkociag();
    }
    else if (objectNumber == 2)
    {
        Piramida();
    }
}

//-------------------- Draw the Scene  -------------------------

/*
 * The display function is called when the window needs to be drawn.
 * It's called when the window opens and it is called by the keyboard-handling
 * functions when the user hits a key that modifies the scene.
 */
void display() {  // Display function will draw the image.

    if (useAnaglyph) {
        glDisable(GL_COLOR_MATERIAL); // in anaglyph mode, everything is drawn in white
        float white[] = { 1,1,1,1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    }
    else {
        glEnable(GL_COLOR_MATERIAL);  // in non-anaglyph mode, glColor* is respected
    }
    glNormal3f(0, 0, 1); // (Make sure normal vector is correct for object 1.)

    glClearColor(0, 0, 0, 1); // Background color (black).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!useAnaglyph) {
        glLoadIdentity(); // Make sure we start with no transformation!
        glTranslated(0, 0, -15);  // Move object away from viewer (at (0,0,0)).
        draw();
    }
    else {
        glLoadIdentity();
        glColorMask(1, 0, 0, 1);
        glRotatef(4, 0, 1, 0);
        glTranslated(1, 0, -15);
        draw();
        glColorMask(1, 0, 0, 1);
        glClear(GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(-4, 0, 1, 0);
        glTranslated(-1, 0, -15);
        glColorMask(0, 1, 1, 1);
        draw();
        glColorMask(1, 1, 1, 1);
    }

    glutSwapBuffers(); // Required AT THE END to copy color buffer onto the screen.

} // end display()


/*  The initGL function is called once from main() to initialize
 *  OpenGL.  Here, it sets up a projection, turns on some lighting,
 *  and enables the depth test.
 */
void initGL() {
    glMatrixMode(GL_PROJECTION);
    glFrustum(-3.5, 3.5, -3.5, 3.5, 5, 25);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float gray[] = { 0.7,0.7,0.7,1 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gray);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(3);  // make wide lines for the stellated dodecahedron.
}

//-------------------- Key-handling functions ---------------------------

void doSpecialKey(int key, int x, int y) {
    // called when a special key is pressed
    int redraw = 1;
    if (key == GLUT_KEY_LEFT)
        rotateY -= 15;
    else if (key == GLUT_KEY_RIGHT)
        rotateY += 15;
    else if (key == GLUT_KEY_DOWN)
        rotateX += 15;
    else if (key == GLUT_KEY_UP)
        rotateX -= 15;
    else if (key == GLUT_KEY_PAGE_UP)
        rotateZ += 15;
    else if (key == GLUT_KEY_PAGE_DOWN)
        rotateZ -= 15;
    else if (key == GLUT_KEY_HOME)
        rotateX = rotateY = rotateZ = 0;
    else
        redraw = 0;
    if (redraw)
        glutPostRedisplay(); // will repaint the window
}

void doKeyboard(unsigned char ch, int x, int y) {
    int redraw = 1;
    if (ch == '1')
    {
        objectNumber = 1;
    }   
    else if (ch == '2')
        objectNumber = 2;
    else if (ch == '3')
        objectNumber = 3;
    else if (ch == '4')
        objectNumber = 4;
    else if (ch == '5')
        objectNumber = 5;
    else if (ch == '6')
        objectNumber = 6;
    else if (ch == ' ')
        useAnaglyph = !useAnaglyph;
    else
        redraw = 0;
    if (redraw)
        glutPostRedisplay(); // will repaint the window
}


// --------------------------- main() -------------------------------------

int main(int argc, char** argv) {  // Initialize GLUT and open the window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  // Use double-buffering and depth buffer.
    glutInitWindowSize(700, 700);            // Size of display area, in pixels.
    glutInitWindowPosition(100, 100);        // Location of window in screen coordinates.
    glutCreateWindow("Some Objects in 3D"); // Parameter is window title.
    initGL();   // Call the OpenGL initialization function, defined above; must be after glutCreateWindow.
    glutDisplayFunc(display);               // display() is called when the window needs to be redrawn.
    glutKeyboardFunc(doKeyboard);           // doKeyboard() is called to process normal keys.
    glutSpecialFunc(doSpecialKey);          // doSpecialKey() is called to process other keys (such as arrows).
    glutMainLoop();
    return 0;
}
