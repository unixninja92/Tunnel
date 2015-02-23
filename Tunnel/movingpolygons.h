/*
 * Tunnel Copyright 2015 unixninja92
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
    explicit MovingPolygons(share, int, double, QObject *parent = 0);
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
    QList<polygonBlock> queue;
    polygonBlock generatePolygonBlock(QPolygonF, QPolygonF);
    qreal sceneWidth;
    qreal sceneHeight;
    qreal sceneMidWidth;
    qreal lastBlockTopLeft;
    int size;
    int count;
    int wallTimer;
    double move;
};

#endif // MOVINGPOLYGONS_H
