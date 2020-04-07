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

#include "controller.h"

#include <QApplication>
#include <QDebug>
#include <QFile>

Controller::Controller(QObject *parent) :
    QObject(parent),

    // Get the global memory
    memory(GlobalMemory::getInstance())
{
    // About screen connections
    // Done Button -> Clock Screen
    connect(memory->screenAbout, SIGNAL(doneBtnClicked()), this, SLOT(switchToScreenClock()));

    // Clock Screen connections
    // About Button -> About Screen
    // Volume Button -> Volume Screen
    // Setup Button -> Setup Screen
    connect(memory->screenClock, SIGNAL(aboutBtnClicked()), this, SLOT(switchToScreenAbout()));
    connect(memory->screenClock, SIGNAL(volumeBtnClicked()), this, SLOT(switchToScreenVolume()));
    connect(memory->screenClock, SIGNAL(setupBtnClicked()), this, SLOT(switchToScreenSetAlarm()));
    connect(memory->screenClock, SIGNAL(alarmSnoozeBtnClicked()), this, SLOT(alarmSnooze()));
    connect(memory->screenClock, SIGNAL(alarmEnableBtnClicked()), this, SLOT(alarmEnableToggle()));
    connect(memory->screenClock, SIGNAL(alarmTimeChanged(QTime)), this, SLOT(save()));

    // Alarm setup screen connections
    // Done Button -> Clock Screen
    // [Alarm Am/Pm Change] -> if alarm is playing check whether its needed to stop playing
    // [Alarm Enabled Change] -> Make sure that the alarm has stopped
    // [Alarm time change] -> if alarm is playing check whether its needed to stop playing
    connect(memory->screenSetAlarm, SIGNAL(doneBtnClicked()), this, SLOT(switchToScreenClock()));
    connect(memory->screenSetAlarm, SIGNAL(volumeBtnClicked()), this, SLOT(switchToScreenVolume()));
    connect(memory->screenSetAlarm, SIGNAL(alarmPmChanged(int)), this, SLOT(alarmStopCheck()));
    connect(memory->screenSetAlarm, SIGNAL(alarmEnabledChanged(bool)), this, SLOT(stopAlarm()));
    connect(memory->screenSetAlarm, SIGNAL(alarmTimeChanged(QTime)), this, SLOT(alarmStopCheck()));
    connect(memory->screenSetAlarm, SIGNAL(alarmTimeChanged(QTime)), this, SLOT(save()));

    // Set volume screen connections
    // [Volume Changed] -> Apply the change and then save the new value to memory
    // Done button -> Clock Screen
    connect(memory->screenSetVolume, SIGNAL(volumeChanged(int)), this, SLOT(changeVolume(int)));
    connect(memory->screenSetVolume, SIGNAL(volumeChanged(int)), this, SLOT(save()));
    connect(memory->screenSetVolume, SIGNAL(doneBtnClicked()), memory->window, SLOT(goBackScreen()));

    // Connect the 1-second timer
    connect(memory->timer, SIGNAL(timeout()), this, SLOT(clockTick()));

    // Connect the Spare-Time timer
    connect(memory->bgTimer, SIGNAL(timeout()), this, SLOT(bgTick()));

    // Connect the player state change timer
    connect(memory->player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(alarmStateChange(QMediaPlayer::State)));
    connect(memory->player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(playerError(QMediaPlayer::Error)));
    
    // Prevent the settings tree from falling back to a higher parent
    memory->userApplicationSettings->setFallbacksEnabled(false);
    memory->userOrganizationSettings->setFallbacksEnabled(false);
    memory->systemApplicationSettings->setFallbacksEnabled(false);
    memory->systemOrganizationSettings->setFallbacksEnabled(false);

    // Set the media location
    //memory->player->setMedia(QUrl("qrc:///sound"));
    //memory->player->setMedia(QUrl::fromLocalFile("morningBugle.wav"));
    memory->player->setMedia(QUrl::fromLocalFile("Users/June/Music/morningBugle.wav"));

    // Fill in some run-time values to the about screen
    memory->screenAbout->updateReplacement();

    // Ensure that the alarm and clock times don't have any seconds
    memory->timeConverter.trimSeconds(memory->alarmTime);
    memory->timeConverter.trimSeconds(memory->clockTime);

    // Restore registry values
    restore();

    // Make an initial tick
    clockTick();

    // Perform a stop alarm
    // also disables the snooze button
    stopAlarm();

    // Switch to the clock screen
    switchToScreenClock();

    // Show the central window
    memory->window->show();

    // Begin the second and spare-time timers
    memory->timer->start(1000);
    memory->bgTimer->start(0);
}

