#include "3D_bib.h"
#include <cmath>



#include <iostream>
using namespace std;

Operaciones3D::Operaciones3D()
{
        //Variables para operaciones trigonometricas
        pi = 3.14159265359;
        LoadIdentity(A);
}


//recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
//se aplica la formula r
float Operaciones3D::RadToDeg(float r)
{
      return ((180*r)/pi);
}

float Operaciones3D::DegToRad(float g)
{
      return ((g*pi)/180);
}

void Operaciones3D::LoadIdentity(float M[][4])
{
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(i==j)
         M[i][j]=1;
      else
         M[i][j]=0;
 }

void Operaciones3D::translate(float x, float y, float z)
{
  LoadIdentity(T);
  T[0][3]=x;
  T[1][3]=y;
  T[2][3]=z;
 }

void Operaciones3D::rotateX(float deg)
{
  LoadIdentity(R);
  R[1][1] = cos(deg);
  R[1][2] = -1*sin(deg);
  R[2][1] = sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateY(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][2] = sin(deg);
  R[2][0] = -1*sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateZ(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][1] = -1*sin(deg);
  R[1][0] = sin(deg);
  R[1][1] = cos(deg);
 }

void Operaciones3D::MultM(float M1[][4], float M2[][4], float Res[][4])
{
  float tmp[4][4];
  int i,j,k;
  for(i=0; i<4;i++)
     for(j=0;j<4;j++){
        tmp[i][j]=0;
        for(k=0;k<4;k++)
           tmp[i][j]+=M1[i][k]*M2[k][j];
     }
  for(i=0;i<4;i++)
     for(j=0;j<4;j++)
        Res[i][j] = tmp[i][j];
}

//multiplica la matriz m por el punto p y regresa el resultado en el punto p
void Operaciones3D::MatPoint(float m[][4], float p[3])
{
  float tmp[4];
  int i,j;
  for(i=0; i<3; i++)
    { tmp[i] = p[i];
      p[i] = 0;
    }
  tmp[3]=1;
  for(i=0;i<3;i++)
    for(j=0;j<4;j++)
        p[i] += m[i][j]*tmp[j];
}

//multiplica la matriz m por cada punto del objeto definido por la matriz p de size x 3
void Operaciones3D::MatObject(float m[][4], int size, float p[][3])
{
     int i;
     for(i=0; i<size; i++)
       MatPoint(m,p[i]);
}


void Operaciones3D::Escalado(float sx,float sy, float sz)
{
  LoadIdentity(E);
  E[0][0]=sx;
  E[1][1]=sy;
  E[2][2]=sz;
}


void Operaciones3D::EscaladoGeneral(float sx,float sy, float sz,float distA,float distB){
    translate(0,-distA,-distB);
    Escalado(sx,sy,sz);
    MultM(T,E,A);
    translate(0,distA,distB);
    MultM(A,T,A);
}


//rotacion paralela a uno de los ejes
//theta: angulo de rotacion;
//distA,distB: vector (distA,distB) que separa al eje de rotacion del objeto
//con respecto a uno de los ejes del sistema cartesiano. Si el eje es:
//X: (distA,distB) es el vector (0,distA,distB)
//Y: (distA,distB) es el vector (distA,0,distB)
//Z: (distA,distB) es el vector (distA,distB,0)
void Operaciones3D::RotacionParalela(char eje, float theta, float distA, float distB)
{
     switch(eje){
        case 'X'://rotacion paralela en "X"
            translate(0,-distA,-distB);
            rotateX(DegToRad(theta));
            MultM(T,R,A);
            translate(0,distA,distB);
            MultM(A,T,A);
            break;
        case 'Y'://rotacion paralela en "Y"
            translate(-distA,0,-distB);
            MultM(A,T,A);
            rotateY(DegToRad(theta));
            MultM(A,R,A);
            translate(distA,0,distB);
            MultM(A,T,A);
            break;
        case 'Z'://rotacion paralela en "Z"
            translate(-distA,-distB,0);
            rotateZ(DegToRad(theta));
            MultM(T,R,A);
            translate(distA,distB,0);
            MultM(A,T,A);
            break;
     }
}

void Operaciones3D::RotacionLibre(float theta, float p1[3], float p2[3]){
    float V,a,b,c,d;

    /// [1] - CALCULO DEL VECTOR UNITARIO
    //Consideramos el eje Z
    //Calculo |V|
    V = sqrt(pow(p2[0]-p1[0],2) + pow(p2[1]-p1[1],2) + pow(p2[2]-p1[2],2));
    if(V < 0){
        V = -1*V;
    }

    //Calculo de a,b,c
    a = (p2[0]-p1[0]) / V;
    b = (p2[1]-p1[1]) / V;
    c = (p2[2]-p1[2]) / V;
    //Calculo de d (hipotenusa)
    d = sqrt(pow(b,2) + pow(c,2));

    //Caso para el eje X
    if(d == 0){
            translate(-p1[0],-p1[1],-p1[2]);
            rotateX(DegToRad(theta));
            MultM(R,T,A);
            translate(p1[0],p1[1],p1[2]);
            MultM(T,A,A);
    }
    else{// PARA LOS EJES Y y Z
        /// [2] TRASLACION
        translate(-p1[0],-p1[1],-p1[2]);
        //MultM(A,T,A);
        /// [3] CALCULO: RX(ALPHA)
        LoadIdentity(R);
        R[1][1] = c / d;
        R[1][2] = -b / d;
        R[2][1] = b / d;
        R[2][2] = c / d;
        //Primera mult para A
        MultM(T,R,A);

        /// [4] CALCULO: RY(BETA)
        LoadIdentity(R);
        R[0][0] = d;
        R[0][2] = a;
        R[2][0] = -a;
        R[2][2] = d;
        //Segunda mult para A
        MultM(A,R,A);

        /// [5] CALCULO: RZ(THETA)
        LoadIdentity(R);
        R[0][0] = cos(DegToRad(theta));
        R[0][1] = -sin(DegToRad(theta));
        R[1][0] = sin(DegToRad(theta));
        R[1][1] = cos(DegToRad(theta));
        //Tercera mult para A
        MultM(A,R,A);

        /// [6] CALCULO: RY-1(BETA)
        LoadIdentity(R);
        R[0][0] = d;
        R[0][2] = -a;
        R[2][0] = a;
        R[2][2] = d;
        //Cuarta mult para A
        MultM(A,R,A);

        /// [7] CALCULO: RX-1(ALPHA)
        LoadIdentity(R);
        R[1][1] = c / d;
        R[1][2] = b / d;
        R[2][1] = -b / d;
        R[2][2] = c / d;
        //Quinta mult para A
        MultM(A,R,A);

        /// [8] TRASLACION INVERSA
        translate(p1[0],p1[1],p1[2]);
        MultM(A,T,A);
    }
}


///OPERACIONES DE PILA
void Operaciones3D::Push(float mmodel[][4])
{
    Matriz *objM = new Matriz();
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            objM->M[i][j] = mmodel[i][j];
        }
    }
    pila.push(objM);
}

void Operaciones3D::Pop(float mmodel[][4])
{
    Matriz *temp;
    temp = pila.top();
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            mmodel[i][j] = temp->M[i][j];
        }
    }
    delete temp;
    //pila.pop();
}

