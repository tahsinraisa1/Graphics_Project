/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include "RGBpixmap.cpp"

float degree=0, degree1=0, degree2=0,tx=-6.75,ty=0,tz=-17,scale=0.3,tt=0,high_shininess=100.0f;
float cx=0,cy=0,cz=-2,ux=0,uy=1,uz=0,xx=0.0,yy=45,yz=0,xz=45,ex=0,ey=1,ez=8,rr=40,rs=5,zz=0;
int fl=0,fgg,wk=0,l1f=0,l2f=0;
static int stacks=26;
static int slices=26;
float ne=2.0, fa=100.0;
/* GLUT callback Handlers */
const float DEG2RAD = 3.14159/180;
double angle=0;
RGBpixmap pix[6];

GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat mat_ambient[]    = { 0.6f, 0.9f, 0.6f, 1.0f };
GLfloat mat_ambient1[]    = { 0.75f,0.22f,0.667f, 1.0f };
GLfloat mat_ambient2[]    = { .43f,.67f,.09f, 1.0f };
GLfloat mat_ambient3[]    = { 0.33f, 0.56f, 0.8f, 1.0f };
GLfloat mat_ambient4[]    = { 0.4f, 0.3f, 0.2f, 1.0f };
GLfloat mat_red[]    = { 1,0,0, 1.0f };
GLfloat mat_green[]    = { 0,1,0, 1.0f };

const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { -6,18,10, 1.0f };

const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = { 30,18,-1, 1.0f };

const GLfloat light_diffuse2[]  = { 0.7f, 0.3f, 0.5f, 1.0f };
const GLfloat light_specular2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position2[] = { 12, 18.0, -6.0, 1.0 };
const GLfloat spot_direction[] = { -1.0, -1.0, -1.0 };

const GLfloat no_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };


const GLfloat mat_diffuse[]    = { 0.8f, 0.7f, 0.2f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 0.9f, 0.5f, 1.0f };


const GLfloat mat_diffuse1[]    = { 0.6f, 0.2f, 0.8f, 1.0f };
const GLfloat mat_specular1[]   = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat mat_diffuse2[]    = { 0.6f, 0.2f, 0.2f, 1.0f };
const GLfloat mat_specular2[]   = { 1.0f, 0.5f, 1.0f, 1.0f };

const GLfloat mat_diffuse3[]    = { 0.3f, 0.2f, 0.6f, 1.0f };
const GLfloat mat_specular3[]   = { 0.4f, 0.8f, 0.3f, 1.0f };

const GLfloat spec[]    = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat mat_diffuse4[]    = { 0.3f, 0.9f, 0.9f, 1.0f };
const GLfloat mat_specular4[]   = { 0.4f, 0.3f, 0.3f, 1.0f };
int wid1, hei1;
double anglee=45;
float gar;

int Depth=1;


void drawkoch(GLfloat newy,GLfloat oldy,GLfloat oldx,GLfloat newx,GLint iter)
{

    GLfloat cox[4]= {oldx,oldx+((newx-oldx)/3.0),oldx+((newx-oldx)*2/3.0),newx}, coy[4]= {newy,newy+((oldy-newy)/3.0),newy+((oldy-newy)*2/3.0),oldy};

    if (iter == 0)
    {
        glVertex3d(oldx,newy,0.2);
        glVertex3d(oldx,oldy,.2);
        glVertex3d(newx,oldy,.2);
        glVertex3d(newx,newy,.2);
        return;
    }


    else if(iter>0)
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(i!=1||j!=1)
                {
                    drawkoch(coy[i],coy[i+1],cox[j],cox[j+1],iter-1);
                }

            }
        }
    }
}

void KochCurve(int iter)
{

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient4);

    glBegin(GL_QUADS);
    glVertex3f(0,0, 0);
    glVertex3f(1,0, 0);
    glVertex3f(1,1, 0);
    glVertex3f(0,1, 0);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   no_light);


    glBegin(GL_QUADS);
    drawkoch(.95,.05,.95,.05,iter);
    glEnd();
}

