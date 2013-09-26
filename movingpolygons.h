#ifndef MOVINGPOLYGONS_H
#define MOVINGPOLYGONS_H

#include <QGraphicsScene>
#include <QObject>
#include <QPolygonF>
#include <QTimer>
#include <QTimerEvent>
#include "polygonarray.h"

#define TUNNEL_WIDTH 150
#define POLYGON_HEIGHT 75
#define WIDTH_MODIFIER (TUNNEL_WIDTH/2)

class MovingPolygons : public QObject
{
    Q_OBJECT
public:
    explicit MovingPolygons(QGraphicsScene*, QGraphicsEllipseItem*, QObject *parent = 0);
    polygonBlock generateStraightCenterPolyBlock(int pos = -1);
    polygonBlock generateRandomPolyBlock();
    polygonBlock getCurrentBlock();
    polygonBlock getNextBlock();
    void rotate();
    int getSize();
    void killTime();
protected:
    void timerEvent(QTimerEvent *event);
private:
    QGraphicsScene* scene;
    QGraphicsEllipseItem* dot;
    qreal sceneWidth;
    qreal sceneHeight;
    qreal sceneMidWidth;
    PolygonArray* array;
    int size;
    bool color;
    int count;
    int timer;
    qreal lastBlockTopLeft;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
};

#endif // MOVINGPOLYGONS_H
