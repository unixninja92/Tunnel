/*
 *  Copyright 2013 unixninja92
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
#ifndef MOVINGPOLYGONS_H
#define MOVINGPOLYGONS_H

#include <QGraphicsScene>
#include <QObject>
#include <QPolygonF>
#include <QTimer>
#include <QTimerEvent>
#include <QGraphicsSimpleTextItem>
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
    void updateScore();
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
    int wallTimer;
    int scoreTimer;
    int score;
    QGraphicsSimpleTextItem* scoreKeeper;
    qreal lastBlockTopLeft;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
};

#endif // MOVINGPOLYGONS_H
