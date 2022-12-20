#include "sculptor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "cutbox.h"
#include "cutellipsoid.h"
#include "cutsphere.h"
#include "cutvoxel.h"
#include "figurageometrica.h"
#include "putbox.h"
#include "putellipsoid.h"
#include "putsphere.h"
#include "putvoxel.h"
#include "sculptor.h"

using namespace std;

int main()
{
    vector<FiguraGeometrica*> figs;
    ifstream ifile("Teste.txt", ios::in);

    string part1;
    int nx, ny, nz;
    int x, y, z,
        x1, y1, z1,
        rd, rdx, rdy, rdz;
    float r, g, b, a;

    if (!ifile) {
        cerr << "Erro ao abrir arquivo.";
        exit(1);
    }

    ifile >> part1 >> nx >> ny >> nz;
    Sculptor S(nx, ny, nz);
    cout << "Tamanho da escultura: " << nx << "x" << ny << "x" << nz << "\n\n";

    while (ifile >> part1) {

        if ("putvoxel" == part1) {

            ifile >> x >> y >> z
                >> r >> g >> b >> a;

            figs.push_back(new PutVoxel(x, y, z, r, g, b, a));
        }
        else if ("cutvoxel" == part1) {
            ifile >> x >> y >> z;

            figs.push_back(new CutVoxel(x, y, z));
        }
        else if ("putbox" == part1) {
            ifile >> x >> x1
                >> y >> y1
                >> z >> z1
                >> r >> g >> b >> a;

            figs.push_back(new PutBox(x, y, z, x1, y1, z1, r, g, b, a));
        }
        else if ("cutbox" == part1) {
            ifile >> x >> x1
                >> y >> y1
                >> z >> z1;

            figs.push_back(new CutBox(x, y, z, x1, y1, z1));

        }
        else if ("putsphere" == part1) {
            ifile >> x >> y >> z
                >> rd
                >> r >> g >> b >> a;

            figs.push_back(new PutSphere(x, y, z, rd, r, g, b, a));
        }
        else if ("cutsphere" == part1) {
            ifile >> x >> y >> z
                >> rd;
            figs.push_back(new CutSphere(x, y, z, rd));
        }
        else if ("putellipsoid" == part1) {
            ifile >> x >> y >> z
                >> rdx >> rdy >> rdz
                >> r >> g >> b >> a;

            figs.push_back(new PutEllipsoid(x, y, z, rdx, rdy, rdz, r, g, b, a));

        }
        else if ("cutellipsoid" == part1) {
            ifile >> x >> y >> z
                >> rdx >> rdy >> rdz;

            figs.push_back(new CutEllipsoid(x, y, z, rdx, rdy, rdz));

        }
        else {
            cerr << "Erro no arquivo.\n";
            exit(1);
        }
    }

    for (auto& fig : figs) {
        fig->draw(S);
        delete fig;
    }

    S.writeOFF((char*)"Teste.txt.off");
}
