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
#include "tunnel.h"
#include <QDebug>
#include <QSettings>
#include <QPainter>

bool Share::isPaused = false;

Tunnel::Tunnel(QOpenGLWidget *parent) :
    QOpenGLWidget(parent)
{

    started = false;
}

//void TunnelW::createScene(int w, int h)
//{
//    shared.scene = new QGraphicsScene(this);
//    shared.scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//    ui->view->setScene(shared.scene);
//    shared.scene->setSceneRect(0,0,w-2,h-2);
//    shared.scene->setBackgroundBrush(Qt::gray);
//}

void Tunnel::runGame(Level l)
{
    paintDevice = new QOpenGLPaintDevice();
//    score = new Score(shared, this);
//    screen = new EndScreen(shared, this, level);

    QPainter* wallPainter = new QPainter(paintDevice);
    this->initPainter(wallPainter);
    wallPainter->beginNativePainting();
//    QBrush* solidBlack(Qt::SolidPattern);
    wallPainter->setBackground(*new QBrush(Qt::gray));
    wallPainter->setBrush(Qt::SolidPattern);
    wallPainter->setRenderHint(QPainter::Antialiasing);

    dot = new QPainterPath();
    dot->addEllipse(paintDevice->width()/2-10,//x
                    ((walls->getSize() - 4)
                     *shared.pHeight)-shared.pHeight/2-10,//y
                    DOT_DIAMETER, //width
                    DOT_DIAMETER);//height
    Share::isPaused = false;
    moveLeft = false;
    moveRight = false;
    level = l;
    started = true;
    walls = new MovingPolygons(shared, pMove, paintDevice->height(),
                               paintDevice->width());

    while(!Share::isPaused){
        qDebug() << "new while!";
        walls->tick(wallPainter);
        qDebug() << "TICK";

        if(moveLeft) dot->translate(-dMove,0);
        else if(moveRight) dot->translate(dMove,0);
        qDebug() << "Move dat dot";
//        if(dot->intersects(*walls->getCurrentBlock().left) ||
//                dot->intersects(*walls->getNextBlock().left) ||
//                dot->intersects(*walls->getCurrentBlock().right) ||
//                dot->intersects(*walls->getNextBlock().right)) {
//            qDebug() << "YOU LOST";
//            wallPainter->endNativePainting();
//            endGame();
//        }
        wallPainter->drawPath(*dot);
        this->paintGL();

    }
}

//void TunnelW::startGame(Level l)
//{
//    level = l;
//    started = true;
//    createScene(ui->view->size().width(), ui->view->size().height());
//    walls = new MovingPolygons(shared, pMove, shared.scene);
//    score = new Score(shared, shared.scene);
//    screen = new EndScreen(shared, this, level);
//    dot = shared.scene->addEllipse(
//                    shared.scene->width()/2-10,//x
//                    ((walls->getSize() - 4)
//                     *shared.pHeight)-shared.pHeight/2-10,//y
//                    DOT_DIAMETER, //width
//                    DOT_DIAMETER, //height
//                    QPen(Qt::blue), //outline
//                    QBrush(Qt::blue));//fill
//    Share::isPaused = false;
//    moveLeft = false;
//    moveRight = false;
//    frameTimer = startTimer(600/FRAMES_PER_SECOND);
//}

void Tunnel::restartGame()
{
//    cleanShared();
    delete score;
    delete screen;
    delete walls;
    runGame(level);
}

void Tunnel::cleanShared()
{
//    delete shared.scene;
}

void Tunnel::keyPressEvent(QKeyEvent *event)
{
    if(!Share::isPaused) {
        if(event->key() == Qt::Key_Comma ||
                event->key() == Qt::Key_Left ||
                event->key() == Qt::Key_A) {
                    moveLeft = true;
        }
        else if(event->key() == Qt::Key_Period ||
                event->key() == Qt::Key_Right ||
                event->key() == Qt::Key_D){
            moveRight = true;
        }
    }
}

void Tunnel::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Comma ||
            event->key() == Qt::Key_Left ||
            event->key() == Qt::Key_A) {
        moveLeft = false;
    }
    else if(event->key() == Qt::Key_Period ||
            event->key() == Qt::Key_Right ||
            event->key() == Qt::Key_D){
        moveRight = false;
    }
}

/*
 * Updates the dot every frame
 */
//void TunnelW::timerEvent(QTimerEvent *)
//{
//    if(!Share::isPaused) {
////        walls->tick();//moves wall
//        if(moveLeft) dot->moveBy(-dMove,0);
//        else if(moveRight) dot->moveBy(dMove,0);
//        if(dot->collidesWithItem(walls->getCurrentBlock().left) ||
//                dot->collidesWithItem(walls->getNextBlock().left) ||
//                dot->collidesWithItem(walls->getCurrentBlock().right) ||
//                dot->collidesWithItem(walls->getNextBlock().right)) {
//            endGame();
//        }
//    }
//}

void Tunnel::endGame()
{
    killTimer(frameTimer);
    walls->killTime();
    score->killTime();
    screen->exec();
}

int Tunnel::getScore()
{
    return score->getScore();
}

void Tunnel::setPHeight(int h)
{
    shared.pHeight = h;
}

double Tunnel::getPMove()
{
    return pMove;
}

void Tunnel::setPMove(double m)
{
    pMove = m;
}

double Tunnel::getDMove()
{
    return dMove;
}

void Tunnel::setDMove(double m)
{
    dMove = m;
}

bool Tunnel::hasStarted()
{
    return started;
}
