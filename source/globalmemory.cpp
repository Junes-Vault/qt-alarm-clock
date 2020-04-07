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

#include "globalmemory.h"

#include <QApplication>

// Set global memory instance
GlobalMemory* GlobalMemory::instance = 0;

// Send back global memory
GlobalMemory* GlobalMemory::getInstance()
{
    if(!instance) instance = new GlobalMemory();

    return instance;
}

// Initialize all global memory values
GlobalMemory::GlobalMemory(QObject *parent) :
    QObject(parent),
    timer(new QTimer(this)),
    bgTimer(new QTimer(this)),
    tick(false),

    player(new QMediaPlayer(this)),
    triggered(false),

    userApplicationSettings(new QSettings(QApplication::organizationName(), QApplication::applicationName())),
    userOrganizationSettings(new QSettings(QApplication::organizationName())),
    systemApplicationSettings(new QSettings(QSettings::SystemScope, QApplication::organizationName(), QApplication::applicationName())),
    systemOrganizationSettings(new QSettings(QSettings::SystemScope, QApplication::organizationName())),

    window(new Window(switchBackScreen)),
    screenAbout(new ScreenAbout()),
    screenClock(new ScreenClock(alarmTime, clockTime, alarmEnabled, timeConverter, tick)),
    screenSetAlarm(new ScreenSetAlarm(alarmTime, alarmEnabled, timeConverter)),
    screenSetVolume(new ScreenSetVolume(volume)),

    alarmTime(QTime::currentTime()),
    clockTime(QTime::currentTime()),
    alarmEnabled(false),
    timeConverter(Clock()),
    volume(0)
{}

GlobalMemory::~GlobalMemory()
{
    // Reverse delete
    delete screenSetVolume;
    delete screenSetAlarm;
    delete screenClock;
    delete screenAbout;
    delete window;

    delete systemOrganizationSettings;
    delete systemApplicationSettings;
    delete userOrganizationSettings;
    delete userApplicationSettings;

    delete player;
    delete bgTimer;
    delete timer;
}
