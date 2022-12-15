#include "sculptor.h"
#include <vector>

Sculptor::Sculptor()
{

}

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    //Número de linhas, colunas e planos
    nx=_nx;
    ny=_ny;
    nz=_nz;

    //Alocação dinâmica
    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0]= new Voxel[nx*ny*nz];

    for(int i=0; i< nx; i++)
    {
        v[i+1] = v[i]+ny;
        for(int j= 0; j<ny;j++){
            v[i][j+1] = v[i][j]+nz;
        }
    }

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
}


//Destrutor
Sculptor::~Sculptor(){
    if(nx==0||ny==0||nz==0){
        return;
    }
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}


void Sculptor::setColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;

}

void Sculptor::cutVoxel(int x, int y, int z)
{

     v[x][y][z].isOn = false;
}

int Sculptor::getNx()
{
    return nx;
}

int Sculptor::getNy()
{
    return ny;
}

int Sculptor::getNz()
{
    return nz;
}

vector<vector<Voxel>> Sculptor::planeXY(float zFactor)
{
    int z0 = int(nz*zFactor);

    vector<vector<Voxel>> plane;
    vector<Voxel> line;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            line.push_back(v[i][j][z0]);
        }
        plane.push_back(line);
        line.clear();
    }

    return plane;
}


/*!
 * \brief Implementa a função para escrever o arquivo off.
 * \param filename
 */
void Sculptor::writeOFF(string filename){

    ofstream fout;
    fout.open(filename);
    //Primeira linha do arquivo
    fout<<"OFF"<<endl;
    int voxel=0;

    char aux[nx][ny][nz];

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn)
                {
                    aux[nx][ny][nz]=0;
                }
            }
        }
    }

    bool auxx, auxy, auxz;

    for(int i=1;i<nx-1;i++){
        for(int j=1;j<ny-1;j++){
            for (int k=1;k<nz-1;k++){
                auxx=false; auxy=false; auxz=false;
                if(v[i+1][j][k].isOn && v[i-1][j][k].isOn){
                    auxx=true;
                }
                if(v[i][j+1][k].isOn && v[i][j-1][k].isOn){
                    auxy=true;
                }
                if(v[i][j][k+1].isOn && v[i][j][k-1].isOn){
                    auxx=true;
                }
                if(auxx && auxy && auxz){
                    aux[i][j][k]=1;
                }
            }
        }
    }
    //O loop está contando o número de voxels ativos
    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn && aux[i][j][k]==0)
                {
                    voxel++;
                }
            }
        }
    }

    /*Segunda linha do arquivo. Mútiplica a quantidade total de voxels
     * pelo número de vértices e faces de um único cubo para obter a
     * quantidade total de vértices e faces presentes no desenho.
    */
    fout<<voxel*8<<" "<<voxel*6<<" "<<endl;
    /*Para todo voxel ativo, o laço calcula a posição dos seus 8
     * vértices. Olhar resumo (Figura 3).
    */
    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    fout<<-0.5+i<<" "<<0.5+j<<" "<<-0.5+k<<endl;
                    fout<<-0.5+i<<" "<<-0.5+j<<" "<<-0.5+k<<endl;
                    fout<<0.5+i<<" "<<-0.5+j<<" "<<-0.5+k<<endl;
                    fout<<0.5+i<<" "<<0.5+j<<" "<<-0.5+k<<endl;
                    fout<<-0.5+i<<" "<<0.5+j<<" "<<0.5+k<<endl;
                    fout<<-0.5+i<<" "<<-0.5+j<<" "<<0.5+k<<endl;
                    fout<<0.5+i<<" "<<-0.5+j<<" "<<0.5+k<<endl;
                    fout<<0.5+i<<" "<<0.5+j<<" "<<0.5+k<<endl;
                }
            }
        }
    }

    /*O primeiro número de cada linha simboliza quantos vértices são necessários
     *para formar uma face, os quatro números em seguida representam os vértices
     * que formam uma determinada face. Os quatro números finais de cada linha
     * simbolizam a cor e a tranaparência de cada voxel. Ao incrementar o valor
     * vértice por 8 toda vez que um voxel ativo for encontrado, impede-se que
     * existam linhas com os mesmos valores. Cada voxel terá seus próprios valores
     * de vértice.
    */

    int vertice=0;
    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    fout<<"4 "<<vertice+0<<" "<<vertice+3<<" "<<vertice+2<<" "<<vertice+1<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vertice+4<<" "<<vertice+5<<" "<<vertice+6<<" "<<vertice+7<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vertice+0<<" "<<vertice+1<<" "<<vertice+5<<" "<<vertice+4<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vertice+0<<" "<<vertice+4<<" "<<vertice+7<<" "<<vertice+3<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vertice+3<<" "<<vertice+7<<" "<<vertice+6<<" "<<vertice+2<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vertice+1<<" "<<vertice+2<<" "<<vertice+6<<" "<<vertice+5<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;

                    vertice+=8;
                }
            }
        }
    }
    fout.close();
}