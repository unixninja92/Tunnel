#ifndef MOVINGPOLYGONS_H
#define MOVINGPOLYGONS_H

#include <QObject>
#include <QList>
#include <shared.h>

class MovingPolygons : public QObject
{
    Q_OBJECT
public:
    explicit MovingPolygons(share, QObject *parent = 0);
    polygonBlock generateStraightCenterPolyBlock(int pos = -1);
    polygonBlock generateRandomPolyBlock();
    polygonBlock getCurrentBlock();
    polygonBlock getNextBlock();
    int getSize();
    void rotate();
    void killTime();

protected:
    void timerEvent(QTimerEvent *event);

private:
    share shared;
//    PolygonArray* array;
    QList<polygonBlock> queue;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
    qreal sceneWidth;
    qreal sceneHeight;
    qreal sceneMidWidth;
    qreal lastBlockTopLeft;
    int size;
    int count;
    int wallTimer;
};

//class MovingPolygons : public QObject
//{
//    Q_OBJECT
//public:
//    explicit MovingPolygons(QObject *parent = 0);
//    ~MovingPolygons();

//signals:

//public slots:
//};

#endif // MOVINGPOLYGONS_H
