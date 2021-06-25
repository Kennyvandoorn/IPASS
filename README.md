# IPASS
This is the repository for my propaedeutic year end project, called IPASS.

The goal of this project was to write a library for a hardware component of your choice,
and write this library using the OOP ways that we learned this period.
You also needed to use the library you created to "talk" to the hardware.
I created a little tic-tac-due(toe) game that uses buttons as input, and after a button press,
a circle will be drawn at the corresponding coordinate in the grid.
I chose to create a library that was based on hwlib.
See:
```
https://github.com/wovo/hwlib
```

I chose the SSD1331 driver that is combined with an RGB Oled screen.
```
https://hu-hbo-ict.gitlab.io/turing-lab/ti-lab-shop/RGB%20)LED%2096%20x%2064.html
```

I also used two of the following keypads:
```
https://hu-hbo-ict.gitlab.io/turing-lab/ti-lab-shop/keypad%20foil%204x4.html
```

# Created by
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


