/*
 *Copyright 2015 unixninja92
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

