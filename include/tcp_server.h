#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_
#include <WiFiServer.h>
 
class tcp_server{
public:   
     tcp_server(const char* hostname, uint16_t port);
     void begin();
     void update();

private:
     WiFiServer _server;
     const char* _hostname;
};


#endif