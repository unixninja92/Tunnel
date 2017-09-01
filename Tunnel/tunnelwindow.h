#ifndef TUNNELWINDOW_H
#define TUNNELWINDOW_H

#include <QWidget>
#include <shared.h>
#include <tunnel.h>

namespace Ui {
class TunnelWindow;
}

class TunnelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TunnelWindow(QWidget *parent = 0);
    ~TunnelWindow();
    Tunnel *tunnel;

private:
    Ui::TunnelWindow *ui;
};

#endif // TUNNELWINDOW_H
