#ifndef PUTSPHERE_H
#define PUTSPHERE_H
#include "figurageometrica.h"

class PutSphere :
    public FiguraGeometrica
{
    int p_x0, p_y0, p_z0, p_rd;
    float p_r, p_g, p_b, p_a;

public:
    PutSphere(int x0, int y0, int z0, int rd, float r, float g, float b, float a);
    void draw(Sculptor& t);
};

#endif // PUTSPHERE_H
