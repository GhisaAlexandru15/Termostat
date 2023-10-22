# Termostat
Remote Control Thermostat.
This was a university project - that's why I programmed directly on the ATMega16U2 Processor's registers.
I used 4 7-segment displays to show the temperature, a thermistor as the temperature sensor and an IR LED receiver to get the signal (which I decoded myself) from the remote control.
You can change the units from Celsius to Fahrenheit and set the temperature to 5 C/40 F when you are leaving the house with just the click of a button and the last temperature is stored.
I also made sure it doesn't malfunction (I noticed that if the wire that gets the voltage on the thermistor is disconnected (it gets 0V), the program gets -375,15 C (absolute 0) so the heating system will be permanently on, so I only take into consideration temperatures between -100 and 250 C.
![Snapchat-1038584367](https://github.com/GhisaAlexandru15/Termostat/assets/44662097/e7b4dede-b1b2-470f-bf98-b20b736dd783)
