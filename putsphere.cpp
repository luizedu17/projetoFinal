#include "putsphere.h"


PutSphere::PutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius, float _r, float _g, float _b, float _a)
{
    xcenter = _xcenter;ycenter = _ycenter;zcenter = _zcenter;radius = _radius;
    r = _r;g = _g;b = _b;a = _a;
}
PutSphere::~PutSphere()
{

}

void PutSphere::draw(Sculptor &t){
    for (int i = xcenter-radius; i < xcenter+radius; i++) {
        for (int j = ycenter-radius; j < ycenter+radius; j++){
            for (int k = zcenter-radius; k < zcenter+radius; k++){
                if(((float)pow((i-xcenter),2))+((float)pow((j-ycenter),2))+((float)pow((k-zcenter),2))<=(pow(radius,2))){
                    t.putVoxel(i,j,k);
                }
            }
        }
    }
}