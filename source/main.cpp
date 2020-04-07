/*
    Copyright 2013 June Hanabi

    This file is part of AlarmClock.

    AlarmClock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Qt Pre-Processing and Framework Booting
    QApplication a(argc, argv);

    // Some Presets
    QApplication::setApplicationName("AlarmClock");
    QApplication::setApplicationVersion("v1.1.3.0-beta");
    QApplication::setOrganizationDomain("com.gmail.jHanabi1");
    QApplication::setOrganizationName("June Hanabi");

    // Unused variable but used to start everything
    Controller c;

    // Start framework
    return a.exec();
}
