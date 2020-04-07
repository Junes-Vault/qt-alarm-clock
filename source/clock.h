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
 * Provides a way to work between 12 and 24 hour time
 * while ignoring seconds
*/
#ifndef CLOCK_H
#define CLOCK_H

#include <QTime>

// A struct because we don't need a class
struct Clock
{
    int hours;
    int minutes;
    bool pm;

    Clock(int hours = 12, int minutes = 0, bool pm = true);

    // Take apart a 24 hour time
    // and convert to 12 filling in the
    // above values
    void parse24Time(QTime& time);

    // Put back together the 12-hour
    // time using the values from above
    void apply12Time(QTime& time);

    // Takes apart and immidiately puts
    // back together thus zeroing out seconds
    void trimSeconds(QTime& time);
};

#endif // CLOCK_H
