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
 * The global memory
 * This only stores the memory, it doesnt contain any control or setup
 * logic at all
*/

#ifndef GLOBALMEMORY_H
#define GLOBALMEMORY_H

#include "screenabout.h"
#include "screenclock.h"
#include "screensetalarm.h"
#include "screensetvolume.h"
#include "window.h"
#include "clock.h"

#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include <QSettings>
#include <QTime>

class GlobalMemory : public QObject
{
    Q_OBJECT
public:
    static GlobalMemory* getInstance();
    ~GlobalMemory();

    // 1-second timer
    QTimer* timer;

    // Spare-time timer
    QTimer* bgTimer;

    // clock tick
    bool tick;

    // Media player for audio
    QMediaPlayer* player;

    // Alarm tripped
    bool triggered;

    // Registry access
    QSettings* userApplicationSettings;
    QSettings* userOrganizationSettings;
    QSettings* systemApplicationSettings;
    QSettings* systemOrganizationSettings;

    // Screens and the window
    Window* window;
    ScreenAbout* screenAbout;
    ScreenClock* screenClock;
    ScreenSetAlarm* screenSetAlarm;
    ScreenSetVolume* screenSetVolume;

    // The screen to switch back to
    QWidget* switchBackScreen;

    // alarm and clock time
    QTime alarmTime;
    QTime clockTime;
    bool alarmEnabled;
    Clock timeConverter;

    // volume
    int volume;

private:
    GlobalMemory(QObject* parent = 0);
    static GlobalMemory* instance;
};

#endif // GLOBALMEMORY_H
