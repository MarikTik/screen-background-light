#include "tcp_server.h"
#include "log.h"
#include <WiFiClient.h>
tcp_server::tcp_server(uint16_t port)
     : _server(port)
{
}

void tcp_server::begin()
{
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
}
