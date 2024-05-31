#include "tcp_server.h"
#include "log.h"
#include <functional>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>

static inline void call_if_no_ota_present(std::function<void()> function)
{
    #if defined(HOSTNAME) and !defined(USE_OTA)
      function();
    #endif
}

tcp_server::tcp_server(const char* hostname, uint16_t port)
    : _server(port), _hostname(hostname)
{
}

void tcp_server::begin()
{
    call_if_no_ota_present([this](){
        if(MDNS.begin(_hostname))
          log_v("MDNS responder started");
        else 
          log_e("Error setting up MDNS responder");
    });
    _server.begin();
}

void tcp_server::update()
{
    auto client = _server.accept();
    if (client) {
      log_v("Client connected");
      while (client.connected()) {
        while(client.available())
        {
          char c = client.read();
          Serial.write(c);
        }
      }
      client.stop();
      log_v("Client disconnected");
    }
    call_if_no_ota_present([](){
        MDNS.update();
    });
}
