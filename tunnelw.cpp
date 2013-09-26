#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

TunnelW::TunnelW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TunnelW)
{
    ui->setupUi(this);
    ui->view->setRenderHint(QPainter::Antialiasing);
    createScene(ui->view->size().width(), ui->view->size().height());
    polyBlocks = new MovingPolygons(scene, dot);
    drawDot();
    left = false;
    right = false;
    startTimer(10);
}

TunnelW::~TunnelW()
{
    delete ui;
}

void TunnelW::createScene(int w, int h)
{
    scene = new QGraphicsScene;
    ui->view->setScene(scene);
    scene->setSceneRect(0,0,w-2,h-2);
    scene->setBackgroundBrush(Qt::gray);
}

void TunnelW::drawDot()
{
    dot = scene->addEllipse(scene->width()/2-10,
                            ((polyBlocks->getSize() - 4)*POLYGON_HEIGHT)-POLYGON_HEIGHT/2-10,
                            20, 20, QPen(Qt::blue),QBrush(Qt::blue));
}

void TunnelW::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Comma) {
        left = true;
//        if(!dot->collidesWithItem(polyBlocks->getCurrentBlock().left) && !dot->collidesWithItem(polyBlocks->getNextBlock().left)){
//            dot->moveBy(-3,0);
//        }
    }
    else if(event->key() == Qt::Key_Period){
        right = true;
//        if(!dot->collidesWithItem(polyBlocks->getCurrentBlock().right) && !dot->collidesWithItem(polyBlocks->getNextBlock().right)){
//            dot->moveBy(3,0);
//        }
    }
}

void TunnelW::keyReleaseEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_0) {
        polyBlocks->getCurrentBlock().left->moveBy(0,20);
        polyBlocks->getCurrentBlock().right->moveBy(0,20);
//        if(leftFlatSide.isClosed()) dot->moveBy(0,10);
    }
    else if(event->key() == Qt::Key_1){
//        polyBlocks->startTime();
//        QTimer timer;
//       QObject::connect(&timer, SIGNAL(timeout()),SLOT(update());
//        timer.start(100);
    }
    else if(event->key() == Qt::Key_Comma) {
        left = false;
    }
    else if(event->key() == Qt::Key_Period){
        right = false;
    }
}

void TunnelW::timerEvent(QTimerEvent *event)
{
    if(left) dot->moveBy(-1,0);
    else if(right) dot->moveBy(1,0);
    if(dot->collidesWithItem(polyBlocks->getCurrentBlock().left) ||
            dot->collidesWithItem(polyBlocks->getNextBlock().left) ||
            dot->collidesWithItem(polyBlocks->getCurrentBlock().right) ||
            dot->collidesWithItem(polyBlocks->getNextBlock().right)) {
        killTimer(event->timerId());
        polyBlocks->killTime();
    }
}
