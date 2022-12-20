#ifndef CUTBOX_H
#define CUTBOX_H
#include "figurageometrica.h"


class CutBox :
    public FiguraGeometrica
{
    int	p_x0, p_y0, p_z0, p_x1, p_y1, p_z1;
public:
    CutBox(int x0, int y0, int z0, int x1, int y1, int z1);
    void draw(Sculptor& t);
};

#endif // CUTBOX_H
