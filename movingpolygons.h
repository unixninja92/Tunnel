/*
 *Copyright 2014 unixninja92
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
