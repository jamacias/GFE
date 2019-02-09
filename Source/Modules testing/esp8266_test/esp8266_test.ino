// #include <SoftwareSerial.h>
// SoftwareSerial softSerial(8, 9); // RX, TX

void setup()
{
  uint32_t baud = 9600;
  Serial.begin(115200);
  Serial2.begin(baud);
  Serial.print("SETUP!! @");
  Serial.println(115200);
}

void loop()
{
    while(Serial2.available() > 0)
    {
      char a = Serial2.read();
      if(a == '\0')
        continue;
      if(a != '\r' && a != '\n' && (a < 32))
        continue;
      Serial.print(a);
    }

    while(Serial.available() > 0)
    {
      char a = Serial.read();
      Serial.write(a);
      Serial2.write(a);
    }
}
