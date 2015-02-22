/*
 *Copyright 2013 unixninja92
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
#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QDebug>

TunnelW::TunnelW(QWidget *parent) :
    QWidget(parent),
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
    shared.walls = new MovingPolygons(shared, speed, shared.scene);
    shared.score = new Score(shared, shared.scene);
    shared.screen = new EndScreen(shared, this);
    shared.dot = new Dot(shared, speed*.5, this);
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

int TunnelW::getSpeed()
{
    return speed;
}

void TunnelW::setSpeed(int s)
{
    speed = s;
}

bool TunnelW::hasStarted()
{
    return started;
}
