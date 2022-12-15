#include "plotter.h"
#include "sculptor.h"
#include "figurageometrica.h"
#include "putbox.h"
#include "cutbox.h"
#include "putsphere.h"
#include "cutsphere.h"
#include "putellipsoid.h"
#include "cutellipsoid.h"
#include "putvoxel.h"
#include "cutvoxel.h"
#include <vector>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}



/*!
 * \brief Função responsável por capturar o evento de arrastar/clicar do mouse e desenhar as formas geométricas.
 * \param event
 */
void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;


    brush.setColor(QColor(0,0,0));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    QVector<qreal> dashes;
    qreal space = 1;
    dashes << 9 << space << 9 << space;
    pen.setDashPattern(dashes);
    pen.setDashOffset(3);
    p.setPen(pen);


    int sizeH = int(plane2D.size());
    int sizeV = int(plane2D[0].size());
    float normSizeH = width()/sizeH;
    float normSizeV = height()/sizeV;
    float normSize;

    if(normSizeH <= normSizeV){
        normSize = normSizeH;
    }
    else{
        normSize = normSizeV;
    }

    normalizao=normSize;
    QPoint *plottingStart = new QPoint(width()/2 - normSize*sizeH/2, height()/2 - normSize*sizeV/2);
    plotStart=plottingStart;
    for(int i=0; i<sizeH; i++)
    {
        for(int j=0; j<sizeV; j++)
        {
            if(!plane2D[i][j].isOn){
                brush.setColor(QColor(255,203,219));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);

                pen.setColor(QColor(255,255,255));
                pen.setWidth(1);
                p.setPen(pen);

                p.drawRect(i*normSize + plottingStart->x(), j*normSize + plottingStart->y(),
                           normSize, normSize);
            }

        }
    }

    for(int i=0; i<sizeH; i++)
    {
        for(int j=0; j<sizeV; j++)
        {
            if(plane2D[i][j].isOn){
                brush.setColor(QColor(plane2D[i][j].r*255,plane2D[i][j].g*255,plane2D[i][j].b*255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);

                pen.setColor(QColor(0,0,0));
                pen.setWidth(0.5);
                pen.setStyle(Qt::SolidLine);
                p.setPen(pen);

                p.drawRect(i*normSize + plottingStart->x(), j*normSize + plottingStart->y(),
                           normSize, normSize);
            }

        }
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event){
    emit moveXY((event->x() - (plotStart->x()))/normalizao, (event->y()- (plotStart->y()))/normalizao);

    emit clickX((event->x() - (plotStart->x()))/normalizao);
    emit clickY((event->y()- (plotStart->y()))/normalizao);
    if(lmbPressed){
        emit clickXY((event->x() - (plotStart->x()))/normalizao, (event->y()- (plotStart->y()))/normalizao);
    }
}

void Plotter::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton ){
    emit clickX((event->x() - (plotStart->x()))/normalizao);
    emit clickY((event->y()- (plotStart->y()))/normalizao);
    emit clickXY((event->x() - (plotStart->x()))/normalizao, (event->y()- (plotStart->y()))/normalizao);
    lmbPressed = true;
  }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton ){
    lmbPressed = false;
  }
}


/*!
 * \brief Função responsável por exibir a matriz.
 * \param sculpt
 * \param depth
 */
void Plotter::paintMatrix(Sculptor *sculpt, int depth){

    float depthNorm = float(depth)/100;


    plane2D = sculpt->planeXY(depthNorm);

    repaint();
}
