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
#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QDebug>

bool Share::isPaused = false;

TunnelW::TunnelW(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::TunnelW)
{
    ui->setupUi(this);
    ui->view->setRenderHint(QPainter::Antialiasing);
    started = false;
}

TunnelW::~TunnelW()
{
    delete ui;
}

void TunnelW::createScene(int w, int h)
{
    shared.scene = new QGraphicsScene(this);
    ui->view->setScene(shared.scene);
    shared.scene->setSceneRect(0,0,w-2,h-2);
    shared.scene->setBackgroundBrush(Qt::gray);
}

void TunnelW::startGame()
{
    started = true;
    createScene(ui->view->size().width(), ui->view->size().height());
    walls = new MovingPolygons(shared, pMove, shared.scene);
    score = new Score(shared, shared.scene);
    screen = new EndScreen(shared, this);
    dot = shared.scene->addEllipse(
                    shared.scene->width()/2-10,//x
                    ((walls->getSize() - 4)
                     *shared.pHeight)-shared.pHeight/2-10,//y
                    DOT_DIAMETER, //width
                    DOT_DIAMETER, //height
                    QPen(Qt::blue), //outline
                    QBrush(Qt::blue));//fill
    Share::isPaused = false;
    moveLeft = false;
    moveRight = false;
    frameTimer = startTimer(1000/FRAMES_PER_SECOND);
}

void TunnelW::restartGame()
{
    cleanShared();
    delete score;
    delete screen;
    delete walls;
    startGame();
}

void TunnelW::cleanShared()
{
    delete shared.scene;
}

void TunnelW::keyPressEvent(QKeyEvent *event)
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

void TunnelW::keyReleaseEvent(QKeyEvent *event)
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
 * Updates the screen every frame
 */
void TunnelW::timerEvent(QTimerEvent *)
{
    if(!Share::isPaused) {
//        walls->tick();//moves wall
        if(moveLeft) dot->moveBy(-dMove,0);
        else if(moveRight) dot->moveBy(dMove,0);
        if(dot->collidesWithItem(walls->getCurrentBlock().left) ||
                dot->collidesWithItem(walls->getNextBlock().left) ||
                dot->collidesWithItem(walls->getCurrentBlock().right) ||
                dot->collidesWithItem(walls->getNextBlock().right)) {
            killTimer(frameTimer);
            walls->killTime();
            score->killTime();
            screen->exec();
        }
    }
}

int TunnelW::getScore()
{
    return score->getScore();
}

void TunnelW::setPHeight(int h)
{
    shared.pHeight = h;
}

double TunnelW::getPMove()
{
    return pMove;
}

void TunnelW::setPMove(double m)
{
    pMove = m;
}

double TunnelW::getDMove()
{
    return dMove;
}

void TunnelW::setDMove(double m)
{
    dMove = m;
}

bool TunnelW::hasStarted()
{
    return started;
}
