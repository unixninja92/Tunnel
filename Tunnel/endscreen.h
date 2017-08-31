/*
 *  Tunnel Copyright 2015 unixninja92
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  @author unixninja92
 */
#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QObject>
#include <QWidget>
#include <shared.h>
#include <tunnelw.h>

/*
 *  EndScreen is a popup box that apears when the user has died/crashed into a
 *  wall giving them the option to either play again on the same dificulty or
 *  be taken back to the main menu.
 */
class EndScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndScreen(share, TunnelW*, Level, QWidget *parent=0);
    void exec();

private:
    share shared;
    Level level;
    QPointer<QMessageBox> endBox;
    QPointer<QAbstractButton> menuButton;
    QPointer<QAbstractButton> againButton;
    QPointer<TunnelW> tun;
    QSettings settings;
};

#endif // ENDSCREEN_H
