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
#include "dot.h"

Dot::Dot(share s, int speed, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    dot =  (shared.scene->addEllipse(shared.scene->width()/2-10,
                            ((shared.walls->getSize() - 4)*POLYGON_HEIGHT)-POLYGON_HEIGHT/2-10,
                            20, 20, QPen(Qt::blue),QBrush(Qt::blue)));
    left = false;
    right = false;
    timer = startTimer(speed);
}

void Dot::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Comma) {
        left = true;
    }
    else if(event->key() == Qt::Key_Period){
        right = true;
    }
}

void Dot::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Comma) {
        left = false;
    }
    else if(event->key() == Qt::Key_Period){
        right = false;
    }
}

void Dot::timerEvent(QTimerEvent *event)
{
    if(left) dot->moveBy(-1,0);
    else if(right) dot->moveBy(1,0);
    if(dot->collidesWithItem(shared.walls->getCurrentBlock().left) ||
            dot->collidesWithItem(shared.walls->getNextBlock().left) ||
            dot->collidesWithItem(shared.walls->getCurrentBlock().right) ||
            dot->collidesWithItem(shared.walls->getNextBlock().right)) {
        killTimer(timer);
        shared.walls->killTime();
        shared.score->killTime();
        shared.screen->exec();
    }
}
