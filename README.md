# UA-25 Hardware Modification for Windows 10 and MacOs 10.11 - 10.14 Mojave

This is a fork of RemoteFlyer's mod. In my version of UA-25, I needed some changes in I2C addressing and ROM offset for the device ID.

The UA-25 is not USB class complient when in advanced mode. Advanced mode is needed for MIDI IN/OUT, for 24 bit sampling and for higher sample rates. If you just need 16 bit / 44.1 kHz sampling without MIDI, no modification is needed, it works out of the box. But to use the advanced mode, a driver is needed. With Linux (ALSA), the advanced mode works well, but for recent Windows or MacOs versions, there are no drivers, as Roland has stopped the support of UA-25 a long time ago. This mod changes the USB device ID of the UA-25, so that the OS loads the driver for the UA-25EX, which is essentially the same interface with some more analog features (compressor, ground-lift) and had a slightly longer support by Roland. The last available UA-25EX driver for MacOs is for 10.11., but I can confirm it works with 10.14.6 Mojave. The modded UA-25 still works great with Linux/ALSA.

## **** Use this code at your own risk.  There are checks in the code, but I am not responsible for you bricking your UA-25 ****

Give your old Roland Edirol UA-25 Audio and Midi interface a bit more life by making it compatible with Windows 10

The UA-25 contains an 8k I2c EEPROM which stores the USB VID/PID and firmware to start the device. By changing this identifier to the same ID that the UA-25EX uses, new versions of windows 10 will recognise the device.

Inside the UA-25 is a 4 pin connector labelled CN2 that contains the i2c signals, you can connect the arduino analog A4 and A5 pins to this connector as follows, but make sure the UA-25 is unpowered and disconnected from usb for now...

```
PIN  SIGNAL   ARDUINO PIN
1    x        N/C
2    SCL      Analog A5
3    SDA      Analog A4
4    GND      GND
```

To change the contents of an i2c EEPROM, you can use an Arduino and the code provided in the sketch to program the eeprom usb ID and checksum.  The code has safety checks that can be monitored using the arduino serial monitor.

1. Make sure the UA-25 is unpowered.
2. Once the Arduino is connected to the UA-25 with the three wires, load the sketch into the Arduino editor, connect your arduino to the computer and upload the sketch.  
3. Connect the UA-25 to a different USB port or usb charger to supply power to it and wait a few seconds. 
5. Press CTRL+SHIFT+M in the Arduino editor to load the serial monitor.  This will reset the arduino and run the code.

All being well, the following text will appear in the Arduino Serial Monitor...

```
Found VID_582&PID_74 with checksum 0xA785
Found UA-25 ID with correct checksum, do the coding
Checking
Found VID_582&PID_E6 with checksum 0xA7F7
Found correct ID and Checksum.  Done here.
```

But if you see the following ...

```
Found VID_582&PID_E6 with checksum 0xA7F7
Sorry, did not detect the UA-25 ID and checksum
```

... then you already had the UA-25 and the code has already done its job. 

If you see anything else,  the code wont work. 

That's it... 
Disconnect the power from the AU-25, plug it into a USB port and Windows 10 should recognise it as a UA-25EX and install the drivers.  
