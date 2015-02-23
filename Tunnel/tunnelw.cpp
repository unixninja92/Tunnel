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
//    cleanShared();
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
    shared.walls = new MovingPolygons(shared, pSpeed, pMove, shared.scene);
    shared.score = new Score(shared, shared.scene);
    shared.screen = new EndScreen(shared, this);
    shared.dot = new Dot(shared, dSpeed*.5, dMove, this);
//    qDebug() << "HI!!";
}

void TunnelW::restartGame()
{
    cleanShared();
    startGame();
}

void TunnelW::cleanShared()
{
    delete shared.scene;
    delete shared.score;
    delete shared.screen;
    delete shared.walls;
    delete shared.dot;
}

void TunnelW::keyPressEvent(QKeyEvent *event)
{
    QApplication::sendEvent(shared.dot, event);
}

void TunnelW::keyReleaseEvent(QKeyEvent *event)
{
    QApplication::sendEvent(shared.dot, event);
}

int TunnelW::getScore()
{
    return shared.score->getScore();
}

int TunnelW::getPSpeed()
{
    return pSpeed;
}

void TunnelW::setPSpeed(int s)
{
    pSpeed = s;
}

int TunnelW::getDSpeed()
{
    return dSpeed;
}

void TunnelW::setDSpeed(int s)
{
    dSpeed = s;
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
