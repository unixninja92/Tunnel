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
#include <sstream>

TunnelW::TunnelW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TunnelW)
{
    ui->setupUi(this);
    ui->view->setRenderHint(QPainter::Antialiasing);
    createScene(ui->view->size().width(), ui->view->size().height());
    startGame();
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
    shared.walls = new MovingPolygons(shared, shared.scene);
    shared.score = new Score(shared, shared.scene);
    shared.screen = new EndScreen(shared, this);
    shared.dot = new Dot(shared, this);
//    qDebug() << "HI!!";
}

void TunnelW::restartGame()
{
    cleanShared();
    createScene(ui->view->size().width(), ui->view->size().height());
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


Dot::Dot(share s, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    dot =  (shared.scene->addEllipse(shared.scene->width()/2-10,
                            ((shared.walls->getSize() - 4)*POLYGON_HEIGHT)-POLYGON_HEIGHT/2-10,
                            20, 20, QPen(Qt::blue),QBrush(Qt::blue)));
    left = false;
    right = false;
    timer = startTimer(20);
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



MovingPolygons::MovingPolygons(share s, QObject *parent) :
    QObject(parent)
{
    shared = s;
    sceneWidth = shared.scene->width();
    sceneMidWidth = sceneWidth/2;
    sceneHeight = shared.scene->height();
//    array = new PolygonArray(sceneHeight/POLYGON_HEIGHT+3);//+3 so two blocks are always off screen
    size = sceneHeight/POLYGON_HEIGHT+3;
    queue = *new QList<polygonBlock>();
    for(int i = 0; i < size; i++){
        queue.append(generateStraightCenterPolyBlock(i-1));
//        array->set(generateStraightCenterPolyBlock(i-1), i);
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
    return queue.at(size-4);//array->get(size-4);
}

polygonBlock MovingPolygons::getNextBlock()
{
    return queue.at(size-5);//array->get(size-5);
}

void MovingPolygons::rotate()
{
//    array->rotate(generateStraightCenterPolyBlock(-1));
//    array->rotate(generateRandomPolyBlock());
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
//            array->get(i).left->moveBy(0,1);
//            array->get(i).right->moveBy(0,1);
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

Score::Score(share s, QObject *parent) :
    QObject(parent)
{
    shared = s;
    score = 0;
    scoreKeeper = shared.scene->addSimpleText(" ");
    scoreKeeper->setPos(shared.scene->width()-30, 20);
    scoreKeeper->setBrush(Qt::white);
    scoreKeeper->setZValue(1);
    updateScore();
    scoreTimer = startTimer(1000);
}

void Score::updateScore()
{
    std::stringstream out;
    out << score;
    scoreKeeper->setText(QString::fromStdString(out.str()));
}

void Score::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==scoreTimer){
        score++;
        updateScore();
    }
}

void Score::killTime()
{
    killTimer(scoreTimer);
}

int Score::getScore()
{
    return score;
}

EndScreen::EndScreen(share s, TunnelW* t, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    tun = t;
    endBox = new QMessageBox(this);
    endBox->setText("Score ");
    again = endBox->addButton("Play again", QMessageBox::ResetRole);
}

void EndScreen::exec()
{
    endBox->exec();
    if(endBox->clickedButton() == again){
        tun->restartGame();
    }
}
