#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H
#include "figurageometrica.h"

class PutEllipsoid :
    public FiguraGeometrica
{
    int	p_x0, p_y0, p_z0, p_rdX, p_rdY, p_rdZ;
    float p_r, p_g, p_b, p_a;

public:
    PutEllipsoid(int x0, int y0, int z0, int rdX, int rdY, int rdZ, float r, float g, float b, float a);
    void draw(Sculptor& t);
};

#endif // PUTELLIPSOID_H
