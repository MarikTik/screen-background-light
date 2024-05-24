#include "wifi.h"
#include "log.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

void wifi_connection::begin(){
     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
     log_v("Connecting to %s network\n", WIFI_SSID);
     while(WiFi.status() != WL_CONNECTED){
          delay(200);
          log_d(".");
     }
     log_i("\nConnection established\n");
     log_d("Local IP: %s\n", WiFi.localIP().toString().c_str());
     
     if (MDNS.begin(HOSTNAME)) {
          log_d("mDNS responder started, hostname is %s\n", HOSTNAME);
     }
     else {
          log_e("Error setting up mDNS responder\n");
     }
}

void wifi_connection::update(){
     MDNS.update();
}
