#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QDebug>
#include <QApplication>
#include <QVector>
#include <QTime>
#include <QString>
#include <sstream>

TunnelW::TunnelW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TunnelW)
{
    ui->setupUi(this);
    ui->view->setRenderHint(QPainter::Antialiasing);
    createScene(ui->view->size().width(), ui->view->size().height());
    shared.scene->setBackgroundBrush(Qt::gray);
    startGame();
}

TunnelW::~TunnelW()
{
    delete ui;
}

void TunnelW::createScene(int w, int h)
{
    shared.scene = new QGraphicsScene();
    ui->view->setScene(shared.scene);
    shared.scene->setSceneRect(0,0,w-2,h-2);
}

void TunnelW::startGame()
{
    shared.walls = new MovingPolygons(shared);
    shared.score = new Score(shared);
    shared.dot = new Dot(shared, this);
//    qDebug() << "HI!!";
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
    dot = shared.scene->addEllipse(shared.scene->width()/2-10,
                            ((shared.walls->getSize() - 4)*POLYGON_HEIGHT)-POLYGON_HEIGHT/2-10,
                            20, 20, QPen(Qt::blue),QBrush(Qt::blue));
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
    }
}



MovingPolygons::MovingPolygons(share s, QObject *parent) :
    QObject(parent)
{
    shared = s;
    sceneWidth = shared.scene->width();
    sceneMidWidth = sceneWidth/2;
    sceneHeight = shared.scene->height();
    array = new PolygonArray(sceneHeight/POLYGON_HEIGHT+3);//+3 so two blocks are always off screen
    size = array->getSize();
    for(int i = 0; i < size; i++){
        array->set(generateStraightCenterPolyBlock(i-1), i);
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
    return array->get(size-4);
}

polygonBlock MovingPolygons::getNextBlock()
{
    return array->get(size-5);
}

void MovingPolygons::rotate()
{
//    array->rotate(generateStraightCenterPolyBlock(-1));
    array->rotate(generateRandomPolyBlock());
}

int MovingPolygons::getSize()
{
    return size;
}

void MovingPolygons::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==wallTimer){
        for(int i = 0; i<size; i++){
            array->get(i).left->moveBy(0,1);
            array->get(i).right->moveBy(0,1);
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

EndScreen::EndScreen(share s, QWidget *parent) :
    QWidget(parent)
{
    shared = s;

}
