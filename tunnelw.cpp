#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>

TunnelW::TunnelW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TunnelW)
{
    ui->setupUi(this);
    ui->view->setRenderHint(QPainter::Antialiasing);
    createScene(ui->view->size().width(), ui->view->size().height());
    drawDot();
}

TunnelW::~TunnelW()
{
    delete ui;
}

void TunnelW::createScene(int w, int h)
{
    scene = new QGraphicsScene;
    ui->view->setScene(scene);
    scene->setSceneRect(0,0,w-10,h-10);
    scene->setBackgroundBrush(Qt::gray);
}

void TunnelW::drawDot()
{
    dot = scene->addEllipse(290, 590, 20, 20, QPen(Qt::blue),QBrush(Qt::blue));
}

void TunnelW::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Comma) {
        dot->moveBy(-5,0);
    }
    else if(event->key() == Qt::Key_Period){
        dot->moveBy(5,0);
    }
}

void TunnelW::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Comma) {
    }
    else if(event->key() == Qt::Key_Period){
    }
}
