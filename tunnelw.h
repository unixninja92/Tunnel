#ifndef TUNNELW_H
#define TUNNELW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
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
