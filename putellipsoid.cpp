#include "putellipsoid.h"
PutEllipsoid::PutEllipsoid(int x0, int y0, int z0,int rdX,int rdY,int rdZ, float r, float g, float b, float a)
    : p_x0(x0), p_y0(y0), p_z0(z0), p_rdX(rdX), p_rdY(rdY), p_rdZ(rdZ), p_r(r), p_g(g), p_b(b), p_a(a)
{
}
void PutEllipsoid::draw(Sculptor& t)
{
    int i, j, k;
    double DisX, DisY, DisZ;

    t.setColor(p_r, p_g, p_b, p_a);

    for (i = p_z0 - p_rdZ; i < p_z0 + p_rdZ; i++) {
        DisX = ((double)(i - p_z0)) / (double)(p_rdZ);
        for (j = p_y0 - p_rdY; j < p_y0 + p_rdY; j++) {
            DisY = ((double)(j - p_y0)) / (double)(p_rdY);
            for (k = p_x0 - p_rdX; k < p_x0 + p_rdX; k++) {
                DisZ = ((double)(k - p_x0)) / (double)(p_rdX);
                if ((DisX * DisX + DisY * DisY + DisZ * DisZ) <= 1.00) {
                    t.putVoxel(i, j, k);
                }
            }
        }
    }
}
