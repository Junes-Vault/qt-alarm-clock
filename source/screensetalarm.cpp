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

#include "screensetalarm.h"
#include "ui_screensetalarm.h"

ScreenSetAlarm::ScreenSetAlarm(QTime& alarmTime,
                               bool& alarmEnabled,
                               Clock& timeConverter,
                               QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ScreenSetAlarm),
    alarmTime(alarmTime),
    alarmEnabled(alarmEnabled),
    timeConverter(timeConverter)
{
    // Wire ui to class
    ui->setupUi(this);
}

ScreenSetAlarm::~ScreenSetAlarm()
{
    delete ui;
}

// Send back alarm time
// Not used by program, placed here in case used elsewhere
QTime ScreenSetAlarm::getAlarmTime()
{
    return alarmTime;
}

// Send back alarm hour
// Not used by program, placed here in case used elsewhere
int ScreenSetAlarm::getAlarmHour()
{
    timeConverter.parse24Time(alarmTime);
    return timeConverter.hours;
}

// Send back alarm minute
// Not used by program, placed here in case used elsewhere
int ScreenSetAlarm::getAlarmMinute()
{
    timeConverter.parse24Time(alarmTime);
    return timeConverter.minutes;
}

// Send back alarm am or pm
// Not used by program, placed here in case used elsewhere
bool ScreenSetAlarm::isAlarmPm()
{
    timeConverter.parse24Time(alarmTime);
    return timeConverter.pm;
}

// Send back alarm enabled
// Not used by program, placed here in case used elsewhere
bool ScreenSetAlarm::isAlarmEnabled()
{
    return alarmEnabled;
}

// Set alarm time
void ScreenSetAlarm::setAlarmTime(QTime time)
{
    // Make sure we're not assinging the same value
    if(time == alarmTime) return;

    // Assign new value
    alarmTime = time;
    emit alarmTimeChanged(time);

    // Re-Render everything
    reUpdateControls();
}

// Set alarm hour
void ScreenSetAlarm::setAlarmHour(int hour)
{
    // Parse 24 to 12 hour time and make sure it's not the exact same
    timeConverter.parse24Time(alarmTime);
    if(timeConverter.hours == hour) return;

    // Adjust and apply new time and
    timeConverter.hours = hour;
    timeConverter.apply12Time(alarmTime);

    // Notify changes
    emit alarmHourChanged(timeConverter.hours);
    emit alarmTimeChanged(alarmTime);

    // Re-render
    reUpdateControls();
}

// Set alarm minute
void ScreenSetAlarm::setAlarmMinute(int minute)
{
    // Parse 24 to 12 hour time and make sure it's not the exact same
    timeConverter.parse24Time(alarmTime);
    if(timeConverter.minutes == minute) return;

    // Adjust and apply new time and
    timeConverter.minutes = minute;
    timeConverter.apply12Time(alarmTime);

    // Notify changes
    emit alarmMinuteChanged(timeConverter.minutes);
    emit alarmTimeChanged(alarmTime);

    // Re-render
    reUpdateControls();
}

// Set alarm am or pm
void ScreenSetAlarm::setAlarmPm(bool pm)
{
    // Parse 24 to 12 hour time and make sure it's not the exact same
    timeConverter.parse24Time(alarmTime);
    if(timeConverter.pm == pm) return;

    // Adjust and apply new time and
    timeConverter.pm = pm;
    timeConverter.apply12Time(alarmTime);

    // Notify changes
    emit alarmPmChanged(pm);
    emit alarmTimeChanged(alarmTime);

    // Re-render
    reUpdateControls();
}

// Set alarm enabled or not
void ScreenSetAlarm::setAlarmEnabled(bool set)
{
    // Make sure a different value
    if(alarmEnabled == set) return;

    // Assign and notify changes
    alarmEnabled = set;
    emit alarmEnabledChanged(alarmEnabled);

    // Re-render
    reUpdateControls();
}

// Re-render or refresh all controls and displays
void ScreenSetAlarm::reUpdateControls()
{
    // parse time
    timeConverter.parse24Time(alarmTime);

    // Set the hour slider and LCD
    ui->hourSlider->setValue(timeConverter.hours);
    ui->hourDisplay->display(timeConverter.hours);

    // Prepare a leading 0 for the minute LCD
    QString minutes = QString::number(timeConverter.minutes);
    if(timeConverter.minutes < 10) minutes.prepend("0");

    // Set the minute slider and LCD
    ui->minuteSlider->setValue(timeConverter.minutes);
    ui->minuteDisplay->display(minutes);

    // Set the am / pm button checked accordingly
    ui->amPmBtn->setChecked(timeConverter.pm);

    // set the text accordingly
    if(timeConverter.pm)
    {
        //ui->amPmBtn->setChecked(true);
        ui->amPmBtn->setText("PM");
    }
    else
    {
        //ui->amPmBtn->setChecked(false);
        ui->amPmBtn->setText("AM");
    }

    // Set the set button accordingly
    ui->setBtn->setChecked(alarmEnabled);
}

// Hour slider changed
void ScreenSetAlarm::on_hourSlider_valueChanged(int value)
{
    setAlarmHour(value);
}

// Minute slider changed
void ScreenSetAlarm::on_minuteSlider_valueChanged(int value)
{
    setAlarmMinute(value);
}

// Set button clicked
void ScreenSetAlarm::on_setBtn_clicked()
{
    setAlarmEnabled(ui->setBtn->isChecked());
}

// Am or Pm button clicked
void ScreenSetAlarm::on_amPmBtn_clicked()
{
    setAlarmPm(ui->amPmBtn->isChecked());
}

// Done button pressed
void ScreenSetAlarm::on_doneBtn_clicked()
{
    emit doneBtnClicked();
}

void ScreenSetAlarm::on_add0015Btn_clicked()
{
    int seconds = 15 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_add0030Btn_clicked()
{
    int seconds = 30 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_add0100Btn_clicked()
{
    int seconds = 1 * 60 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_add0200Btn_clicked()
{
    int seconds = 2 * 60 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_add0500Btn_clicked()
{
    int seconds = 5 * 60 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_add0800Btn_clicked()
{
    int seconds = 8 * 60 * 60;
    QTime newTime = alarmTime.addSecs(seconds);
    setAlarmTime(newTime);
}

void ScreenSetAlarm::on_min00Btn_clicked()
{
    setAlarmMinute(0);
    reUpdateControls();
}

void ScreenSetAlarm::on_min15Btn_clicked()
{
    setAlarmMinute(15);
    reUpdateControls();
}

void ScreenSetAlarm::on_min30Btn_clicked()
{
    setAlarmMinute(30);
    reUpdateControls();
}

void ScreenSetAlarm::on_min45Btn_clicked()
{
    setAlarmMinute(45);
    reUpdateControls();
}

void ScreenSetAlarm::on_volumeBtn_clicked()
{
    emit volumeBtnClicked();
}

void ScreenSetAlarm::on_nowBtn_clicked()
{
    setAlarmTime(QTime::currentTime());
}
