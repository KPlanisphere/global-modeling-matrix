#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "3D_bib.h"

#ifndef PIRAMIDE_H
#define PIRAMIDE_H


class Piramide
{
    public:
        Piramide(Operaciones3D *);
        ~Piramide();
        float Norma(float [], float []);
        void ImprimeMallaPiramide(int,float [][3]);
        void ImprimePiramide(float [][3]);
        void RotacionPiramide(char , float, float, float,float [][3]);
        void RotacionPiramide(float , float [], float [],float [][3]);

    private:
        Operaciones3D *Op3D;
};

#endif // PIRAMIDE_H
