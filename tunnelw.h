#ifndef TUNNELW_H
#define TUNNELW_H

#define TUNNEL_WIDTH 100
#define POLYGON_HEIGHT 75
#define WIDTH_MODIFIER (TUNNEL_WIDTH/2)

#include <QWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "polygonarray.h"
//#include "linker.h"

class Dot;
class MovingPolygons;
class Score;

typedef struct Share{
    QGraphicsScene* scene;
    MovingPolygons* walls;
    Score* score;
    Dot* dot;
}share;

namespace Ui {
class TunnelW;
}

class TunnelW : public QWidget
{
    Q_OBJECT

public:
    explicit TunnelW(QWidget *parent = 0);
    ~TunnelW();
    void startGame();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::TunnelW *ui;
    void createScene(int w, int h);
    share shared;
};

class Dot : public QWidget
{
    Q_OBJECT
public:
    explicit Dot(share, QWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    share shared;
    QGraphicsEllipseItem* dot;
    bool left;
    bool right;
    int timer;
};


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
    PolygonArray* array;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
    qreal sceneWidth;
    qreal sceneHeight;
    qreal sceneMidWidth;
    qreal lastBlockTopLeft;
    int size;
    int count;
    int wallTimer;
};

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(share, QObject *parent=0);
    void killTime();
    void updateScore();
    int getScore();

protected:
    void timerEvent(QTimerEvent *event);

private:
    share shared;
    QGraphicsSimpleTextItem* scoreKeeper;
    int score;
    int scoreTimer;
};

#endif // TUNNELW_H
