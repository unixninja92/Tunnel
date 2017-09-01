#include "tunnelwindow.h"
#include "ui_tunnelwindow.h"

TunnelWindow::TunnelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TunnelWindow)
{
    ui->setupUi(this);
    tunnel = new Tunnel();
}

TunnelWindow::~TunnelWindow()
{
    delete ui;
}
