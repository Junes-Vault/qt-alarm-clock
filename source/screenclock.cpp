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

#include "screenclock.h"
#include "ui_screenclock.h"

ScreenClock::ScreenClock(QTime& alarmTime,
                         QTime& clockTime,
                         bool& alarmEnabled,
                         Clock& timeConverter,
                         bool& tick,
                         QWidget* parent):
    QWidget(parent),
    ui(new Ui::ScreenClock),
    alarmTime(alarmTime),
    clockTime(clockTime),
    alarmEnabled(alarmEnabled),
    timeConverter(timeConverter),
    tick(tick)
{
    // Wire ui to class
    ui->setupUi(this);
}

ScreenClock::~ScreenClock()
{
    delete ui;
}

// Send back alarm time
// Not used by program, placed here in case used elsewhere
QTime ScreenClock::getAlarmTime()
{
    return alarmTime;
}

// Send back clock time
// Not used by program, placed here in case used elsewhere
QTime ScreenClock::getClockTime()
{
    return clockTime;
}

// Set alarm time
// Not used by program, placed here in case used elsewhere
void ScreenClock::setAlarmTime(QTime time)
{
    // If this isnt a new time then don't do anything
    if(time == alarmTime) return;

    // Change time
    alarmTime = time;
    emit alarmTimeChanged(alarmTime);

    // Render updates
    updateAlarmTime();
}

// Render alarm updates
void ScreenClock::updateAlarmTime()
{
    // Get 12 hour alarm time
    timeConverter.parse24Time(alarmTime);
    QString display = QString::number(timeConverter.hours) + ":";

    // Tack on the minutes
    if(timeConverter.minutes < 10) display += "0";
    display += QString::number(timeConverter.minutes);

    // Send this to the alarm LCD
    ui->alarmDisplay->display(display);

    // Is it am or pm
    // Toggle and set am/pm button accordingly
    if(timeConverter.pm)
    {
        ui->alarmAmPmBtn->setText("PM");
        ui->alarmAmPmBtn->setChecked(true);
    }
    else
    {
        ui->alarmAmPmBtn->setText("AM");
        ui->alarmAmPmBtn->setChecked(false);
    }

    // Update the alarm box
    ui->alarmDisplay->setEnabled(alarmEnabled);
    alarmSetToggle(alarmEnabled);
}

// Render Clock Updates
void ScreenClock::updateClockTime()
{
    // Parse time
    // Since this is a class to the view, the time isnt stored here
    // the view only displays the time fed to it
    timeConverter.parse24Time(clockTime);

    // Tack on the hours
    QString display = QString::number(timeConverter.hours);

    // Tack on the colon sign for the blinking effect
    if(tick) display += ":";
    else display+= " ";

    // Tack on minutes with leading 0
    if(timeConverter.minutes < 10) display += "0";
    display += QString::number(timeConverter.minutes);

    // Show final string
    ui->clockDisplay->display(display);

    // Set am/pm button accordingly
    if(timeConverter.pm)
    {
        ui->clockAmPmBtn->setChecked(true);
        ui->clockAmPmBtn->setText("PM");
    }
    else
    {
        ui->clockAmPmBtn->setChecked(false);
        ui->clockAmPmBtn->setText("AM");
    }
}

// Change alarm enabled or not
// This method isn't used by this program but is placed here in case used elsewhere
void ScreenClock::setAlarmEnabled(bool enabled)
{
    // If nothing will change then dont do anything
    if(enabled == alarmEnabled) return;

    // Set new enabled status
    alarmEnabled = enabled;
    emit alarmEnabledChanged(alarmEnabled);

    // Show enabled
    ui->alarmBox->setEnabled(enabled);
}

// Send back enabled or not
// This method isn't used by this program but is placed here in case used elsewhere
bool ScreenClock::isAlarmEnabled()
{
    return alarmEnabled;
}

// About button clicked
void ScreenClock::on_aboutBtn_clicked()
{
    emit aboutBtnClicked();
}

// Volume button clicked
void ScreenClock::on_volumeBtn_clicked()
{
    emit volumeBtnClicked();
}

// Alarm button clicked
void ScreenClock::on_setAlarmBtn_clicked()
{
    emit setupBtnClicked();
}

void ScreenClock::alarmSnoozeEnabled(bool enabled)
{
    ui->snoozeBtn->setEnabled(enabled);
    ui->snoozeBtn->setChecked(enabled);
}

void ScreenClock::alarmSetToggle(bool toggle)
{
    ui->alarmEnableBtn->setChecked(toggle);
}

void ScreenClock::on_snoozeBtn_clicked()
{
    emit alarmSnoozeBtnClicked();
}

void ScreenClock::on_alarmEnableBtn_clicked()
{
    emit alarmEnableBtnClicked();
}
