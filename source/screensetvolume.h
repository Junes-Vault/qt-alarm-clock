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
 * Set volume screen
*/

#ifndef SCREENSETVOLUME_H
#define SCREENSETVOLUME_H

#include <QWidget>

namespace Ui
{
    class ScreenSetVolume;
}

class ScreenSetVolume : public QWidget
{
    Q_OBJECT
signals:
    //volume changed
    void volumeChanged(int value);

    // done clicked
    void doneBtnClicked();

public:
    ScreenSetVolume(int& volume,
                    QWidget* parent = 0);
    ~ScreenSetVolume();

    // send back volume
    int getVolume();

public slots:
    // set volume
    void setVolume(int value);

    // Update volume controls
    void updateVolume();

private slots:
    // Stuff was moved or pressed
    void on_volumeKnob_valueChanged(int value);
    void on_doneBtn_clicked();

private:
    Ui::ScreenSetVolume* ui;
    int& volume;
};

#endif // SCREENSETVOLUME_H
