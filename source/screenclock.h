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
 * The clock screen, aka "main screen", "home screen", or "opening screen"
*/

#ifndef SCREENCLOCK_H
#define SCREENCLOCK_H

#include "clock.h"

#include <QWidget>
#include <QTime>

namespace Ui
{
    class ScreenClock;
}

class ScreenClock : public QWidget
{
    Q_OBJECT
signals:
    // Buttons being clicked
    void aboutBtnClicked();
    void volumeBtnClicked();
    void setupBtnClicked();
    void alarmSnoozeBtnClicked();
    void alarmEnableBtnClicked();

    // Stuff changing
    void alarmTimeChanged(QTime value);
    void clockTimeChanged(QTime value);
    void alarmEnabledChanged(bool value);

public:
    ScreenClock(QTime& alarmTime,
                QTime& clockTime,
                bool& alarmEnabled,
                Clock& timeConverter,
                bool& tick,
                QWidget* parent = 0);
    ~ScreenClock();

    // Get stuff
    QTime getAlarmTime();
    QTime getClockTime();
    bool isAlarmEnabled();

public slots:
    // Set stuff
    void setAlarmTime(QTime time);
    void setAlarmEnabled(bool enabled = true);

    // Render stuff
    void updateAlarmTime();
    void updateClockTime();
    void alarmSnoozeEnabled(bool enabled);
    void alarmSetToggle(bool toggle);

private slots:
    // Stuff being clicked
    void on_aboutBtn_clicked();
    void on_volumeBtn_clicked();
    void on_setAlarmBtn_clicked();
    void on_snoozeBtn_clicked();
    void on_alarmEnableBtn_clicked();

private:
    // References to the global memory
    Ui::ScreenClock* ui;
    QTime& alarmTime;
    QTime& clockTime;
    bool& alarmEnabled;
    Clock& timeConverter;
    bool& tick;
};

#endif // SCREENCLOCK_H