static void resize(int width, int height)
{
    wid1=width;
    hei1=height;
    const float ar = (float) width / (float) height;
    gar=ar;

}
void spin()
{
    tt +=8;
    glutPostRedisplay();
}
void cubeTex()
{
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2d(0,0);
    glVertex3f(1.0,0.0,0.0);
    glTexCoord2d(1,0);
    glVertex3f(1.0,1,0.0);
    glTexCoord2d(1,1);
    glVertex3f(0.0,1,0.0);
    glTexCoord2d(0,1);

    glEnd();
}
void dCubeTex()
{
    glPushMatrix();
    cubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,0,0);
    glRotated(90,0,1,0);
    cubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,0,-1);
    glRotated(180,0,1,0);
    cubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,-1);
    glRotated(-90,0,1,0);
    cubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,-1);
    glRotated(90,1,0,0);
    cubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1,0);
    glRotated(-90,1,0,0);
    cubeTex();
    glPopMatrix();
}
void drawCube()
{
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1,0.0);
    glVertex3f(1.0,1,0.0);
    glVertex3f(1.0,0.0,0.0);

    glVertex3f(0.0,1,1.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,1,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1,1.0);
    glVertex3f(0.0,1,0.0);

    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,1,0.0);
    glVertex3f(1.0,1,1.0);
    glVertex3f(1.0,0.0,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(0.0,0.0,1.0);

    glVertex3f(0.0,1,0.0);
    glVertex3f(0.0,1,1.0);
    glVertex3f(1.0,1,1.0);
    glVertex3f(1.0,1,0.0);

    glEnd();
}
void drawPolygon1()
{
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,1.6,1.1);
    glVertex3f(5.0,1.6,1.1);
    glVertex3f(5,5,1.1);
    glVertex3f(4,5,1.1);
    glVertex3f(-0.5,2.5,1.1);
    glEnd();

}

void drawPolygon2()
{
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,1.6,-2.9);
    glVertex3f(-0.5,2.5,-2.9);
    glVertex3f(4,5,-2.9);
    glVertex3f(5,5,-2.9);
    glVertex3f(5.0,1.6,-2.9);

    glEnd();
}

