#include "endscreen.h"

EndScreen::EndScreen(share s, TunnelW* t, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    tun = t;
    endBox = new QMessageBox(this);
    endBox->setText("Score ");
    again = endBox->addButton("Play again", QMessageBox::ResetRole);
}

void EndScreen::exec()
{
    endBox->exec();
    if(endBox->clickedButton() == again){
        tun->restartGame();
    }
}

