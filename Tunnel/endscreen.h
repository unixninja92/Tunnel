/*
 *Copyright 2015 unixninja92
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
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