void drawsemiCircle()
{
    float x1,y1,x2,y2;
    float angle;
    double radius=0.5;

    x1 = 0.0,y1=0.0;
    glVertex3f(x1,y1,0.0);

    glBegin(GL_TRIANGLE_FAN);
    for (angle=180.0f; angle>0.0f; angle-=0.2)
    {
        x2 = x1+sin(angle*DEG2RAD)*radius;
        y2 = y1+cos(angle*DEG2RAD)*radius;
        glVertex3f(x2,y2,0.0);
    }

    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (angle=0.0f; angle<=180.0f; angle+=0.2)
    {
        x2 = x1+sin(angle*DEG2RAD)*radius;
        y2 = y1+cos(angle*DEG2RAD)*radius;
        glVertex3f(x2,y2,0.0);
        glVertex3f(x2,y2,.3);
    }

    glEnd();
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(2.5,1,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,0);
    glVertex3f(2.5,1,0);
    glVertex3f(0,1,0);
    glEnd();


}
void drawCylinder()
{

    float x1,y1,x2,y2;
    float angle;
    double radius=0.5;

    x1 =0.0,y1=0.0;
    glVertex3f(x1,y1,0.0);

    glPushMatrix();
    glRotated(-90,1,0,0);
    glBegin(GL_POLYGON);
    for (angle=360.0f; angle>0.0f; angle-=0.2)
    {
        x2 = x1+sin(angle*DEG2RAD)*radius;
        y2 = y1+cos(angle*DEG2RAD)*radius;
        glVertex3f(x2,y2,0.0);
        glVertex3f(x2,y2,1.0);
    }

    glEnd();

    glBegin(GL_POLYGON);
    for (angle=360.0f; angle>0.0f; angle-=0.2)
    {
        x2 = x1+sin(angle*DEG2RAD)*radius;
        y2 = y1+cos(angle*DEG2RAD)*radius;
        glVertex3f(x2,y2,1.0);
        glVertex3f(x2,y2,0.0);
    }

    glEnd();
    glPopMatrix();


}
void pyBat()
{
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(2.5,0.0,0.0);
    glVertex3f(2.5,10,0.0);
    glVertex3f(0.0,10,0.0);

    glVertex3f(0.0,10,1.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(2.5,0.0,1.0);
    glVertex3f(2.5,10,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,10,1.0);
    glVertex3f(0.0,10,0.0);

    glVertex3f(2.5,0.0,0.0);
    glVertex3f(2.5,10,0.0);
    glVertex3f(2.5,10,1.0);
    glVertex3f(2.5,0.0,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(2.5,0.0,0.0);
    glVertex3f(2.5,0.0,1.0);
    glVertex3f(0.0,0.0,1.0);

    glVertex3f(0.0,10,0.0);
    glVertex3f(0.0,10,1.0);
    glVertex3f(2.5,10,1.0);
    glVertex3f(2.5,10,0.0);

    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(2.5,0.0,1.0);
    glVertex3f(1.25,3.0,2.0);

    glVertex3f(2.5,10,1.0);
    glVertex3f(0.0,10,1.0);
    glVertex3f(1.25,3.0,2.0);

    glVertex3f(0.0,10,1.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(1.25,3.0,2.0);

    glVertex3f(2.5,0.0,1.0);
    glVertex3f(2.5,10,1.0);
    glVertex3f(1.25,3.0,2.0);

    glEnd();

    glPushMatrix();
    glTranslated(1.25,10,.5);
    glScaled(1,5,1);
    drawCylinder();
    glPopMatrix();


}
void drawLeg()
{
    glPushMatrix();
    //glColor3f(1.0,0.25,0.75);
    glScaled(4,0.1,2);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.75,0.75);
    glScaled(2,1.5,0.1);
    glTranslated(0.5,0.067,10);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.25,0.75);
    glScaled(4,0.1,2);
    glTranslated(0,0,-2);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.75,0.75);
    glScaled(2,1.5,0.1);
    glTranslated(0.5,0.067,-30);
    drawCube();
    glPopMatrix();

}
void drawbody()
{
    glPushMatrix();
    //glColor3f(1.0,0.25,0.55);
    drawPolygon1();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.25,0.95);
    glTranslated(0,0,-4);
    drawPolygon1();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.25,0.55);
    drawPolygon2();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.25,0.95);
    glTranslated(0,0,4);
    drawPolygon2();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(-0.5,1.6,-2.9);
    glScaled(0.1,1,4);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.3,0.55,0.55);
    glTranslated(-0.5,2.6,-2.9);
    glRotated(-61,0,0,1);
    glScaled(0.1,2.5,4);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.3,0.55,0.55);
    glTranslated(2.8,4.3,-2.92);
    glRotated(-61,0,0,1);
    glScaled(0.1,1.4,4);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(4,5,-2.9);
    glRotated(-90,0,0,1);
    glScaled(0.1,1,4);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(5,1.6,-2.9);
    glRotated(-90,0,1,0);
    glScaled(4,3.3,0.1);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(-0.5,1.6,-2.9);
    glScaled(5.5,0.1,4);
    drawCube();
    glPopMatrix();

}
void drawWing()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    // //glColor3f(0.1,0.55,0.75);
    glScaled(0.001,1,5);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //  //glColor3f(0.1,0.55,0.75);
    glTranslated(0,0.5,0);
    glRotated(90,0,1,0);
    glScaled(1,1,0.1);
    drawsemiCircle();
    glPopMatrix();

    glPushMatrix();
    //  //glColor3f(0.1,0.55,0.75);
    glTranslated(0,0.5,5);
    glRotated(-90,0,1,0);
    glScaled(1,1,0.1);
    drawsemiCircle();
    glPopMatrix();
    glPopMatrix();

}

