# UA-25 Hardware Modification 


Give your old Roland Edirol UA-25 Audio and Midi interface a bit more life by making it compatible with Windows 10

The UA-25 contains an 8k I2c EEPROM which stores the USB VID/PID and firmware to start the device. By changing this identifier to the same ID that the UA-25EX uses, new versions of windows 10 will recognise the device.

To change the contents of an i2c EEPROM, you will need an Arduino.

