#include "Piramide.h"



extern float P1[3];
extern float P2[3];
extern float points[8][3];
extern float points2[8][3];
extern float points3[8][3];
extern float Theta1,sx1,sy1,sz1;
extern float Theta2,sx2,sy2,sz2;
extern float Theta3,sx3,sy3,sz3;



Piramide::Piramide(Operaciones3D *data)
{
    Op3D = data;
}

Piramide::~Piramide()
{
    //dtor
}


/////////////////////////////////////////////////////////////////////////////
//funciones de objetos
/////////////////////////////////////////////////////////////////////////////
float Piramide::Norma(float p1[7], float p2[7])
{
      float n=0;
      int i;
      for(i=0;i<3;i++)
        n += pow(p2[i]-p1[i],2);
      return(sqrt(n));
}

void Piramide::ImprimeMallaPiramide(int k,float pin[][3])
{
     int i,j;
     float U[3],d,norma;
     for(i=0;i<7;i++)
     {
        norma = Norma(pin[i],pin[i+1]);
        d = norma/(float)k;
        U[0] = (pin[i+1][0]-pin[i][0])/norma;
        U[1] = (pin[i+1][1]-pin[i][1])/norma;
        U[2] = (pin[i+1][2]-pin[i][2])/norma;
        for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(pin[i+4][0],pin[i+4][1],pin[i+4][2]);
             glVertex3f(pin[i][0]+U[0]*d*j,pin[i][1]+U[1]*d*j,pin[i][2]+U[2]*d*j);
           glEnd();
        }
     }
     norma = Norma(pin[i],pin[0]);
     d = norma /(float)k;
     U[0] = (pin[0][0]-pin[i][0])/norma;
     U[1] = (pin[0][1]-pin[i][1])/norma;
     U[2] = (pin[0][2]-pin[i][2])/norma;
     for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(pin[i+4][0],pin[i+4][1],pin[i+4][2]);
             glVertex3f(pin[i][0]+U[0]*d*j,pin[i][1]+U[1]*d*j,pin[i][2]+U[2]*d*j);
           glEnd();
        }

}

void Piramide::ImprimePiramide(float pin[][3])
{   int i;

    glBegin(GL_LINE_LOOP);
      for(i=0;i<4;i++)
        glVertex3f(pin[i][0],pin[i][1],pin[i][2]);
    glEnd();


    glBegin(GL_LINE_LOOP);
      for(i=4;i<8;i++)
        glVertex3f(pin[i][0],pin[i][1],pin[i][2]);
    glEnd();


    glBegin(GL_LINES);
      for(i=0;i<4;i++){
        glVertex3f(pin[i+4][0],pin[i+4][1],pin[i+4][2]);
        glVertex3f(pin[i][0],pin[i][1],pin[i][2]);
        }
    glEnd();
    //ImprimeMallaPiramide(20);
    //glColor3f(1,1,1);
 }


//Rotacion paralela
//rota a la piramide theta grados, donde el eje de rotacion se encuentra
//a una distancia distA-distB del eje seleccionado (ejeXYZ)
void Piramide::RotacionPiramide(char ejeXYZ, float theta, float distA, float distB,float pin[][3])
{
     //se prepara la matriz de operaciones A: T^(-1)R(T)
     Op3D->RotacionParalela(ejeXYZ,theta,distA,distB);
     //se aplica A a cada punto de la piramide
     Op3D->MatObject(Op3D->A,5,pin);
}

//Rotacion libre
void Piramide::RotacionPiramide(float theta, float p1[3], float p2[3],float pin[][3])
{
     //se imprime el eje de rotacion
     //glColor3f(1.0,1.0,1.0);
     glBegin(GL_LINES);
       glVertex3f(p1[0],p1[1],p1[2]);
       glVertex3f(p2[0],p2[1],p2[2]);
     glEnd();
    //Se prepara la matriz de operaciones A
    Op3D->RotacionLibre(theta,p1,p2);
    //se aplica A a cada punto de la piramide
    Op3D->MatObject(Op3D->A,5,pin);
}