void drawWing2()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    //glColor3f(0.1,0.55,0.75);
    glScaled(.3,1,5);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.1,0.55,0.75);
    glTranslated(0,0.5,0);
    glRotated(90,0,1,0);
    drawsemiCircle();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.1,0.55,0.75);
    glTranslated(0.3,0.5,5);
    glRotated(-90,0,1,0);
    drawsemiCircle();
    glPopMatrix();
    glPopMatrix();

}
void drawBackPropeller()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    //glColor3f(.43,.67,.09);
    glTranslated(13.8,6.4,-1);
    glScaled(.2,1.1,.2);
    drawCylinder();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.403,.67,.09);
    glTranslated(11.0,7.5,-1.5);
    glRotated(-90,0,0,1);
    glRotated(-90,0,1,0);
    glRotated(-90,1,0,0);
    glRotated(-90,0,0,1);
    drawWing();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.043,.67,.09);
    glTranslated(13.3,7.5,-3.5);
    glRotated(-90,0,0,1);
    drawWing();
    glPopMatrix();
    glPopMatrix();
}

void drawback()
{
    glPushMatrix();
    //glColor3f(0.89,0.55,0.75);
    glTranslated(10,3,-.5);
    glRotated(-90,0,1,0);
    glScaled(0.1,1,6);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(10,3,-1.6);
    glRotated(-90,0,1,0);
    glScaled(0.1,1,6);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(10,3,-1.6);
    glScaled(0.1,1,1.1);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(10,3,-1.5);
    glRotated(-90,0,1,0);
    glRotated(-90,0,0,1);
    glScaled(0.1,1,6);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(10,4,-1.5);
    glRotated(-90,0,1,0);
    glRotated(-90,0,0,1);
    glScaled(0.1,1,6);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.7,0.55,0.75);
    glTranslated(9.9,4,-1.2);
    glRotated(-90,1,0,0);
    glRotated(-90,0,0,1);
    glRotated(-45,1,0,0);
    drawWing2();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.4,0.75,0.75);
    glTranslated(5,2,-0.5);
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.4,0.75,0.75);
    glTranslated(5,2,-1.5);
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-.5,0,0);
    glTranslated(13.8,6.4,-1);
    glRotated(-90,0,0,1);
    glRotated(90,1,0,0);
    glRotated(tt,0,1,0);
    glScaled(.5,.5,.5);
    glTranslated(-13.8,-6.4,1);
    drawBackPropeller();
    glPopMatrix();
}

