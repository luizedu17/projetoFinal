#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;


struct Voxel {
  float r,g,b;
  float a;
  bool isOn;
};

class Sculptor {
protected:
  int nx, ny, nz;
  Voxel ***v;
  float r,g,b,a;
public:
  Sculptor();
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float red, float green, float blue, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  int getNx();
  int getNy();
  int getNz();
  vector<vector<Voxel>> planeXY(float zFactor);
  vector<vector<vector<Voxel>>> plane3D();
  void writeOFF(string filename);
};

#endif // SCULPTOR_H