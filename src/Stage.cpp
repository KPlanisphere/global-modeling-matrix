#include "Stage.h"
#include "Piramide.h"

extern float P1[3];
extern float P2[3];
extern float points[8][3];
extern float points2[8][3];
extern float points3[8][3];
extern float Theta1,sx1,sy1,sz1,tx1,ty1,tz1;
extern float Theta2,sx2,sy2,sz2,tx2,ty2,tz2;
extern float Theta3,sx3,sy3,sz3,tx3,ty3,tz3;
extern Operaciones3D Op3D;

Piramide Cubo(&Op3D),Cubo2(&Op3D),Cubo3(&Op3D);

Stage::Stage(Operaciones3D *data)
{
    Op3D = data;
}

Stage::~Stage()
{
    //dtor
}

void Stage::ShowStage(){

    Op3D->Push(Op3D->A);
    ///CUBO N°1
    ///COLOR: ROJO
    glColor3f(1,0,0);

    Op3D->RotacionParalela('Y',Theta1,0,0);

    Op3D->translate(tx1,ty1,tz1);
    Op3D->MultM(Op3D->A,Op3D->T,Op3D->A);

    Op3D->Escalado(sx1,sy1,sz1);
    Op3D->MultM(Op3D->A,Op3D->E,Op3D->A);

    Op3D->MatObject(Op3D->A,8,points);
    Cubo.ImprimePiramide(points);

    //Op3D->Push(Op3D->A);
    //Op3D->Pop(Op3D->A);

    ///CUBO N°2
    ///COLOR: VERDE
    glColor3f(0,1,0);
    Op3D->RotacionParalela('Y',Theta2,0,0);

    Op3D->translate(tx2,ty2,tz2);
    Op3D->MultM(Op3D->A,Op3D->T,Op3D->A);

    Op3D->Escalado(sx2,sy2,sz2);
    Op3D->MultM(Op3D->A,Op3D->E,Op3D->A);

    Op3D->MatObject(Op3D->A,8,points2);
    Cubo2.ImprimePiramide(points2);


    ///CUBO N°3
    ///COLOR: AZUL
    glColor3f(0,0,1);

    Op3D->RotacionParalela('Y',Theta3,0,0);

    Op3D->translate(tx3,ty3,tz3);
    Op3D->MultM(Op3D->A,Op3D->T,Op3D->A);

    Op3D->Escalado(sx3,sy3,sz3);
    Op3D->MultM(Op3D->A,Op3D->E,Op3D->A);

    Op3D->MatObject(Op3D->A,8,points3);
    Cubo.ImprimePiramide(points3);

    Op3D->Pop(Op3D->A);

}
