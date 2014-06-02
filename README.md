SquatCheck
==========

An adruino based tool to check if a person performing a squat exercise goes low enough.

## Parts
1 Arduino pro mini (or UNO but it is bigger)
1 HC-SR04 Ultrasound ping sensor
1 9V battery
1 switch
1 Piezo buzzer
2 Status indicator (see below)

### Status indicators
There are two information that needs to be transmitted to the user :

* The status of the device (Setup or running)
* When running when the user reaches the programmed level

This information is sent using a buzzer but as gyms can be noisy or user may want to listen to music the sound cannot be the only mean to communicate.
For visual communication I choose to have a [button with a LED](http://www.adafruit.com/blog/2011/10/13/new-product-waterproof-metal-pushbutton-with-blue-led-ring-16mm-blue-momentary/) for the status. And a [laser](http://www.adafruit.com/products/1054) that projects a red dot on the wall in front of me while squatting but you may choose any other device.

## Usage
When the device is turned on It emmits a sound and the status indicator is blinking. It waits for the user to squat 1 time as low as they want to go on other squats (Usually the setup is done without added weights). When the device detects something not moving between 10 and 150cm above it, it switches to running mode with the level of the object above it as the reverence level.
As soon as in running mode the status indicator is lit with its brightness relative to the height of what is above it. as soon as something goes below the reference level the buzzer emmits a sound and the level indicator is turned on.

## Schematics
[Schematics](http://i.imgur.com/oKm0ZgJ.png)

## Prototype
