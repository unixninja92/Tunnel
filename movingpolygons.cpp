#include "movingpolygons.h"
#include <QVector>
#include <QTime>


MovingPolygons::MovingPolygons(QGraphicsScene* s, QGraphicsEllipseItem* d, QObject *parent) :
    QObject(parent)
{
    scene = s;
    dot = d;
    sceneWidth = scene->width();
    sceneMidWidth = sceneWidth/2;
    sceneHeight = scene->height();
    array = new PolygonArray(sceneHeight/POLYGON_HEIGHT+3);//+3 so two blocks are always off screen
    size = array->getSize();
    color = false;
    for(int i = 0; i < size; i++){
        array->set(generateStraightCenterPolyBlock(i-1), i);
    }
    count = 0;
    timer = startTimer(40);
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
    else{
        rand = qrand()%((int)sceneWidth-TUNNEL_WIDTH -20)+10;
    }

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

    newBlock.left = scene->addPolygon(left);
    newBlock.left->setBrush(Qt::black);

    newBlock.right = scene->addPolygon(right);
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

void MovingPolygons::timerEvent(QTimerEvent *event)
{
    for(int i = 0; i<size; i++){
        array->get(i).left->moveBy(0,1);
        array->get(i).right->moveBy(0,1);
    }
    count++;
    if(count%75==0) rotate();
}

void MovingPolygons::killTime()
{
    killTimer(timer);
}

int MovingPolygons::getSize()
{
    return size;
}


