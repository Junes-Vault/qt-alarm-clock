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

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget*& switchBackScreen, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window),
    switchBackScreen(switchBackScreen)
{
    // Wire the Ui to this class
    ui->setupUi(this);
}

Window::~Window()
{
    // Reverse delete
    delete ui;
}

// Send back screen
QWidget* Window::getScreen()
{
    return ui->screenStack->currentWidget();
}

// Set new screen
void Window::setScreen(QWidget* widget)
{
    // Make sure the pointer is valid first
    if(!widget) return;

    // Make sure screen exists in stack first, if not then add it
    if(ui->screenStack->indexOf(widget) == -1) ui->screenStack->addWidget(widget);

    // Add this screen as the previous screen
    switchBackScreen = getScreen();

    // Now switch and notify of switch
    ui->screenStack->setCurrentWidget(widget);
    emit screenChanged(widget);
}

void Window::goBackScreen()
{
    // Make sure the pointer is valid
    if(!switchBackScreen) return;

    // Switch screens
    setScreen(switchBackScreen);

    // Trash new back screen
    // You may only go back 1 time
    switchBackScreen = 0;
}
