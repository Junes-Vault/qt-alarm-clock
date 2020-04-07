/*
    Copyright 2013 June Hanabi

    This file is part of AlarmClock.

    AlarmClock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * The single program window
*/

#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

signals:
    // Screen changed
    void screenChanged(QWidget* screen);

public:
    Window(QWidget*& switchBackScreen, QWidget* parent = 0);
    ~Window();

    // get screen
    QWidget* getScreen();

public slots:
    // change screen
    void setScreen(QWidget* widget);

    // previous screen
    void goBackScreen();

private:
    Ui::Window* ui;

    // previous widget
    QWidget*& switchBackScreen;
};

#endif // WINDOWMAIN_H
