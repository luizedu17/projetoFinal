#include "putsphere.h"
PutSphere::PutSphere(int x0, int y0, int z0, int rd, float r, float g, float b, float a)
    : p_x0(x0), p_y0(y0), p_z0(z0), p_rd(rd), p_r(r), p_g(g), p_b(b), p_a(a)
{
}
void PutSphere::draw(Sculptor& t)
{
    int i, j, k;
    float DisX, DisY, DisZ;

    t.setColor(p_r, p_b, p_b, p_a);

    for (i = p_z0 - p_rd; i < p_z0 + p_rd; i++) {
        DisZ = ((float)(i - p_z0)) / ((float)(p_rd));
        for (j = p_y0 - p_rd; j < p_y0 + p_rd; j++) {
            DisY = ((float)(j - p_y0)) / ((float)(p_rd));
            for (k = p_x0 - p_rd; k < p_x0 + p_rd; k++) {
                DisX = ((float)(k - p_x0)) / ((float)(p_rd));
                if ((DisX * DisX + DisY * DisY + DisZ * DisZ) <= 1.00) {
                    t.putVoxel(i, j, k);
                }
            }
        }
    }
}
