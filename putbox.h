#ifndef PUTBOX_H
#define PUTBOX_H
#include "figurageometrica.h"

class PutBox :
    public FiguraGeometrica
{

    int	p_x0, p_y0, p_z0, p_x1, p_y1, p_z1;
    float p_r, p_g, p_b, p_a;

public:
    PutBox(int x0, int y0, int z0, int x1, int y1, int z1, float r, float g, float b, float a);
    void draw(Sculptor& t);
};

#endif // PUTBOX_H
