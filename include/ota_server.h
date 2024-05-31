#ifndef OTA_SERVER_H_
#define OTA_SERVER_H_
#include <ArduinoOTA.h>
#include <functional>

class ota_server{
     using status_callback_t = ArduinoOTAClass::THandlerFunction;
     using progress_callback_t = ArduinoOTAClass::THandlerFunction_Progress;
     using error_callback_t = ArduinoOTAClass::THandlerFunction_Error;
public:
     ota_server(const char* hostname, uint16_t port);
     void begin();
     void update();

     ota_server& on_start(status_callback_t status_callback);
     ota_server& on_end(status_callback_t status_callback);
     ota_server& on_progress(progress_callback_t progress_callback);
     ota_server& on_error(error_callback_t error_callback);
private:
     
     const char* _hostname;
     uint16_t _port;

};


#endif