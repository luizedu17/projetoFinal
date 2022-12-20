#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H
#include "figurageometrica.h"

class CutEllipsoid :
    public FiguraGeometrica
{
    int	p_x0, p_y0, p_z0, p_rdX, p_rdY, p_rdZ;
public:
    CutEllipsoid(int x0, int y0, int z0, int rdX, int rdY, int rdZ);
    void draw(Sculptor& t);
};

#endif // CUTELLIPSOID_H
