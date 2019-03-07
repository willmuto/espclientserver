#include <WiFi.h>

// Contains SSID and PASSWORD for wifi network,
// both const char* variables.
#include "mywifi.h"

/*
 *  import socket
 *  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 *  s.connect(('192.168.1.8', 2000))
 *  s.send(b'TEST\n')
 *  s.close()
 *  
 */

bool DEBUG = 1;

const uint PORT = 2000;
unsigned int SERIAL_BAUD = 115200;
unsigned int WIFI_RECONNECT_TIME = 100;       // in milliseconds

WiFiServer server(PORT);
WiFiClient client;

void debug(String msg) 
{
  // Print debug output.
  if (DEBUG) Serial.println(msg);
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_RECONNECT_TIME);
  }
  
  debug("Connected to the WiFi network " + String(SSID)); 
  Serial.print("With IP ");
  Serial.println(WiFi.localIP()); 
  Serial.print("Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  server.begin();
  debug("Server started.");

}

void loop() {
  // listen for incoming clients
  client = server.available();
  
  if (client) {
    Serial.println("New client connected.");

    while (client.connected()) {
      if (client.available()) {
        String s = client.readStringUntil('\n');
        Serial.println("Read: " + s);
      }
    }

    // close the connection:
    client.stop();
    Serial.println("client disonnected.");
  }
}
