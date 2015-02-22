#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QObject>
#include <QWidget>
#include <shared.h>
#include <tunnelw.h>


class EndScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndScreen(share, TunnelW*, QWidget *parent=0);
    void exec();

private:
    share shared;
    QPointer<QMessageBox> endBox;
    QPointer<QAbstractButton> menu;
    QPointer<QAbstractButton> again;
    QPointer<TunnelW> tun;
};

#endif // ENDSCREEN_H
