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

#include "screensetvolume.h"
#include "ui_screensetvolume.h"

ScreenSetVolume::ScreenSetVolume(int& volume,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenSetVolume),
    volume(volume)
{
    // wire ui
    ui->setupUi(this);
}

ScreenSetVolume::~ScreenSetVolume()
{
    delete ui;
}

// send back volume
// Not used by program, placed here in case used elsewhere
int ScreenSetVolume::getVolume()
{
    return volume;
}

// Set volume
void ScreenSetVolume::setVolume(int value)
{
    // Make sure new value
    if(volume == value) return;

    // Assign and notify change
    volume = value;
    emit volumeChanged(value);

    // update controls
    updateVolume();
}

// Update controls
void ScreenSetVolume::updateVolume()
{
    // Update the volume knob and LCD screen
    ui->volumeKnob->setValue(volume);
    ui->volumeDisplay->display(volume);
}

// volume knob rotated
void ScreenSetVolume::on_volumeKnob_valueChanged(int value)
{
    setVolume(value);
}

// done button clicked
void ScreenSetVolume::on_doneBtn_clicked()
{
    emit doneBtnClicked();
}
