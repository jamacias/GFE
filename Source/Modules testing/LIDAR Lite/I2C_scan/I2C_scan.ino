#include <Wire.h>

// #define address 0x62
#define address 0x51

void setup(){
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nInitializing I2C communication...");
}


void loop(){
    byte error;

    Serial.print("Communicating I2C address: 0x");
    Serial.println(address, HEX);
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0){
        Serial.print("I2C device found at address 0x");
        Serial.println(address, HEX);
    }
    else if (error==4){
        Serial.print("Unknown error at address 0x");
        Serial.println(address, HEX);
    }
    else{
        Serial.print("Not found at address 0x");
        Serial.println(address, HEX);
        Serial.print("Error: ");
        Serial.println(error);
    }

    delay(5000);           // wait 5 seconds for next scan
}
