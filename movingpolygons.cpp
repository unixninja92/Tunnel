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
#include "movingpolygons.h"

MovingPolygons::MovingPolygons(share s, QObject *parent) :
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
    wallTimer = startTimer(40);
    qsrand(time(NULL));
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
//    else{
//        rand = qrand()%((int)sceneWidth-TUNNEL_WIDTH -20)+10;
//    }

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

polygonBlock MovingPolygons::generatePolygonBlock(QPolygonF left, QPolygonF right)
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

void MovingPolygons::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==wallTimer){
        for(int i = 0; i<size; i++){
            queue.at(i).left->moveBy(0,1);
            queue.at(i).right->moveBy(0,1);
        }
        count++;
        if(count%75==0) rotate();
    }
}

void MovingPolygons::killTime()
{
    killTimer(wallTimer);
}
