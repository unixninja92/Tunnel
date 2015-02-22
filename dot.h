#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QWidget>
#include <shared.h>
#include <movingpolygons.h>
#include <score.h>
#include <endscreen.h>

class Dot : public QWidget
{
    Q_OBJECT
public:
    explicit Dot(share, QWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    share shared;
    QGraphicsEllipseItem* dot;
    bool left;
    bool right;
    int timer;
};

//class Dot : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit Dot(QWidget *parent = 0);
//    ~Dot();

//signals:

//public slots:
//};

#endif // DOT_H
