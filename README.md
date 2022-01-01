# soviet_silvester
SNOVEM GODEM COMRADE

A gag project for Novigod 2022.
Detects a toilet flush using a reed switch in the toilet's tank, triggering the Soviet anthem to play, accompanied by a light show.
While idle, the lights are a nice white/green.

## Hardware
* Esp32
* Arduino Nano
* SPST Reed switch
* Magnets
* Addressable LED (RGB) Strip
* Logic level shifter (for I2C between Arduino/ESP)
* [SC8002B Amp+Speaker module](https://www.keyestudio.com/products/keyestudio-8002b-power-amplifier-module-speaker-buzzer-for-arduino-industrial-grade)

------

* With some adjustments this should work with 2 Esps (instead of the nano), in which case the logic level shifter is not necessary.

## Config
* I2C between Esp/Arduino
* Reed switch hot-glued inside toilet tank
* Magnets glued on each arm of toilet handles (inside tank). Adjust sensitivity to recognize flushes
* PlatformIO

## Running
Not originally intended to be public, so code is a bit messy.
There are 2 environments in the PlatformIO project, for Arduino/Esp (Slave/master).

Feel free to contact me if you'd like help getting it running.
