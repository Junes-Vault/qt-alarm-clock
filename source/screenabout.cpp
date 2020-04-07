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

#include "screenabout.h"
#include "ui_screenabout.h"

ScreenAbout::ScreenAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenAbout)
{
    // wire ui to this class
    ui->setupUi(this);
}

ScreenAbout::~ScreenAbout()
{
    delete ui;
}

void ScreenAbout::updateReplacement()
{
    // replace $version with application version string
    ui->aboutDisplay->setHtml(ui->aboutDisplay->toHtml().replace(
                    "$version",
                    QApplication::applicationVersion()));
}

void ScreenAbout::on_doneBtn_clicked()
{
    // Announce done button clicked
    emit doneBtnClicked();
}
