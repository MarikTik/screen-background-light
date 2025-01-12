/**
 * @file ota.hpp
 * @brief Provides a wrapper class for managing OTA (Over-The-Air) updates on ESP32.
 *
 * This header defines the `ota` class, which encapsulates the functionality for setting up
 * and managing OTA updates. It allows customization of OTA behavior through callbacks for
 * events such as start, end, progress, and errors.
 *
 * @note This library leverages the ArduinoOTA library for OTA updates and is tailored for ESP32 devices.
 */
#ifndef OTA_HPP_
#define OTA_HPP_
#include <ArduinoOTA.h>
namespace comm{
     /**
     * @class ota
     * @brief Encapsulates the functionality for managing OTA updates on ESP32.
     *
     * The `ota` class provides an interface for configuring and handling OTA updates.
     * It supports custom callbacks for various stages of the OTA process and allows
     * updates to be handled seamlessly.
     */
     class ota{
          using status_callback_t = ArduinoOTAClass::THandlerFunction;              ///< Type alias for status-related callback functions.
          using progress_callback_t = ArduinoOTAClass::THandlerFunction_Progress;   ///< Type alias for progress-related callback functions.
          using error_callback_t = ArduinoOTAClass::THandlerFunction_Error;         ///< Type alias for error-related callback functions.
     public:
          /**
          * @brief Constructs an `ota` instance with the specified port for OTA updates.
          *
          * @param port The TCP port to be used for OTA updates (default is 3232).
          */
          ota(uint16_t port);

          /**
          * @brief Initializes the OTA process.
          *
          * This method configures the OTA server and prepares it to accept incoming update requests.
          * It sets the port for OTA communication and starts the server.
          */
          void begin();

          /**
          * @brief Handles OTA updates.
          *
          * This method must be called periodically in the main loop to process OTA requests.
          */
          void update();


          /**
          * @brief Sets a callback to be executed when an OTA update starts.
          *
          * @param status_callback The callback function to execute on OTA start.
          * @return A reference to the current `ota` instance for method chaining.
          */
          ota& on_start(status_callback_t status_callback);

          /**
          * @brief Sets a callback to be executed when an OTA update ends.
          *
          * @param status_callback The callback function to execute on OTA end.
          * @return A reference to the current `ota` instance for method chaining.
          */
          ota& on_end(status_callback_t status_callback);


          /**
          * @brief Sets a callback to track OTA update progress.
          *
          * @param progress_callback The callback function to execute for tracking progress.
          * It receives two parameters: the current progress and the total size.
          * @return A reference to the current `ota` instance for method chaining.
          */
          ota& on_progress(progress_callback_t progress_callback);


          /**
          * @brief Sets a callback to track OTA update progress.
          *
          * @param progress_callback The callback function to execute for tracking progress.
          * It receives two parameters: the current progress and the total size.
          * @return A reference to the current `ota` instance for method chaining.
          */
          ota& on_error(error_callback_t error_callback);
          
     private:
          uint16_t _port; ///< The TCP port used for OTA communication.
     };


}  // namespace scr::comm

#endif // OTA_HPP_