/*
    Copyright 2013 June Hanabi

    This file is part of AlarmClock.

    AlarmClock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AlarmClock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * The about screen
*/

#ifndef SCREENABOUT_H
#define SCREENABOUT_H

#include <QWidget>

namespace Ui
{
    class ScreenAbout;
}

class ScreenAbout : public QWidget
{
    Q_OBJECT
signals:
    // Notify that the done button was clicked
    void doneBtnClicked();

public:
    ScreenAbout(QWidget* parent = 0);
    ~ScreenAbout();

public slots:
    // Replace any variables in the description
    // that need to be replaced at run-time
    void updateReplacement();

private slots:
    // Done button was clicked
    void on_doneBtn_clicked();

private:
    Ui::ScreenAbout* ui;
};

#endif // SCREENABOUT_H
