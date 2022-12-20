#include "cutsphere.h"
CutSphere::CutSphere(int x0, int y0, int z0, int rd): p_x0(x0), p_y0(y0), p_z0(z0), p_rd(rd)
{
}
void CutSphere::draw(Sculptor& t)
{
    int i, j, k;
    float DisX, DisY, DisZ;

    for (i = p_z0-p_rd; i < p_z0+p_rd; i++) {
        DisZ = ((float)(i - p_z0)) / ((float)(p_rd));
        for (j = p_y0 - p_rd; j < p_y0 + p_rd; j++) {
            DisY = ((float)(j - p_y0)) / ((float)(p_rd));
            for (k = p_x0 - p_rd; k< p_x0 + p_rd; k++) {
                DisX = ((float)(k - p_x0)) / ((float)(p_rd));
                if ((DisX * DisX + DisY * DisY + DisZ * DisZ) <= 1.00) {
                    t.cutVoxel(i, j, k);
                }
            }
        }
    }
}