void drawUpper()
{
    glPushMatrix();
    //glColor3f(0.8,0.9,0.2);
    glTranslated(4.1,5,-1);
    glScaled(.2,1.1,.2);
    drawCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.7,6.1,-1.5);
    glRotated(-90,0,0,1);
    glRotated(-90,0,1,0);
    glRotated(-90,1,0,0);
    glRotated(-90,0,0,1);
    drawWing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.5,6.2,-3.5);
    glRotated(-90,0,0,1);
    drawWing();
    glPopMatrix();

}
void drawTable(int flag)
{
    if(flag==1)
    {
        //glPushMatrix();
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-2,-.5,-5);
        glRotated(90,1,0,0);
        glScalef(26,10,.4);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-1.5,-14.3,4);
        glScalef(1,14,1);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-1.5,-14.3,-3);
        glScalef(1,14,1);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(22.5,-14.3,4);
        glScalef(1,14,1);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(22.5,-14.3,-3);
        glScalef(1,14,1);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient4);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse4);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular4);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glPushMatrix();
        glTranslated(-2,-.4,-5);
        glScalef(26,.4,10);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-2,-14.3,3);
        glScalef(1,14,1);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-2,-14.3,-4.1);
        glScalef(1,14,1);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(23,-14.3,3);
        glScalef(1,14,1);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(23,-14.3,-4.1);
        glScalef(1,14,1);
        drawCube();
        glPopMatrix();
        glPopMatrix();
    }
}
void drawWindowWall(int flag)
{
    glPushMatrix();
    if(flag==0)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular1);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);

        glPushMatrix();
        glTranslated(37,-14.31,-10);
        glRotated(180,0,1,0);
        glScalef(47,15,2);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(2,0.31,-10);
        glRotated(180,0,1,0);
        glScalef(12,20,2);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(37,0.31,-10);
        glRotated(180,0,1,0);
        glScalef(12,20,2);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(25,15.31,-10);
        glRotated(180,0,1,0);
        glScalef(23,5,2);
        drawCube();
        glPopMatrix();

        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslated(37,-14.31,-10);
        glRotated(180,0,1,0);
        glScalef(47,15,2);
        dCubeTex();
        glPopMatrix();

        glPushMatrix();
        glTranslated(2,0.31,-10);
        glRotated(180,0,1,0);
        glScalef(12,20,2);
        dCubeTex();
        glPopMatrix();

        glPushMatrix();
        glTranslated(37,0.31,-10);
        glRotated(180,0,1,0);
        glScalef(12,20,2);
        dCubeTex();
        glPopMatrix();

        glPushMatrix();
        glTranslated(25,15.31,-10);
        glRotated(180,0,1,0);
        glScalef(23,5,2);
        dCubeTex();
        glPopMatrix();

        glPopMatrix();
    }
}
void drawWalls(int flag)
{
    if(flag==1)
    {
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-10,-14.5,-8);
        glRotated(-90,0,1,0);
        glScalef(23,35,2);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(35,-14.5,-8);
        glRotated(-90,0,1,0);
        glScalef(23,35,2);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        drawWindowWall(1);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,6);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-8,-12.5,-8);
        glRotated(-90,0,1,0);
        glRotated(-90,1,0,0);
        glScalef(23,43,2);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        //ceiling
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-10,22.5,-10);
        glRotated(-90,0,1,0);
        glRotated(-90,1,0,0);
        glScalef(25,47,2);
        dCubeTex();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

    }
    if(flag==0)
    {
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glTranslated(-8,-14.31,-10);
        glScalef(2,35,25);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslated(2,0,0);
        glScaled(0.95,1,1);
        drawWindowWall(0);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glTranslated(-8,-14.31,-12);
        glRotated(-90,0,0,1);
        glScalef(2,45,27);
        drawCube();
        glPopMatrix();
    }
}
void jack()
{
    glPushMatrix();
    glTranslated(-2.4,3.2,-6);
    glScalef(.6,3.5,.6);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-2.4,6.8,-6);
    glScalef(.5,.5,.5);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-2.4,-.4,-6);
    glScalef(.5,.5,.5);
    glutSolidSphere(1,slices,stacks);
    glNormal3f(0,0,1);
    glPopMatrix();
}
void drawJack()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    glTranslated(0,4.1,2.5);
    glRotated(-45,1,0,0);
    jack();
    glPopMatrix();
    glPushMatrix();
    glTranslated(.5,-4.4,-5.1);
    glRotated(60,0,1,0);
    glRotated(45,1,0,0);
    jack();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2,4.1,-9.5);
    glRotated(120,0,1,0);
    glRotated(-45,1,0,0);
    jack();
    glPopMatrix();
    glPopMatrix();
}
void drawFrame()
{
    glPushMatrix();
    //glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-27.5,1,7);
    //glRotated(-15,0,1,0);
    glRotated(90,0,1,0);
    glScalef(11,15,0);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glBindTexture(GL_TEXTURE_2D,8);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(-27.5,-1,9);
//    //glRotated(-15,0,1,0);
    glRotated(90,0,1,0);
    glScalef(2,17,1);
    dCubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-27.5,1,-4);
