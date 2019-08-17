# UA-25 Hardware Modification 

**** Use this code at your own risk.  There are checks in the code, but I am not responsible for you bricking your UA-25 ****

Give your old Roland Edirol UA-25 Audio and Midi interface a bit more life by making it compatible with Windows 10

The UA-25 contains an 8k I2c EEPROM which stores the USB VID/PID and firmware to start the device. By changing this identifier to the same ID that the UA-25EX uses, new versions of windows 10 will recognise the device.

Inside the UA-25 is a 4 pin connector that contains the i2c signals, you can connect the arduino analog A4 and A5 pins to this connector as follows, but make sure the UA-25 is unpowered and disconnected from usb for now...

```PIN  SIGNAL   ARDUINO PIN
1    x        N/C
2    SCL      Analog A5
3    SDA      Analog A4
4    GND      GND```

To change the contents of an i2c EEPROM, you can use an Arduino and the code provided in the sketch to program the eeprom usb ID and checksum.  The code has safety checks that can be monitored using the arduino serial monitor.

1. Make sure the UA-25 is unpowered.
2. Once the Arduino is connected to the UA-25 with the three wires, load the sketch into the Arduino editor, connect your arduino to the computer and upload the sketch.  
3. Connect the UA-25 to a different USB port or usb charger to supply power to it and wait a few seconds. 
5. Press CTRL+SHIFT+M in the Arduino editor to load the serial monitor.  This will reset the arduino and run the code.

All being well, the following text will appear in the Arduino Serial Monitor...

```Found VID_582&PID_74 with checksum 0xA785
Found UA-25 ID with correct checksum, do the coding
Checking
Found VID_582&PID_E6 with checksum 0xA7F7
Found correct ID and Checksum.  Done here.```

But if you see the following ...

```Found VID_582&PID_E6 with checksum 0xA7F7
Sorry, did not detect the UA-25 ID and checksum```

... then you already had the UA-25 and the code has already done its job. 

If you see anything else,  the code wont work. 

That's it... 
Disconnect the power from the AU-25, plug it into a USB port and Windows 10 should recognise it as a UA-25EX and install the drivers.  
