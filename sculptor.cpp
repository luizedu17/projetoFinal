#include "sculptor.h"
#include <cstdlib>		// for exit()
#include <iostream>		// for std::cout std::cerr
#include <string>		//for std::string
#include <fstream>		//for std::ofstream
#include <algorithm>	// for std::swap()
using namespace std;

/*
Método para criar matriz 3d alocada dinamicamente com padrão inicializado _nx, _ny e _nz = 20, que será o tamanho máximo da "escultura" em seus eixos.
*/

Sculptor::Sculptor(int _nx, int _ny, int _nz) : r(0.5), g(0.5), b(0.5), a(0.5)
{
    _nx = 20;
    _ny = 20;
    _nz = 20;
    int i;

    if (_nx <= 0 || _ny <= 0 || _nz <= 0) cout << "Valores de dimensão inválidos, criando escultura padrão.";
    if (_nx <= 0) _nx = 2;
    if (_ny <= 0) _ny = 2;
    if (_nz <= 0) _nz = 2;

    nx = _nx;
    ny = _ny;
    nz = _nz;


    v = new Voxel**[_nx];
    v[0] = new Voxel*[_nx*_ny];
    v[0][0] = new Voxel[_nx*_ny*_nz];

    if (!(v && v[0] && v[0][0])) {
        cerr << "Impossível alocar espaco de escultura.\n";
        exit(1);
    }


    for (i = 1; i < nz; i++) {
        v[i] = v[i - 1] + ny;
    }
    for (i = 1; i < nz*ny; i++) {
        v[0][i] = v[0][i - 1] + nx;
    }

    for (int i = 0; i < nz; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nx; k++) {
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;
                v[i][j][k].isOn = false;
            }
        }
    }
    cout << "Espaco de escultura criado.\n";
}

/*
Método usado para desocupar o espaco alocado para a matriz 3d;
*/

Sculptor::~Sculptor(){
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
    cout << "Espaco desocupado.\n";
}

/*
Método para atribuir cor e transparência/opacidade.
r,g,b [0,1] correspondem à ausência total(0) ou presença total(1) dos componentes de cor vermelha, verde e azul respectivamente
alpha [0,1] corresponde à transparência total(0) ou opacidade total(1)
*/

void Sculptor::setColor(float r, float g, float b, float alpha) {

    if (r < 0) r = 0;
    else if (r > 1) r = 1;

    if (g < 0) g = 0;
    else if (g > 1) g = 1;

    if (b < 0) b = 0;
    else if (b > 1) b = 1;

    if (alpha < 0) alpha = 0;
    else if (alpha > 1) alpha = 1;

    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
}

void Sculptor::putVoxel(int z, int y, int x) {

    v[z][y][x].isOn = true;
    v[z][y][x].r = r;
    v[z][y][x].g = g;
    v[z][y][x].b = b;
    v[z][y][x].a = a;
}

void Sculptor::cutVoxel(int z, int y, int x) {
 {
        return;
    }

    v[z][y][x].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {

    int i, j, k;
    for (i = z0; i < z1; i++) {
        for (j = y0; j < y1; j++) {
            for (k = x0; k < x1; k++) {
                v[i][j][k].isOn = true;
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {

    int i, j, k;
    for (i = z0; i < z1; i++) {
        for (j = y0; j < y1; j++) {
            for (k = x0; k < x1; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {

    int i, j, k;
    float DisX, DisY, DisZ;

    for (i = 0; i < nz; i++) {
        DisZ = ((float)(i - zcenter)) / ((float)(radius));
        for (j = 0; j < ny; j++) {
            DisY = ((float)(j - ycenter)) / ((float)(radius));
            for (k = 0; k < nx; k++) {
                DisX = ((float)(k - xcenter)) / ((float)(radius));
                if ((DisX*DisX + DisY * DisY + DisZ * DisZ) <= 1.00) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {

    int i, j, k;
    double DisX, DisY, DisZ;

    for (i = 0; i < nz; i++) {
        DisZ = ((double)(i - zcenter)) / (double)(radius);

        for (j = 0; j < ny; j++) {
            DisY = ((double)(j - ycenter)) / (double)(radius);

            for (k = 0; k < nx; k++) {
                DisX = ((double)(k - xcenter)) / (double)(radius);
                if (((DisX*DisX + DisY * DisY + DisZ * DisZ) <= 1.00)) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {

    int i, j, k;
    double DisX, DisY, DisZ;

    for (i = 0; i < nz; i++) {
        DisZ = ((double)(i - zcenter)) / (double)(rz);
        for (j = 0; j < ny; j++) {
            DisY = ((double)(j - ycenter)) / (double)(ry);
            for (k = 0; k < nx; k++) {
                DisX = ((double)(k - xcenter)) / (double)(rx);
                if (((DisX*DisX + DisY * DisY + DisZ * DisZ) <= 1.00)) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {

    int i, j, k;
    double DisX, DisY, DisZ;

    for (i = 0; i < nz; i++) {
        DisX = ((double)(i - zcenter)) / (double)(rz);
        for (j = 0; j < ny; j++) {
            DisY = ((double)(j - ycenter)) / (double)(ry);
            for (k = 0; k < nx; k++) {

                DisZ = ((double)(k - xcenter)) / (double)(rx);
                if ((DisX*DisX + DisY * DisY + DisZ * DisZ) <= 1.00) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filename){

    std::ofstream ofile;

    ofile.open(filename);
    int countVox = 0;
    int face=0;
    int nfacs = 0;

    if (!ofile.is_open()) {
        std::cerr << "Erro ao salvar arquivo .off\n";
        return;
    }

    ofile << "OFF ";

    for (int i = 0; i < nz; i++)
        for (int j = 0; j < ny; j++)
            for (int k = 0; k < nx; k++)
                if (v[i][j][k].isOn)
                    countVox++;

    ofile << 8 * countVox << " " << 6 * countVox << " 0\n";

    for (int k = 0; k < nz; k++) {
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                if (v[k][j][i].isOn) {
                  ofile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n"
                        << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n"
                        << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n"
                        << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n"
                        << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n"
                        << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n"
                        << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n"
                        << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                }
            }
        }
    }

    for (int i = 0; i < nz; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nx; k++) {
                if (v[i][j][k].isOn) {
                    face = 8 * nfacs;
                    ofile << "4 " << face + 0 << " " << face + 3 << " " << face + 2 << " " << face + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                        << "4 " << face + 4 << " " << face + 5 << " " << face + 6 << " " << face + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                        << "4 " << face + 0 << " " << face + 1 << " " << face + 5 << " " << face + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                        << "4 " << face + 0 << " " << face + 4 << " " << face + 7 << " " << face + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                        << "4 " << face + 3 << " " << face + 7 << " " << face + 6 << " " << face + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                        << "4 " << face + 1 << " " << face + 2 << " " << face + 6 << " " << face + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    nfacs++;
                }
            }
        }
    }

    ofile.close();
    cout << "Arquivo .off criado.\n";

}
