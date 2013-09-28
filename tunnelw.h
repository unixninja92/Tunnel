/*
 *Copyright 2013 unixninja92
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
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

typedef struct Share{
    QGraphicsScene* scene;
    MovingPolygons* walls;
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
    void updateScore();
protected:
    void timerEvent(QTimerEvent *event);
private:
    share shared;
    QGraphicsSimpleTextItem* scoreKeeper;
    PolygonArray* array;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
    qreal sceneWidth;
    qreal sceneHeight;
    qreal sceneMidWidth;
    qreal lastBlockTopLeft;
    int size;
    int count;
    int wallTimer;
    int scoreTimer;
    int score;
};
#endif // TUNNELW_H
