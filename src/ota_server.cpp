#include "ota_server.h"
#include "log.h"
#include <ArduinoOTA.h>
#include <cstring>
ota_server::ota_server(const char *hostname, uint16_t port)
     : _hostname(hostname), _port(port)
{
}

void ota_server::begin()
{
     ArduinoOTA.setPort(_port);
     ArduinoOTA.setHostname(_hostname);
     ArduinoOTA.begin();

     on_start([]() {
          #if LOG_LEVEL == LOG_LEVEL_INFO
               char ota_upload_type[10]; // max(sizeof("filesystem"), sizeof("sketch")) == 10
               if (ArduinoOTA.getCommand() == U_FLASH) 
                    std::strcpy(ota_upload_type, "sketch");
               else // U_SPIFFS
                    std::strcpy(ota_upload_type, "filesystem");
               Serial.printf("Start updating %s", ota_upload_type);
          #endif
     })
     .on_progress([](unsigned int progress, unsigned int total) {
          log_d("Progress: %u%%\r", (progress / (total / 100)));
     })
     .on_end([]() {
          log_i("Update complete");
     })
     .on_error([](ota_error_t error) {
          log_e("%u", error);
          if (error == OTA_AUTH_ERROR)
               log_e("Auth Failed");
          else if (error == OTA_BEGIN_ERROR)
               log_e("Auth Failed");
          else if (error == OTA_CONNECT_ERROR)
               log_e("Auth Failed");
          else if (error == OTA_RECEIVE_ERROR)
               log_e("Auth Failed");
          else if (error == OTA_END_ERROR)
               log_e("Auth Failed");
     });
}

void ota_server::update()
{
     ArduinoOTA.handle();
}

ota_server &ota_server::on_start(status_callback_t status_callback)
{
     ArduinoOTA.onStart(status_callback);
     return *this;
}

ota_server &ota_server::on_end(status_callback_t status_callback)
{
     ArduinoOTA.onEnd(status_callback);
     return *this;
}

ota_server &ota_server::on_progress(progress_callback_t progress_callback)
{
     ArduinoOTA.onProgress(progress_callback);
     return *this;
}

ota_server &ota_server::on_error(error_callback_t error_callback)
{
     ArduinoOTA.onError(error_callback);
     return *this;
}