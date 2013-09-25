#ifndef TUNNELW_H
#define TUNNELW_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class TunnelW;
}

class TunnelW : public QWidget
{
    Q_OBJECT

public:
    explicit TunnelW(QWidget *parent = 0);
    ~TunnelW();
    void drawDot();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);


private:
    Ui::TunnelW *ui;
    QGraphicsEllipseItem* dot;
    QGraphicsScene* scene;
    void createScene(int w, int h);
};

#endif // TUNNELW_H
