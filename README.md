# IPASS - SSD1331

# Introduction
This is the repository for my propaedeutic year end project, called IPASS.

The goal of this project was to write a library for a hardware component of your choice,
and write this library using the OOP ways that we learned this period.
You also needed to use the library you created to "talk" to the hardware.
I chose to create a library that was based on hwlib, and I haven't used any other library.

I also created a little tic-tac-due(toe) game that uses buttons as input, and after a button press,
a circle will be drawn at the corresponding coordinate in the grid.
This way I can demonstrate my working library for the OLED.

# Included librarie(s)
The library I created is based on [hwlib and bmptk](https://github.com/wovo/hwlib).

# Used hardware
This library is intended to be used with the [Arduino Due](https://www.arduino.cc/en/Main/ArduinoBoardDue).

I chose the [SSD1331](https://bit.ly/3zVqiJX) driver that is combined with an RGB Oled screen.

I also used two of the following [keypads](https://bit.ly/3h0HOFr).

# Author
| Name(s)              | Studentnumber | Username       |
| -------------------- | ------------- | -------------- |
| Kenny van Doorn      | 1789386       | Kennyvandoorn  |


# Installation
```git
git clone https://github.com/kennyvandoorn/IPASS
```
# Instructions
Make sure you downloaded and included hwlib into your project. 
```
https://github.com/wovo/hwlib
```

Build using the included makefile, or use the included /run.bat file.

# Extra notes
The included main.cpp shows you the use on how to create pins, and create objects.
You can use these predefined variables to test the OLED and key matrix.
These predefined variables start a new game of Tic-Tac-Due!

# License

Copyright (c) Kenny van Doorn (kenny.vandoorn@student.hu.nl), 2021

Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

Note: See license file for a detailed description.