//    //glRotated(-15,0,1,0);
    glRotated(90,0,1,0);
    glScalef(2,17,1);
    dCubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-27.5,1,7);
    glRotated(90,0,1,0);
    glRotated(-90,0,0,1);
    glScalef(2,13,1);
    dCubeTex();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-27.5,18,9);
    glRotated(90,0,1,0);
    glRotated(-90,0,0,1);
    glScalef(2,13,1);
    dCubeTex();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void drawScene()
{
    glPushMatrix();
    // glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
    glBindTexture(GL_TEXTURE_2D,5);
    glEnable(GL_TEXTURE_2D);
    //glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glTranslated(-45,-20,-50);
    glScalef(160,60,1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPushMatrix();
    // glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);
    //glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glTranslated(-45,-21,-51);
    glRotated(90,1,0,0);
    glScalef(160,90,1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void drawLights()
{

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_green);
    glTranslated(30,18,-1);
    glScalef(1,1,1);
    glutSolidSphere(1,slices,stacks);
    glNormal3f(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
    glTranslated(12,18,-6);
    // glTranslated(11,18,-25);
    glScalef(1,1,1);
    glutSolidSphere(1,slices,stacks);
    glNormal3f(0,0,1);
    glPopMatrix();
}
void drawBasket()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(3,-12.2,10);
    glRotated(-90,1,0,0);
    glScaled(5,5,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(3,-5.2,10);
    glRotated(-90,1,0,0);
    glScaled(5,5,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(3,-12.2,10);
    glScaled(5,7,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(8,-12.2,10);
    glRotated(90,0,1,0);
    glScaled(5,7,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(8,-12.2,5);
    glRotated(180,0,1,0);
    glScaled(5,7,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,9);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_red);
    glTranslated(3,-12.2,10);
    glRotated(90,0,1,0);
    glScaled(5,7,.1);
    dCubeTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void clock()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
    glTranslated(26,11,-8);
    glScaled(8,8,1);
    drawCube();

    glPopMatrix();
}
void drawHeli(int flag)
{

    glPushMatrix();
    glRotated(15,0,1,0);
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glRotated(-15,0,1,0);
    drawLeg();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    drawbody();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    drawback();
    glTranslated(4.1,5,-1);
    glRotated(tt,0,1,0);
    glTranslated(-4.1,-5,1);
    drawUpper();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glRotated(-15,0,1,0);
    if(flag==0)
    {
        drawTable(0);
        drawWalls(0);
    }
    else
    {
        drawTable(1);
        drawWalls(1);
    }
    glTranslated(20,.9,6);
    glRotated(-20,0,1,0);
    drawJack();
    //glNormal3f(0,0,1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(20,0,0);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   spec);
    if(flag==1)
    {
        drawFrame();
    }
    glPopMatrix();
    if(flag==1)
    {
        glPushMatrix();
        glTranslated(0,6,0);
        drawScene();
        glPopMatrix();
    }
    glPushMatrix();
    drawLights();
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_CULL_FACE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   spec);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   no_light);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   no_light);
    // gluOrtho2D(-gar,gar,-1.0,1.0);
    glTranslated(-6,-12.3,-7);
    glRotated(-90,0,1,0);
    glRotated(180,1,0,0);
    glRotated(90,1,0,0);
    glScalef(22,40,1);
    KochCurve(Depth);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_CULL_FACE);
    glTranslated(-12,0,-1);
    drawBasket();
    glPushMatrix();
    glDisable(GL_CULL_FACE);
    glTranslated(5,-12.35,11.25);
    glRotated(-10,1,0,0);
    glScaled(.8,1,.8);
    pyBat();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_red);
    glBindTexture(GL_TEXTURE_2D, 11);
    glEnable(GL_TEXTURE_2D);
    glTranslated(10,-11.35,11);
    glScalef(1,1,1);
    gluQuadricTexture(gluNewQuadric(), GL_TRUE);
    gluSphere(gluNewQuadric(), 1, slices, stacks);
    gluDeleteQuadric(gluNewQuadric());
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);
    clock();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPopMatrix();


}
float app=50;
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glViewport(0, 0, wid1, hei1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3d(1,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glFrustum(-gar, gar, -1.0, 1.0, ne, fa);
    gluPerspective((float) app, gar, ne, fa);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //  gluLookAt(ex,ey,ez,ex+cos(xx*DEG2RAD),cy,cz,ux,uy,uz); //yaw
    //  gluLookAt(ex,ey,ez,cx,ey+sin(xx*DEG2RAD),cz,ux,uy,uz); //pitch
    //  gluLookAt(ex,ey,ez,cx,cy,cz,cos(yy*DEG2RAD),sin(yy*DEG2RAD),uz); //roll
    gluLookAt(ex,ey,ez,cx,cy,cz,ux,uy,uz);
//utiu
//    glPushMatrix();
//    // glTranslated(2,-6,-15);
//    glViewport(0, 0, wid1/2, hei1-200);
//    glTranslated(tx,ty,tz);
//    glRotatef(angle, 0, 0, 1);
//    glRotated(degree,1,0,0);
//    glRotated(degree1,0,1,0);
//    glRotated(degree2,0,0,1);
//    glScalef(scale,scale,scale);
//
//    drawHeli(0);
//    glPopMatrix();
    // drawCube();

    glPushMatrix();
    //glViewport(wid1/2, 0, wid1/2, hei1-200);
    glTranslated(tx,ty,tz);
    glRotatef(angle, 0, 0, 1);
    glRotated(degree,1,0,0);
    glRotated(degree1,0,1,0);
    glRotated(degree2,0,0,1);
    glScalef(scale,scale,scale);

    drawHeli(1);

    glPopMatrix();

    glutSwapBuffers();

}
static void idle(void)
{
    glutPostRedisplay();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':   //anti-clockwise x-rotate
        degree+=2.5;
        break;
    case 'X':   //clockwise x-rotate
        degree-=2.5;
        break;
    case 'y':   //anti-clockwise y-rotate
        degree1+=2.5;
        break;
    case 'Y':   //clockwise y-rotate
        degree1-=2.5;
        break;
    case 'z':   //anti-clockwise z-rotate
        degree2+=2.5;
        break;
    case 'Z':   //clockwise z-rotate
        degree2-=2.5;
        break;
    case '1':
        tx+=0.5;
        break;
    case '2':
        tx-=0.5;
        break;
    case '3':
        ty+=0.5;
        break;
    case '4':
        ty-=0.5;
        break;
    case '5':
        tz+=0.5;
        break;
    case '6':
        tz-=0.5;
        break;
    case 's':
        scale+=0.1;
        break;
    case 'S':
        scale-=0.1;
        break;
    case '`':
        tt=0;
        glutIdleFunc(idle);
        break;
    case '~':
        glutIdleFunc(spin);
        break;
    case 'q':
        cx=0;
        cy=0;
        cz=-2;
        ex=0;
        ey=0;
        ez=8;
        ux=0;
        uy=1;
        uz=0;
        break;
    case 'W': //yaw
        fgg=1;
        if(fgg=0)
        {
            cz=-2;
            cy=0;
        }
        xx+=5;
        cx=cos(xx*DEG2RAD)+sin(xx*DEG2RAD);
        cz=-sin(xx*DEG2RAD)+cos(xx*DEG2RAD);
        break;
    case 'P': //pitch
        fgg=0;
        if(fgg=1)
        {
            cy=0;
            cz=-2;
        }
        xz+=5;
        cy=cos(xz*DEG2RAD)-sin(xz*DEG2RAD);
        cz=sin(xz*DEG2RAD)+cos(xz*DEG2RAD);
        break;
    case 'L': //roll
        yy+=5;
        ux=cos(yy*DEG2RAD)-sin(yy*DEG2RAD);
        uy=sin(yy*DEG2RAD)+cos(yy*DEG2RAD);;
        break;
    case 'v': //zoom-in
        rs-=.5;
        ez=rs*cos(yz*DEG2RAD);
        break;
    case 'V': //zoom-out
        rs+=.5;
        ez=rs*cos(yz*DEG2RAD);
        break;
    case 'c': //circular
        zz-=.1;
        ez=rr*sin(zz);
        ex=rr*cos(zz);
        break;

    //class
    case 'e':
        ex+=0.5;
        break;
    case 'E':
        ex-=0.5;
        break;
    case 'r':
        ey+=0.5;
        break;
    case 'R':
        ey-=0.5;
        break;
    case 't':
        ez+=0.5;
        break;
    case 'T':
        ez-=0.5;
        break;
    case 'a':
        cx+=0.05;
        break;
    case 'A':
        cx-=0.05;
        break;
    case 'b':
        cy+=0.05;
        break;
    case 'B':
        cy-=0.05;
        break;
    case 'f':
        cz+=0.05;
        break;
    case 'F':
        cz-=0.05;
        break;
    case 'u':
        ux+=0.05;
        break;
    case 'U':
        ux-=0.05;
        break;
    case 'h':
        uy+=0.05;
        break;
    case 'H':
        uy-=0.05;
        break;
    case 'n':
        uz+=0.05;
        break;
    case 'N':
        uz-=0.05;
        break;
    case '[':
        glEnable(GL_LIGHT0);

        break;
    case ']':
        glDisable(GL_LIGHT0);
        break;
    case '%':
        glEnable(GL_LIGHT1);
        break;
    case '^':
        glDisable(GL_LIGHT1);
        break;
    case '&':
        glEnable(GL_LIGHT2);
        break;
    case '*':
        glDisable(GL_LIGHT2);
        break;
    case '.':
        high_shininess-=5.0;
        break;
    case ',':
        high_shininess+=5.0;
        break;
//    case '<':
//        ne++;
//        resize(wid1,hei1);
//        break;
//    case '>':
//        ne--;
//        resize(wid1,hei1);
//        break;
    case 'd':
        if(Depth<=5)
            Depth++;
        break;
    case 'D':
        if(Depth>=1)
            Depth--;
        break;
    case 'o':
        app+=.5;
        ez+=.5;
        gluPerspective((float) app, gar, ne, fa);
        break;
    case 'O':
        ez-=.5;
        app-=.5;
        gluPerspective((float) app, gar, ne, fa);
        break;
    case 'K':   //walk
        if(wk==0)
        {
            ez=35;
            ex=-40;
            cz=-1;
            cx=0;
            wk=1;
        }

        ez-=.5;
        break;
    case 'k':   //reverse-walk
        ex=-40;
        ez+=.5;
        break;
    }

    glutPostRedisplay();
}

