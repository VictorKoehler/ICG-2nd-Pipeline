#include <GL/glut.h>
#include <objectmodel.h>
#include <definitions.h>
#include <bits/stdc++.h>


using namespace std;


// https://www.opengl.org/discussion_boards/showthread.php/197726-Draw-Sphere



//float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
bool reshape = false;

ObjectModel obj;

float   cam_pos_x = 1.4f, cam_pos_y = 1.0f, cam_pos_z = 2.2f,
        cam_lookat_x = 0, cam_lookat_y = 0, cam_lookat_z = 0,
        cam_up_x = 0, cam_up_y = 1, cam_up_z = 0;


float fovy = 90.0f, zNear = 0.1f, zFar = 100.0f;
 
//------------------------------  reshapeFunc  ---------------------------------
 
// Redimensiona a tela. No entanto, a intenção primária é manter uma tela fixa.
void reshapeFunc (int x, int y)
{
    if (!reshape)
    {
        x = IMAGE_WIDTH;
        y = IMAGE_WIDTH;
    }
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (fovy, (GLdouble)x / (GLdouble)y, zNear, zFar);
    glMatrixMode   (GL_MODELVIEW);
    glViewport     (0, 0, x, y);
}

void drawAxisLines()
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 1.f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
	glEnd();
}

void drawObject(ObjectModel o)
{
    for (vector<Vertex>::iterator it = o.vertices.begin(); it != o.vertices.end(); it++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3f(it->v0.x(), it->v0.y(), it->v0.z());
        glVertex3f(it->v1.x(), it->v1.y(), it->v1.z());
        glVertex3f(it->v2.x(), it->v2.y(), it->v2.z());
        glEnd();
    }
}


//------------------------------  Draw_Spheres   -------------------------------
 
void Draw_Spheres (void)
{
    glMatrixMode   (GL_MODELVIEW);
    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    //glTranslatef    (0.0, 0.0, -5.0);
    gluLookAt(  cam_pos_x, cam_pos_y, cam_pos_z,
                cam_lookat_x, cam_lookat_y, cam_lookat_z,
                cam_up_x, cam_up_y, cam_up_z);
 
    /*
    glColor3f (0.8, 0.2, 0.1);              // Red ball displaced to left.
    glPushMatrix ();
       glTranslatef    (-1.5, 0.0, 0.0);
       glRotatef       (60.0, 1,0,0);
       glRotatef       (zRotated*2.0, 0,0,1);   // Red ball rotates at twice the rate of blue ball.
       glutSolidSphere (1.0, 20, 50);
    glPopMatrix ();
 
    glColor3f (0.1, 0.2, 0.8);              // Blue ball displaced to right.
    glPushMatrix ();
       glTranslatef    (1.5, 0.0, 0.0);
       glRotatef       (60.0, 1,0,0);
       glRotatef       (zRotated, 0,0,1);
       glutSolidSphere (1.0, 20, 50);
    glPopMatrix ();
    
    glPushMatrix ();
       glTranslatef    (-1.5, 0.0, 0.0);
       glRotatef       (60.0, 1,0,0);
       glRotatef       (zRotated*2.0, 0,0,1);   // Red ball rotates at twice the rate of blue ball.
       glutSolidSphere (1.0, 20, 50);
    glPopMatrix ();
    */
    glColor3f (1, 1, 1);
    drawObject(obj);
    //drawAxisLines();
    
    glutSwapBuffers();
}
 
//--------------------------------  idleFunc  ----------------------------------
 
void idleFunc (void)
{
    //zRotated += 0.3;
    glutPostRedisplay();
}
 
//----------------------------------  main  ------------------------------------
 
int main (int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Pass one file to load as argument.\n");
        return 0;
    }
    if (argc > 2 && argv[2][0] == '-' && argv[2][1] == 'r')
        reshape = true;
    obj = ObjectModel(string(argv[1]));

    glutInit               (&argc, argv);
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize     (IMAGE_WIDTH, IMAGE_HEIGHT);
    glutInitWindowPosition (200, 200);
    glutCreateWindow       ("OpenGL + Assimp (ObjectModel) loader");
    glPolygonMode          (GL_FRONT_AND_BACK, GL_LINE);
 
    glClearColor (0.0, 0.0, 0.0, 0.0);
 
    glutDisplayFunc (Draw_Spheres);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);
 
    glutMainLoop();

    return 0;
}