Controller::~Controller()
{}

// Switch to the about screen
void Controller::switchToScreenAbout()
{
    memory->window->setScreen(memory->screenAbout);
}

// Switch to the clock screen
void Controller::switchToScreenClock()
{
    // Make sure to re-initialize the display
    // in case any changed values occured
    memory->screenClock->updateAlarmTime();
    memory->screenClock->updateClockTime();

    memory->window->setScreen(memory->screenClock);
}

// Switch to the set alarm screen
void Controller::switchToScreenSetAlarm()
{
    // Make sure to re-initialize the display
    // in case any changed values occured
    memory->screenSetAlarm->reUpdateControls();

    memory->window->setScreen(memory->screenSetAlarm);
}

// Switch to the volume screen
void Controller::switchToScreenVolume()
{
    // Make sure to re-initialize the display
    // in case any changed values occured
    memory->screenSetVolume->updateVolume();

    memory->window->setScreen(memory->screenSetVolume);
}

// Make sure the alarm is off and untrigegred
void Controller::stopAlarm()
{
    memory->triggered = false;
    memory->player->stop();
    memory->screenClock->alarmSnoozeEnabled(false);
}

// Make sure the alarm is on and triggered
void Controller::startAlarm()
{
    memory->triggered = true;
    memory->player->play();
    memory->screenClock->alarmSnoozeEnabled(true);
}

// Perform a 1-second tick
void Controller::clockTick()
{
    // Invert the tick boolean
    memory->tick = !memory->tick;

    // Get the new current time and trim off any seconds
    memory->clockTime = QTime::currentTime();
    memory->timeConverter.trimSeconds(memory->clockTime);

    // Update the clock display
    memory->screenClock->updateClockTime();

    // and check to see if the alarm needs triggering
    alarmCheck();
}

// Plan to be used in a future update
void Controller::bgTick()
{}

void Controller::alarmStateChange(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::StoppedState)
    {
        // If the alarm has stopped but the trigger is still set then start it right back up
        if(memory->triggered) memory->player->play();
    }
    else if(state == QMediaPlayer::PlayingState)
    {
        // If the alarm is now playing but the trigger is unset the halt it
        if(!memory->triggered) memory->player->stop();
    }
}

// Check that the alarm needs triggering
// if ignore trigger is set then also check that it
// doesnt need to stop
void Controller::alarmCheck(bool ignoreTrigger)
{
    // Proceed no further if the entire alarm system is disabled
    if(!memory->alarmEnabled) return;

    // If times match then play alarm
    // else stop it if told to ignore trigger and times dont match
    if(memory->clockTime == memory->alarmTime) startAlarm();
    else if(ignoreTrigger && memory->clockTime != memory->alarmTime) stopAlarm();
}

// Save any values to registry
void Controller::save()
{
    memory->userApplicationSettings->setValue("volume", memory->volume);
    memory->userApplicationSettings->setValue("alarmTime", memory->alarmTime.toString("h:mm:ap"));
}

// Restore values from registry
void Controller::restore()
{
    memory->volume = memory->userApplicationSettings->value("volume", 100).toInt();
    memory->alarmTime = QTime::fromString(memory->userApplicationSettings->value("alarmTime", "6:30:am").toString(), "h:mm:ap");
}

// Chec kthat the alarm doesnt need stopping
void Controller::alarmStopCheck()
{
    alarmCheck(true);
}

// Apply the new volume value
void Controller::changeVolume(int value)
{
    memory->player->setVolume(value);
}

void Controller::playerError(QMediaPlayer::Error error)
{
    qDebug() << memory->player->errorString();
}

void Controller::alarmSnooze()
{
    // Add 5 minutes to the alarm
    int seconds = 5 * 60;
    memory->alarmTime = memory->alarmTime.addSecs(seconds);

    // Then update and look to stop alarm
    memory->screenClock->updateAlarmTime();
    alarmStopCheck();
}

void Controller::alarmEnableToggle()
{
    // Toggle alarm enabled
    memory->alarmEnabled = !memory->alarmEnabled;

    // Then do an alarm check
    memory->screenClock->updateAlarmTime();
    if(memory->triggered) alarmStopCheck();
    else alarmCheck();
}
