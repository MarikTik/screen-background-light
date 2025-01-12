#include "ota.hpp"
#include <ArduinoOTA.h>
#include <cstring>
#include <ESP8266mDNS.h>
#include "logging.hpp"

namespace comm{
          ota::ota(uint16_t port)
          : _port(port)
     {
     }

     void ota::begin()
     {
          ArduinoOTA.setPort(_port);
          ArduinoOTA.begin();

          on_start([]() {
               #if LOG_LEVEL >= LOG_LEVEL_INFO
                    char ota_upload_type[11]; // max(sizeof("filesystem"), sizeof("sketch")) == 11
                    if (ArduinoOTA.getCommand() == U_FLASH) 
                         std::strcpy(ota_upload_type, "sketch");
                    else // U_SPIFFS
                         std::strcpy(ota_upload_type, "filesystem");
                    Serial.printf("Start updating %s", ota_upload_type);
               #endif
          })
          .on_progress([](unsigned int progress, unsigned int total) {
               log_debug("Progress: %u%%\r", (progress / (total / 100)));
          })
          .on_end([]() {
               log_info("Update complete");
          })
          .on_error([this](ota_error_t error) {
                    log_fatal("unable to establish connection, error code: %u", error);
               if (error == OTA_AUTH_ERROR)
                    log_fatal("Auth Failed");
               else if (error == OTA_BEGIN_ERROR)
                    log_error("OTA_BEGIN_ERROR");
               else if (error == OTA_CONNECT_ERROR)
                    log_error("OTA_CONNECT_ERROR");
               else if (error == OTA_RECEIVE_ERROR)
                    log_error("OTA_RECEIVE_ERROR");
               else if (error == OTA_END_ERROR)
                    log_error("OTA_END_ERROR");
          });
     }

     void ota::update()
     {
          ArduinoOTA.handle();
     }

     ota &ota::on_start(status_callback_t status_callback)
     {
          ArduinoOTA.onStart(status_callback);
          return *this;
     }

     ota &ota::on_end(status_callback_t status_callback)
     {
          ArduinoOTA.onEnd(status_callback);
          return *this;
     }

     ota &ota::on_progress(progress_callback_t progress_callback)
     {
          ArduinoOTA.onProgress(progress_callback);
          return *this;
     }

     ota &ota::on_error(error_callback_t error_callback)
     {
          ArduinoOTA.onError(error_callback);
          return *this;
     }
}

