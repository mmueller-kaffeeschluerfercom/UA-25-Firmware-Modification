#include<Wire.h>
#define eeDeviceAddress 0x56
#define usbIDAddress 0x009B
#define checksumAddress 0x0A

void writeEEPROM(int i2cDeviceAddress, unsigned int eeAddress, byte i2cData ) 
{
  Wire.beginTransmission(i2cDeviceAddress);  // select EEPROM address
  Wire.write(int(eeAddress >> 8));   // set MSB byte of address
  Wire.write(int(eeAddress & 0xFF)); // set LSB byte of address
  Wire.write(i2cData);  // send data byte to address
  Wire.endTransmission();  // end transmission  
  delay(5); // wait for eeprom to write data
}
 
byte readEEPROM(int i2cDeviceAddress, unsigned int eeAddress ) 
{
  byte i2cData = 0xff;
  Wire.beginTransmission(i2cDeviceAddress); // select EEPROM address
  Wire.write(int(eeAddress >> 8));   // set MSB byte of address
  Wire.write(int(eeAddress & 0xFF)); // set LSB byte of address
  Wire.endTransmission();  // end transmission  
  Wire.requestFrom(i2cDeviceAddress, 1); // read 1 byte data from address into buffer
  while (Wire.available()) 
  {
    i2cData = Wire.read();
  }
  return i2cData;
}

uint16_t readEEPROMWord(byte i2cDeviceAddress, unsigned int  eeAddress ) 
{
  return readEEPROM(eeDeviceAddress, eeAddress + 1 ) << 8 | readEEPROM(eeDeviceAddress, eeAddress);  
}

void setup() 
{
  uint16_t usbVID = 0;
  uint16_t usbPID = 0;
  uint16_t checksum = 0;
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Wire.begin();
  // ***** TESTING CODE, DO NOT UNCOMMENT UNLESS USING A BLANK/TEST EEPROM. ******
  // this will write the bytes to a blank i2c EEPROM for testing the script
  // writeEEPROM(eeDeviceAddress, usbIDAddress, 0x82);
  // writeEEPROM(eeDeviceAddress, usbIDAddress + 1, 0x05);
  // writeEEPROM(eeDeviceAddress, usbIDAddress + 2, 0x74);
  // writeEEPROM(eeDeviceAddress, usbIDAddress + 3, 0x00);
  // writeEEPROM(eeDeviceAddress, checksumAddress, 0x85);
  // writeEEPROM(eeDeviceAddress, checksumAddress + 1, 0xA7);
  // ***** END OF TESTING CODE ******
  usbVID = readEEPROMWord(eeDeviceAddress, usbIDAddress);  // read VID from EEPROM
  usbPID = readEEPROMWord(eeDeviceAddress, usbIDAddress + 2);  // read PID from EEPROM
  checksum = readEEPROMWord(eeDeviceAddress, checksumAddress);  // read checksum from EEPROM

  Serial.print("Found VID_");  Serial.print(usbVID, HEX);  Serial.print("&PID_");
  Serial.print(usbPID, HEX);  Serial.print(" with checksum 0x");  Serial.println(checksum, HEX);
  
  if ((usbVID == 0x0582) and (usbPID == 0x0074) and (checksum == 0xa785)) // check for USB ID matching UA-25 ( VID_0582&PID_0074 ) with correct checksum
  { // Found a UA-25
    Serial.println("Found UA-25 ID with correct checksum, do the coding");
    writeEEPROM(eeDeviceAddress, usbIDAddress + 2, 0xE6);  // Write UA-25EX PID to eeprom (VID_0582&PID_00E6)
    writeEEPROM(eeDeviceAddress, checksumAddress, 0xF7);  // Write the checksum change

    Serial.println("Checking");
    usbVID = readEEPROMWord(eeDeviceAddress, usbIDAddress);  // read VID from EEPROM
    usbPID = readEEPROMWord(eeDeviceAddress, usbIDAddress + 2);  // read PID from EEPROM
    checksum = readEEPROMWord(eeDeviceAddress, checksumAddress);  // read checksum from EEPROM
  
    Serial.print("Found VID_");  Serial.print(usbVID, HEX);  Serial.print("&PID_");
    Serial.print(usbPID, HEX);  Serial.print(" with checksum 0x");  Serial.println(checksum, HEX);
    if ((usbVID == 0x0582) and (usbPID == 0x00E6) and (checksum == 0xa7F7)) // check for USB ID matching UA-25 ( VID_0582&PID_0074 ) with correct checksum
    { 
      Serial.println("Found correct ID and Checksum.  Done here.");
    } else {
      Serial.println("Failed, sorry!");
    }
  }
  else
  { // Didn't find UA-25
    Serial.println("Sorry, did not detect the UA-25 ID and checksum.");
  }
}

void loop() {}

