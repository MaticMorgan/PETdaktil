In this project we aim to make a DIY machine that turns PET plastic bottles into 3D printer filament. The aim is to make filament that can, at least for our home use, completely swap regular consumer filament.

A basic functioning principle is the following: a bottle is heated and span to make it as cylindrically shaped as possible. The bottle is then cut into stripes, much like you would peel an apple in one single motion.
The strip is then fed into a 3D printer hotend which has a modified nozzle and is held at a specific temperature. The pieces of produced filament are then fused together length-wise to make a reasonable amount of filament.


A cheap hotend was used. The seller only provided that it worked at 12 V. I measured it had some kind of 100 kOhm thermistor. In order to make sure I had the temperature measurements as accurate as possible I 
took a different thermistor for which I already knew the coefficients and heated the hotend to various temperatures, waited for the temperature to stabilize, measured the temperature with the known thermistor 
and then read the value of the unknown thermistor via a voltage divider with a 100kOhm resistor. I read the value via an Arduino analog input. I then fitted a (now linear) function corelating the analogRead() 
measurement and the temperature. This function will later be used to calculate the actual temeprature in degress Celsius.

The above knowledge is required to make a solid temperature controller. I decided to use PID since it's a standard for anything temperature control related (it's also used in 3D printers, plus I had some 
experience working with PID from my daily job). I chose the most basic Arduino PID library. The heating element is switched on and off via a IRFZ44N MOSFET, while the temperature is measured the same way as 
described above. After a fair bit of trial and error I decided to have two seperate PID regimes: one while far away from the target temperature and a more precise one while close.
N.B.: the actual values of P, I and D are subject to a specific hardware setup. These numbers mean very little in a broad sense and should never be copied.

The pulling of the filament will be done with a stepper motor. I chose a Nema N17 and an A988 stepper motor driver. For smoothness-sake I went with 32 microsteps, the largest amount possible with this driver. The stepper 
motor is powered by 12 V. The motor shaft spins a spool-like holder for the newly made filament.

A standard computer power supply was used. The 12 V rails are to power the heating element, motor and motor driver while the 5 V rails are used to power the Arduino.
N.B.: the PC power supply has to be partially meddle with to make operable under such conditions. Follow online tutorials and proceed at your own risk.
