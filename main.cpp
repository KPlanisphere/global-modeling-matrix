#include "3D_bib.h"
#include "Stage.h"
#include <GL/glut.h>

//Variables dimensiones de la pantalla
int WIDTH=500;
int HEIGTH=500;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=100.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=1.0;
float EYE_Y=5.0;
float EYE_Z=15.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Variables para dibujar los ejes del sistema
float X_MIN=-20;
float X_MAX=20;
float Y_MIN=-20;
float Y_MAX=20;
float Z_MIN=-100;
float Z_MAX=20;

//Se declara el objeto para utilizar las operaciones 3D
Operaciones3D Op3D;
Stage S(&Op3D);

float Theta1=0,sx1 = 1,sy1 = 1,sz1 = 1, tx1 = 0,ty1 = 0,tz1 = 0;
float Theta2=0,sx2 = 1,sy2 = 1,sz2 = 1, tx2 = 0,ty2 = 0,tz2 = 0;
float Theta3=0,sx3 = 1,sy3 = 1,sz3 = 1, tx3 = 0,ty3 = 0,tz3 = 0;
//Variables para la definicion de objetos
float P1[3]={0.0,0.0,5.0};
float P2[3]={0.0,5.0,0.0};
//float points[5][3]={{0,0,1},{1,0,1},{1,0,0},{0,0,0},{0.5,0.75,0.5}};
float points[8][3]= {{0,0,1},{1,0,1},{1,0,0},{0,0,0},
                     {0,1,1},{1,1,1},{1,1,0},{0,1,0}};
float points2[8][3]={{0,0,1},{1,0,1},{1,0,0},{0,0,0},
                     {0,1,1},{1,1,1},{1,1,0},{0,1,0}};
float points3[8][3]={{0,0,1},{1,0,1},{1,0,0},{0,0,0},
                     {0,1,1},{1,1,1},{1,1,0},{0,1,0}};



//Dibujar ejes
void drawAxis()
{
     glShadeModel(GL_SMOOTH);
     glLineWidth(1.0);
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(0.5f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,0.5f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,0.5f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
     glLineWidth(1.0);
 }

//-------------------------------------------------------------------------
//funciones callbacks
void idle(void)
{
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}




static void keys(unsigned char key, int x, int y)
{
    switch(key){
        ///OBJETO 1
        case '1': // ---> ROTAR +
            Theta1=10;  sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '2': // ---> ROTAR -
            Theta1=-10; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '3': // ---> ESCALAR +
            Theta1 = 0; sx1 = 1.1;  sy1 = 1.1;  sz1 = 1.1,  tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '4': // ---> ESCALAR -
            Theta1 = 0; sx1 = 0.9;  sy1 = 0.9;  sz1 = 0.9,  tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '5': // ---> TRASLACIÓN X
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0.1,  ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '6': // ---> TRASLACIÓN Y
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0.1,  tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case '7': // ---> TRASLACIÓN Z
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = -0.1;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        ///OBJETO 2
        case 'q': // ---> ROTAR +
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 =10; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'w': // ---> ROTAR -
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 =-10; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'e': // ---> ESCALAR +
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1.1;  sy2 = 1.1;  sz2 = 1.1,  tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'r': // ---> ESCALAR -
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 0.9;  sy2 = 0.9;  sz2 = 0.9,  tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 't': // ---> TRASLACIÓN X
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0.1,  ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'y': // ---> TRASLACIÓN Y
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0.1,  tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'u': // ---> TRASLACIÓN Z
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0.1;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        ///OBJETO 3
        case 'a': // ---> ROTAR +
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 =10; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 's': // ---> ROTAR -
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 =-10;sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'd': // ---> ESCALAR +
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1.1;  sy3 = 1.1;  sz3 = 1.1,  tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'f': // ---> ESCALAR -
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 0.9;  sy3 = 0.9;  sz3 = 0.9,  tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
        case 'g': // ---> TRASLACIÓN X
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0.1,  ty3 = 0,    tz3 = 0;
            break;
        case 'h': // ---> TRASLACIÓN Y
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0.1,  tz3 = 0;
            break;
        case 'j': // ---> TRASLACIÓN Z
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0.1;
            break;
        default:
            Theta1 = 0; sx1 = 1;    sy1 = 1;    sz1 = 1,    tx1 = 0,    ty1 = 0,    tz1 = 0;
            Theta2 = 0; sx2 = 1;    sy2 = 1;    sz2 = 1,    tx2 = 0,    ty2 = 0,    tz2 = 0;
            Theta3 = 0; sx3 = 1;    sy3 = 1;    sz3 = 1,    tx3 = 0,    ty3 = 0,    tz3 = 0;
            break;
    }
    glutPostRedisplay();
}
//--------------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //drawAxis();
    glColor3f(1.0f,1.0f,1.0f);
    //se rota la piramide Theta grados con respecto al eje de rotacion
    //a una distancia definida por el usuario
    ///S.RotacionPiramide('Y',Theta,0,0);
    ///S.RotacionPiramide(Theta,P1,P2);
    ///S.ImprimePiramide();
    S.ShowStage();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);
    ///RESET DE VALORES
    Theta1=0;Theta2=0; Theta3=0;

    sx1 = 1; sy1 = 1; sz1 = 1;
    sx2 = 1; sy2 = 1; sz2 = 1;
    sx3 = 1; sy3 = 1; sz3 = 1;

    tx1 = 0,ty1 = 0,tz1 = 0;
    tx2 = 0,ty2 = 0,tz2 = 0;
    tx3 = 0,ty3 = 0,tz3 = 0;

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Matriz de Modelado Global | Jesus Huerta Aguilar");
    init();
    //Op3D.LoadIdentity(Op3D.A);
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

