#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "figurageometrica.h"

class CutVoxel :
    public FiguraGeometrica
{
    int p_x, p_y, p_z;
public:
    CutVoxel(int x, int y, int z);
    void draw(Sculptor& t);
};

#endif // CUTVOXEL_H
