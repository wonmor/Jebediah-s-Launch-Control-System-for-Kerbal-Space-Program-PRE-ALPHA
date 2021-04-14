# Jebediah's Launch Control System for Kerbal Space Program
### Version 2.0
### An Open-Source Project by John Seong

An automated countdown timer, a macro keyboard, and a control device for Kerbal Space Program that can be connected to the PC and autonomously launch the vehicle when the timer hits 0.

## FEATURES
1. Automated countdown & launch
2. RCS & Throttle control
3. Simple thrust-to-weight ratio calculation

## VIDEO

[![CLICK HERE](https://img.youtube.com/vi/l9Dpn6NV0MA/0.jpg)](https://www.youtube.com/watch?v=l9Dpn6NV0MA)

## BEHIND THE SCENES
The code was built upon a finite state machine; as the LCD displays transitions to a menu screen from a startup page, the user has to navigate and choose different options which lead to different pages.

The controller supports full RCS control which can be useful when docking a spacecraft, and automated hands-free launch, as it uses keyboard input feature according to the key bindings in the game settings, which is exclusively available on Arduino Leonardo/Micro type boards.

## PICTURES

![ScreenShot](IMG_1621.jpeg)
![ScreenShot](IMG_1622.jpeg)
![ScreenShot](IMG_1625.jpeg)
![ScreenShot](IMG_1631.jpeg)
![ScreenShot](IMG_1632.jpeg)
