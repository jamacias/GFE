#include <Wire.h>

#define I2C_ADDR  0x62
//#define I2C_ADDR  0x51

void setup(){
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop(){
    Wire.requestFrom(I2C_ADDR, 2);    // request 2 bytes from slave device 0x62 (#98)
    while (Wire.available()) { // slave may send less than requested
        byte data = Wire.read(); // receive a byte as character
        Serial.println(data, HEX);         // print the character
    }

    delay(500);
}
