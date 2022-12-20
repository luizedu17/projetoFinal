#include "cutbox.h"

CutBox::CutBox(int x0, int y0, int z0, int x1, int y1, int z1)
    : p_x0(x0), p_y0(y0), p_z0(z0), p_x1(x1), p_y1(y1), p_z1(z1)
{
}

void CutBox::draw(Sculptor& t)
{
    int i, j, k;
    for (i = p_z0; i < p_z1; i++) {
        for (j = p_y0; j < p_y1; j++) {
            for (k = p_x0; k < p_x1; k++) {
                t.cutVoxel(i, j, k);
            }
        }
    }
}
