#include "putvoxel.h"
PutVoxel::PutVoxel(int x, int y, int z, float r, float g, float b, float a)
    : p_x(x), p_y(y), p_z(z), p_r(r), p_g(g), p_b(b), p_a(a)
{
}
void PutVoxel::draw(Sculptor& t) {
    t.setColor(p_r, p_g, p_b, p_a);
    t.putVoxel(p_z, p_y, p_x);
}

PutVoxel::~PutVoxel()
{
}
