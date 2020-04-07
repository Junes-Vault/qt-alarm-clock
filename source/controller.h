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
 * Provides the controller to the alarm clock in
 * a model/view/controller manner
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "globalmemory.h"

class Controller : public QObject
{
    Q_OBJECT

public slots:
    // Screen Switching
    void switchToScreenAbout();
    void switchToScreenClock();
    void switchToScreenSetAlarm();
    void switchToScreenVolume();

    // Alarm Control
    void stopAlarm();
    void startAlarm();

public:
    Controller(QObject* parent = 0);
    ~Controller();

private slots:
    // Ticks
    void clockTick();
    void bgTick(); // Planned to be used in a future update

    // Alarm Control
    void alarmStateChange(QMediaPlayer::State state);
    void alarmCheck(bool ignoreTrigger = false);
    void alarmStopCheck();
    void alarmSnooze();
    void alarmEnableToggle();

    // Volume Control
    void changeVolume(int value);

    // Settings control
    void save();
    void restore();
    
    // Player Control
    void playerError(QMediaPlayer::Error error);

private:
    // The memory for the alarm
    // It's a global variable for simplistic,
    // for model (in MVC style), and to keep unneded extra
    // memory down to a minimum
    GlobalMemory* memory;
};

#endif // CONTROLLER_H
