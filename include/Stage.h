#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "3D_bib.h"

#ifndef STAGE_H
#define STAGE_H

class Stage
{
    public:
        Stage(Operaciones3D *);
        ~Stage();
        void ShowStage();


    private:
        Operaciones3D *Op3D;
};

#endif // STAGE_H
