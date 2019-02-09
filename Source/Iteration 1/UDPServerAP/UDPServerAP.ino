/*
 UDPServerAP based on WebServerAP example.

 This example is a remix of UdpSendRecieve.ino and UDPWebServer.ino with AP

 This is a UDP server communicating using ESP8266 module.
 This sketch will start an access point and start listening for UDP packages
 on a local port. If any package is received it will be printed to the
 Serial Monitor.

 Credits to the orignal author of the examples.
 Modifications and further programming by Javier Macías
*/

#include <stdio.h>
#include <stdlib.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>

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

WiFiEspUDP Udp;

void setup(){
  Serial.begin(115200);   // initialize serial for debugging
  Serial2.begin(9600);    // initialize serial for ESP module
  Serial.println("UDPServerAP.ino");
  WiFi.init(&Serial2);    // initialize ESP module

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
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
}


void loop(){
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize){
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
