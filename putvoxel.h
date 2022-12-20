#ifndef PUTVOXEL_H
#define PUTVOXEL_H
#include "figurageometrica.h"

class PutVoxel :
    public FiguraGeometrica
{
    int p_x, p_y, p_z;
    float p_r, p_g, p_b, p_a;

public:
    PutVoxel(int x, int y, int z, float r, float g, float b, float a);
    void draw(Sculptor& t);
    ~PutVoxel();
};

#endif // PUTVOXEL_H
