#ifndef WIFI_H_
#define WIFI_H_

class wifi_connection{
public:
     wifi_connection(const char* ssid, const char* password, const char* hostname);
     void begin();
     void update();

private:
     const char* _ssid;
     const char* _password;
     const char* _hostname;
};

#endif