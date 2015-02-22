#ifndef SHARED
#define SHARED

#define TUNNEL_WIDTH 100
#define POLYGON_HEIGHT 75
#define WIDTH_MODIFIER (TUNNEL_WIDTH/2)

#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QPointer>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>

class MovingPolygons;
class Score;
class Dot;
class EndScreen;
class TunnelW;

typedef struct Share{
    QPointer<QGraphicsScene> scene;
    QPointer<MovingPolygons> walls;
    QPointer<Score> score;
    QPointer<Dot> dot;
    QPointer<EndScreen> screen;
}share;

typedef struct polygonBlock {
    QGraphicsPolygonItem* left;
    QGraphicsPolygonItem* right;
}polygonBlock;

namespace Ui {
class TunnelW;
}

#endif // SHARED

