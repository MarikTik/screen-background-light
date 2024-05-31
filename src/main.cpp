#include <Arduino.h>
#include "wifi.h"
#include "tcp_server.h"
#include "ota_server.h"

static wifi_connection connection(WIFI_SSID, WIFI_PASSWORD, HOSTNAME);
static tcp_server worker_server(HOSTNAME, SERVER_PORT);
static ota_server ota_download_server(HOSTNAME, OTA_SERVER_PORT);

void setup() {
  Serial.begin(BAUD_RATE);
  connection.begin();
  worker_server.begin();
  ota_download_server.begin();
}

void loop(){
  connection.update();
  worker_server.update();
  ota_download_server.update();
}
