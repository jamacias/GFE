/**
  @file       MotorDemo
  @author     ELECHOUSE
  @version    V0.1
  @date       2012-6-22
  @brief        50A-DualChannelMotorDriverBoard demo code.
  @URL https://github.com/elechouse/motor
*/

/** import motor library */
#include <MOTOR.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>

// Defining joystick inputs
const int x_axis = 1; //Blue
const int y_axis = 2; //Green
const int z_axis = 4; //Yellow

const int button1 = 5; //Marrón
const int button2 = 6; //Blanco

char ssid[] = "ESP8266 Server";         // your network SSID (name)
char pass[] = "esp8266server";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned int localPort = 10002;  // local port to listen on

char packetBuffer[255];          // buffer to hold incoming packet

int x_val = 0;
int y_val = 0;
int z_val = 0;
int button1_state = 0;
int button2_state = 0;

const int centre = 1024/2;

WiFiEspUDP Udp;

void setup(void){
    Serial.begin(115200);   // initialize serial for debugging
    Serial.println("joystick_motors_4.ino");

    Serial2.begin(9600);    // initialize serial for ESP module
    WiFi.init(&Serial2);    // initialize ESP module

    // check for the presence of the shield
    if(WiFi.status() == WL_NO_SHIELD){
      Serial.println("WiFi shield not present");
      while (true); // don't continue
    }

    Serial.print("Attempting to start AP ");
    Serial.println(ssid);

    // uncomment these two lines if you want to set the IP address of the AP
    //IPAddress localIp(192, 168, 111, 111);
    //WiFi.configAP(localIp);

    // start access point
    status = WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);

    Serial.println("Access point started");
    printWifiStatus();

    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    Udp.begin(localPort);

    Serial.print("Listening on port ");
    Serial.println(localPort);

    /** motor driver initialize */
    motor.begin();
    /**
    NOTE:
    motor.begin() will change the prescaller of the timer0,
    so the arduino function delay() millis() and micros() are
    8 times slow than it should be.
    Please use motor_delay(), motor_millis(), motor_micros() instead them.
    */
}


void loop(void){
    x_val = 512;
    y_val = 512;
    z_val = 512;
    button1_state = 1;
    button2_state = 1;

    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if(packetSize){
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remoteIp = Udp.remoteIP();
        Serial.print(remoteIp);
        Serial.print(", port ");
        Serial.println(Udp.remotePort());

        // read the packet into packetBufffer
        int len = Udp.read(packetBuffer, 255);
        if (len > 0){
            packetBuffer[len] = 0;
        }
        Serial.println("Contents:");
        Serial.println(packetBuffer);

        // Message to decode i.e. 1023 1023 1023 1 1
        sscanf(packetBuffer,"%d %d %d %d %d %d", &x_val, &y_val, &z_val, &button1_state, &button2_state);

        Serial.print("x_val = ");
        Serial.println(x_val);
        Serial.print("y_val = ");
        Serial.println(y_val);
        Serial.print("z_val = ");
        Serial.println(z_val);
        Serial.print("button1_state = ");
        Serial.println(button1_state);
        Serial.print("button2_state = ");
        Serial.println(button2_state);
    }

    x_val = 1024 - x_val;
    Serial.print("x_val = ");
    Serial.println(x_val);
    y_val = 1024 - y_val;
    Serial.print("y_val = ");
    Serial.println(y_val);

	int x = x_val - centre;
    Serial.print("x = ");
    Serial.println(x);
	int y = y_val - centre;
    Serial.print("y = ");
    Serial.println(y);

    // Computing the speed
    //	convert to polar
   	float r = hypot(x, y);
   	float t = atan2(y, x);

//	rotate by 45 degrees
   	t = t - 3.14159265358979323846 / 4;

//  back to cartesian
    float left = r * cos(t);
    float right = r * sin(t);

//  rescale the new coords
    left = left * sqrt(2);
    right = right * sqrt(2);

//  clamp to -245/+245 to avoid over power
    left = fmax(-245, fmin(left, 245));
    right = fmax(-245, fmin(right, 245));
    Serial.print(left);
    Serial.print(" ");
    Serial.println(right);

    float left_abs = abs(left);
    float right_abs = abs(right);
    Serial.print(left_abs);
    Serial.print(" ");
    Serial.println(right_abs);

    if(button1_state == 0 || x <= 100 && x >= -100 && y <= 100 && y >= -100){
        Serial.println("Stop!");
        motor.set(A, 0, FORWARD);
        motor.set(B, 0, FORWARD);
        motor_delay(150);
    }

    else{
        if(y >= 0){
            Serial.println("y > 0");
            if(left < 0){
                Serial.print("Motor left moving REVERSE @ ");
                Serial.println(left_abs);
                motor.set(A, left_abs, REVERSE);
                motor_delay(75);
            }
            else{
                Serial.print("Motor left moving FORWARD @ ");
                Serial.println(left);
                motor.set(A, left, FORWARD);
                motor_delay(75);
            }

            if(right < 0){
                Serial.print("Motor right moving REVERSE @ ");
                Serial.println(right_abs);
                motor.set(B, right_abs, REVERSE);
                motor_delay(75);
            }
            else{
                Serial.print("Motor right moving FORWARD @ ");
                Serial.println(right);
                motor.set(B, right, FORWARD);
                motor_delay(75);
            }
        }
        else{
            Serial.println("y < 0");
            if(x < 0 && x >= y || x > 0 && x <= -y){ //Lower third and fourth quarter
                Serial.println("x < 0 && x >= y");
                Serial.print("Motor left moving REVERSE @ ");
                Serial.print(right_abs);
                Serial.print(" and right moving REVERSE @ ");
                Serial.println(left_abs);
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left_abs, REVERSE);
                motor_delay(75);
            }
            else if(x < 0 && x <= y){ //Upper third quarter
                Serial.println("x < 0 && x <= y");
                Serial.print("Motor left moving FORWARD @ ");
                Serial.print(left_abs);
                Serial.print(" and right moving REVERSE @ ");
                Serial.println(right_abs);
                motor.set(A, right_abs, FORWARD);
                motor.set(B, left_abs, REVERSE);
                motor_delay(75);
            }
            else{ //Upper fourth quarter
                Serial.println("x > 0 && x >= -y");
                Serial.print("Motor left moving REVERSE @ ");
                Serial.print(right_abs);
                Serial.print(" and right moving FORWARD @ ");
                Serial.println(left_abs);
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left_abs, FORWARD);
                motor_delay(75);
            }
        }
    }
}

void printWifiStatus(){
    // print your WiFi shield's IP address
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print where to go in the browser
    Serial.println();
    Serial.print("SSID: ");
    Serial.print(ssid);
    Serial.print("\nIP: ");
    Serial.print(ip);
    Serial.println();
}

int calculate_average(int axis){
    int value;
    int num = 10;
    for(int i = 0; i < num; i++){
        value += analogRead(axis);
    }
    int average = value / 10;

    return average;
}
