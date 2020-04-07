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
 * The set alarm screen
*/

#ifndef SCREENSETALARM_H
#define SCREENSETALARM_H

#include "clock.h"

#include <QWidget>
#include <QTime>

namespace Ui
{
    class ScreenSetAlarm;
}

class ScreenSetAlarm : public QWidget
{
    Q_OBJECT
signals:
    // Alarm changes
    void alarmTimeChanged(QTime value);
    void alarmHourChanged(int value);
    void alarmMinuteChanged(int value);
    void alarmPmChanged(int value);
    void alarmEnabledChanged(bool value);

    // screen buttons pressed
    void doneBtnClicked();
    void volumeBtnClicked();

public:
    ScreenSetAlarm(QTime& alarmTime,
                   bool& alarmEnabled,
                   Clock& timeConverter,
                   QWidget* parent = 0);
    ~ScreenSetAlarm();

    // Get and test stuff
    QTime getAlarmTime();
    int getAlarmHour();
    int getAlarmMinute();
    bool isAlarmPm();
    bool isAlarmEnabled();

public slots:
    // set stuff
    void setAlarmTime(QTime time);
    void setAlarmHour(int hour = 12);
    void setAlarmMinute(int minute = 0);
    void setAlarmPm(bool pm = true);
    void setAlarmEnabled(bool set = true);

    // re-render
    void reUpdateControls();

private slots:
    // buttons and stuff were pressed or moved
    void on_hourSlider_valueChanged(int value);
    void on_minuteSlider_valueChanged(int value);
    void on_setBtn_clicked();
    void on_amPmBtn_clicked();
    void on_doneBtn_clicked();
    void on_add0015Btn_clicked();
    void on_add0030Btn_clicked();
    void on_add0100Btn_clicked();
    void on_add0200Btn_clicked();
    void on_add0500Btn_clicked();
    void on_add0800Btn_clicked();
    void on_min00Btn_clicked();
    void on_min15Btn_clicked();
    void on_min30Btn_clicked();
    void on_min45Btn_clicked();
    void on_volumeBtn_clicked();

    void on_nowBtn_clicked();

private:
    Ui::ScreenSetAlarm* ui;
    QTime& alarmTime;
    bool& alarmEnabled;
    Clock& timeConverter;
};

#endif // SCREENSETALARM_H
