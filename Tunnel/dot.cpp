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
#include "dot.h"

Dot::Dot(share s, int speed, double m, QOpenGLWidget *parent) :
    QOpenGLWidget(parent)
{
    shared = s;
    dot =  (shared.scene->addEllipse(
                shared.scene->width()/2-10,//x
                ((shared.walls->getSize() - 4)*POLYGON_HEIGHT)-POLYGON_HEIGHT/2-10,//y
                DOT_DIAMETER, //width
                DOT_DIAMETER, //height
                QPen(Qt::blue), //outline
                QBrush(Qt::blue)));//fill
    moveLeft = false;
    moveRight = false;
    timer = startTimer(speed);
    pixlesToMove = m;
}

void Dot::keyPressEvent(QKeyEvent *event)
{
    if(!Share::isPaused) {
        if(event->key() == Qt::Key_Comma) {
            moveLeft = true;
        }
        else if(event->key() == Qt::Key_Period){
            moveRight = true;
        }
    }
}

void Dot::keyReleaseEvent(QKeyEvent *event)
{
    if(!Share::isPaused) {
        if(event->key() == Qt::Key_Comma) {
            moveLeft = false;
        }
        else if(event->key() == Qt::Key_Period){
            moveRight = false;
        }
    }
}

void Dot::timerEvent(QTimerEvent *event)
{
    if(!Share::isPaused) {
        if(moveLeft) dot->moveBy(-pixlesToMove,0);
        else if(moveRight) dot->moveBy(pixlesToMove,0);
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
}
