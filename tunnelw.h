#ifndef TUNNELW_H
#define TUNNELW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include "movingpolygons.h"

namespace Ui {
class TunnelW;
}

class TunnelW : public QWidget
{
    Q_OBJECT

public:
    explicit TunnelW(QWidget *parent = 0);
    ~TunnelW();
    void drawDot();
    void drawLeft();
    void drawRight();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    Ui::TunnelW *ui;
    QGraphicsEllipseItem* dot;
    QGraphicsScene* scene;
    void createScene(int w, int h);
    QGraphicsPolygonItem* leftSide;
    QGraphicsPolygonItem* rightSide;
    MovingPolygons* polyBlocks;
    bool left;
    bool right;
};

#endif // TUNNELW_H
