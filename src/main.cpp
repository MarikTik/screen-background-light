#include <Arduino.h>
#include "wifi.h"
#include "tcp_server.h"


static wifi_connection connection(WIFI_SSID, WIFI_PASSWORD, HOSTNAME);
static tcp_server server(SERVER_PORT);

void setup() {
  Serial.begin(BAUD_RATE);
  connection.begin();
  server.begin();
}

void loop(){
  connection.update();
  server.update();
}