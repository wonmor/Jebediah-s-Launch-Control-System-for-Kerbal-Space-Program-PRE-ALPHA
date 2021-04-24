# Jebediah Kerman's Launch Control System
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
The code was built upon a finite-state machine concept; as the LCD display transitions to a menu screen from a startup page, the user has to navigate and choose different options, which leads to the corresponding pages.

Using the controller, you can control the RCS thrusters of your vehicle, which can be particularly useful when docking a spacecraft. Most importantly, it has an automatic hands-free launch feature, in which the controller runs appropriate commands for the vehicle to lift off. You can also control the throttle while the vehicle is flying. Jebediah's Launch Control System uses keyboard inputs according to the key bindings in the game settings, which is exclusively available on Arduino Leonardo/Micro type boards. In case of an emergency, a DON'T PANIC (Vehicle Abort) button is included in the package as well!

## PICTURES

![ScreenShot](IMG_1621.jpeg)
![ScreenShot](IMG_1622.jpeg)
![ScreenShot](IMG_1625.jpeg)
![ScreenShot](IMG_1631.jpeg)
![ScreenShot](IMG_1632.jpeg)