/* Program entry point */
void Init()
{

    pix[0].makeCheckImage();
    pix[0].setTexture(1);

    pix[1].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\brickk.bmp");
    pix[1].setTexture(2);

    pix[2].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\wood.bmp");
    pix[2].setTexture(3);

    pix[3].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\monaa.bmp");
    pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\naturee.bmp");
    pix[4].setTexture(5);

    pix[5].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\floor.bmp");
    pix[5].setTexture(6);

    pix[6].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\field.bmp");
    pix[6].setTexture(7);

    pix[7].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\wood2.bmp");
    pix[7].setTexture(8);

    pix[8].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\bsk.bmp");
    pix[8].setTexture(9);

    pix[9].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\clock.bmp");
    pix[9].setTexture(10);

    pix[10].readBMPFile("C:\\Users\\hp\\Desktop\\labHW\\ball.bmp");
    pix[10].setTexture(11);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1100,650);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spin);
    //glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
    // glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 3.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0);

    Init();
    //keys
    cout<<"Press following keys for-----\n"<<"Rotation:"<<endl;
    cout<<"x-axis (counter-clockwise): x\n"<<"x-axis (clockwise): X"<<endl;
    cout<<"y-axis (counter-clockwise): y\n"<<"y-axis (clockwise): Y"<<endl;
    cout<<"z-axis (counter-clockwise): z\n"<<"z-axis (clockwise): Z\n"<<endl;
    cout<<"Translation:"<<endl;
    cout<<"left(-x): press 2, right(+x): press 1\n"<<"up(+y): press 3, down(-y): press 4\n"<<"near(+z): press 5, far(-z): press 6\n"<<endl;
    cout<<"Zoom-in with scaling: Press s for zooming in and S for zooming out\n"<<endl;
    cout<<"Camera zoom-in: press v, zoom-out: press V\n"<<endl;
    cout<<"Roll: L, Yaw: W, Pitch: P\n"<<endl;
    cout<<"Camera circular motion: press c\n"<<endl;
    cout<<"Light0-- on: [ , off: ]\nLight1-- on: % , off: ^\nSpotlight-- on: & , off: *\n"<<endl;
    cout<<"Sierpinski pattern dynamic depth (depth= 2 to 5): press d for depth++ and D for depth--\n"<<endl;
    cout<<"Window aperture adjust: press O for closer and o for farther\n"<<endl;
    cout<<"Walking---\nWalk beside the scene: press K\nWalk backwards: press k\nGo back to initial camera position: press q\n"<<endl;



    glutMainLoop();

    return EXIT_SUCCESS;
}
