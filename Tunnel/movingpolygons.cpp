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
#include "movingpolygons.h"
#include <QDebug>
#include <math.h>
#include <ctime>

MovingPolygons::MovingPolygons(share s, double m, QObject *parent) :
    QObject(parent)
{
    shared = s;
    sceneWidth = shared.scene->width();
    sceneMidWidth = sceneWidth/2;
    sceneHeight = shared.scene->height();
    size = sceneHeight/POLYGON_HEIGHT+3;
    queue = *new QList<polygonBlock>();
    for(int i = 0; i < size; i++){
        queue.append(generateStraightCenterPolyBlock(i-1));
    }
    count = 0;
    qsrand(time(NULL));

    move = m;
}

polygonBlock MovingPolygons::generateStraightCenterPolyBlock(int pos)
{
    QPolygonF left;
    QPolygonF right;
    int yLow = POLYGON_HEIGHT*(pos+1);
    int yHigh = POLYGON_HEIGHT*pos;
    QPoint lStart = QPoint(0,yLow);
    QPoint rStart = QPoint(sceneWidth,yLow);

    left << lStart
         << QPoint(0, yHigh)
         << QPoint(sceneMidWidth-WIDTH_MODIFIER, yHigh)
         << QPoint(sceneMidWidth-WIDTH_MODIFIER, yLow)
         << lStart;

    right << rStart
          << QPoint(sceneWidth, yHigh)
          << QPoint(sceneMidWidth+WIDTH_MODIFIER, yHigh)
          << QPoint(sceneMidWidth+WIDTH_MODIFIER, yLow)
          << rStart;

    lastBlockTopLeft = sceneMidWidth-WIDTH_MODIFIER;
    return generatePolygonBlock(left, right);
}

polygonBlock MovingPolygons::generateRandomPolyBlock()
{
    QPolygonF left;
    QPolygonF right;
    int rand;
    int yLow = 0;
    int yHigh = -POLYGON_HEIGHT;
    QPoint lStart = QPoint(0,yLow);
    QPoint rStart = QPoint(sceneWidth,yLow);

    if(qrand()%2 ==1){
        rand = lastBlockTopLeft;
    }
    else if(qrand()%2 ==1){
        if(lastBlockTopLeft-0 > TUNNEL_WIDTH)
            rand = lastBlockTopLeft-TUNNEL_WIDTH;
        else
            rand = lastBlockTopLeft+TUNNEL_WIDTH;
    }
    else {
        if(sceneWidth-lastBlockTopLeft > TUNNEL_WIDTH)
            rand = lastBlockTopLeft+TUNNEL_WIDTH;
        else
            rand = lastBlockTopLeft-TUNNEL_WIDTH;
    }

    left << lStart
         << QPoint(0, yHigh)
         << QPoint(rand, yHigh)
         << QPoint(lastBlockTopLeft, yLow)
         << lStart;

    right << rStart
          << QPoint(sceneWidth, yHigh)
          << QPoint(rand+TUNNEL_WIDTH, yHigh)
          << QPoint(lastBlockTopLeft+TUNNEL_WIDTH, yLow)
          << rStart;

    lastBlockTopLeft = rand;

    return generatePolygonBlock(left, right);
}

polygonBlock MovingPolygons::generatePolygonBlock(QPolygonF left,
                                                  QPolygonF right)
{
    polygonBlock newBlock;

    newBlock.left = shared.scene->addPolygon(left);
    newBlock.left->setBrush(Qt::black);

    newBlock.right = shared.scene->addPolygon(right);
    newBlock.right->setBrush(Qt::black);

    return newBlock;
}

polygonBlock MovingPolygons::getCurrentBlock()
{
    return queue.at(size-4);
}

polygonBlock MovingPolygons::getNextBlock()
{
    return queue.at(size-5);
}

void MovingPolygons::rotate()
{
    queue.pop_back();
    queue.push_front(generateRandomPolyBlock());
}

int MovingPolygons::getSize()
{
    return size;
}

void MovingPolygons::tick()
{
    for(int i = 0; i<size; i++){
        queue.at(i).left->moveBy(0,move);
        queue.at(i).right->moveBy(0,move);
    }
    count++;
    if(count%((int)floor(POLYGON_HEIGHT/move))==0)
        rotate();
}

