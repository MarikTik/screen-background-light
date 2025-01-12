#include "wifi.hpp"
#include "logging.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

namespace comm{
     wifi::wifi(const char *ssid, const char *password, const char *hostname)
          : _ssid(ssid), _password(password), _hostname(hostname)
     {
     }

     void wifi::begin()
     {
          WiFi.begin(_ssid, _password);
          log_verbose("Connecting to %s network\n", _ssid);
          while(WiFi.status() != WL_CONNECTED){
               delay(200);
               log_debug(".");
          }
          log_info("\nConnection established\n");
          log_debug("Local IP: %s\n", WiFi.localIP().toString().c_str());

          if (MDNS.begin(_hostname)) {
               log_debug("mDNS responder started, hostname is %s\n", _hostname);
          }
          else {
               log_error("Error setting up mDNS responder\n");
          }
     }

     void wifi::update(){
          MDNS.update();
     }
}