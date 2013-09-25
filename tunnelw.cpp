#include "tunnelw.h"
#include "ui_tunnelw.h"
#include <QGraphicsRectItem>

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
    scene->setSceneRect(0,0,w,h);
}

void TunnelW::drawDot()
{
    dot = scene->addEllipse(290, 390, 20, 20, QPen(Qt::blue),QBrush(Qt::blue));

}

void TunnelW::keyPressEvent(QKeyEvent *event)
{
    
}
