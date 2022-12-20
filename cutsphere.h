#ifndef CUTSPHERE_H
#define CUTSPHERE_H
#include "figurageometrica.h"

class CutSphere :
    public FiguraGeometrica
{
    int p_x0, p_y0, p_z0, p_rd;
public:
    CutSphere(int x0, int y0, int z0, int rd);
    void draw(Sculptor& t);
};

#endif // CUTSPHERE_H
