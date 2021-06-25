# IPASS - SSD1331

# Introduction
This is the repository for my propaedeutic year end project, called IPASS.

The goal of this project is to write a library for a hardware component of my choice,
and write this library using the OOP ways that I have learned this period.
I had to use my self-made library to communicate with the hardware.

I have also created a tic-tac-toe game with physical buttons that can be used by two players.
Buttons 1 to 9 are each linked to a specific coordinate in the grid.
After pressing one of the buttons on the keypad, a circle will be drawn at the corresponding coordinate in the grid.
Using this game, I can demonstrate my library for the OLED.

# Included libraries
This library uses [hwlib and bmptk](https://github.com/wovo/hwlib).

# Used hardware
This library is intended to be used with the [Arduino Due](https://www.arduino.cc/en/Main/ArduinoBoardDue).

I chose the [SSD1331](https://bit.ly/3zVqiJX) driver that is combined with a RGB Oled screen.

I also used two of the [foil 4x4 matrix keypads](https://bit.ly/3h0HOFr).

# Author
| Name                 | Studentnumber | Username       |
| -------------------- | ------------- | -------------- |
| Kenny van Doorn      | 1789386       | Kennyvandoorn  |


# Installation
```git
git clone https://github.com/kennyvandoorn/IPASS
```
# Instructions
1. Make sure you have downloaded and included [hwlib](https://github.com/wovo/hwlib) into your project. 
2. Build using the included makefile, or run the run.bat file from your terminal.

# Extra notes
The included main.cpp shows you how to create pins and objects.
You can use the predefined variables to test the OLED and key matrix.
The predefined variables allow players to start and play a game of Tic-Tac-Due!

# License

Copyright (c) Kenny van Doorn (kenny.vandoorn@student.hu.nl), 2021

Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

Note: See license file for a detailed description.

