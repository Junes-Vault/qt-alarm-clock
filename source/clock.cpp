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

#include "clock.h"

#include <QStringList>

Clock::Clock(int hours, int minutes, bool pm) :
hours(hours),
minutes(minutes),
pm(pm)
{}

void Clock::parse24Time(QTime& time)
{
    // First get as a 12-hour string then break up into 3 parts
    QStringList timeStr = time.toString("h:mm:ap").split(':');

    // Re-parse with new 12-hour time
    hours = timeStr.at(0).toInt();
    minutes = timeStr.at(1).toInt();
    pm = timeStr.at(2) == "pm";
}

void Clock::apply12Time(QTime& time)
{
    // First convert to a 12-hour string
    QString newTime;
    newTime += QString::number(hours) + ":";
    newTime += QString::number(minutes) + ":";
    if(pm) newTime += "pm";
    else newTime += "am";

    // Now update the time basd on clock
    time = QTime::fromString(newTime, "h:m:ap");
}

void Clock::trimSeconds(QTime& time)
{
    // Pare and immidiately apply
    parse24Time(time);
    apply12Time(time);
}
