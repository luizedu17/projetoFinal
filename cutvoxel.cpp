#include "cutvoxel.h"
#include <iostream>
CutVoxel::CutVoxel(int x, int y, int z) : p_x(x), p_y(y), p_z(z)
{
}
void CutVoxel::draw(Sculptor& t)
{
    t.cutVoxel(p_z, p_y, p_x);
}
